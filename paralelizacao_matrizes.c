/* 
UNIVERSIDADE FEDERAL DE SÃO CARLOS
DEPARTAMENTO DE COMPUTAÇÃO
SISTEMAS OPERACIONAIS 2
HÉLIO CRESTANA GUARDIA

ATIVIDADE: Estudo de paralelização em um programa de multiplicação de matrizes
AUTORES:
Juliano Lansarini			489093
Romão Martines				595071
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <omp.h>

//Atribuicao de valores default para o numero de linhas e o numero de colunas
#define NLIN 1000
#define NCOL 1000
#define NTHR 4

//Definição do calculo de tempo de processamento de cada atividade
#define toSeconds(t) (t.tv_sec + (t.tv_usec/1000000.))

//Declaração de variáveis globais
int **_A, **_B, **_C;

int _nlin = 0;
int _ncol = 0;
int _nthr = 0;

int _insert = 0;
int _random = 0;


int main (int argc, char *argv[])
{
	//Declaração de variáveis
	int i, j, k;					//contadores de laço
	int temp; 						//auxiliar de calculo que diminuirá tempo de processamento

	//Estruturas para medição de processamento
	struct timeval inic, fim;
	struct rusage r1, r2;


	//Passagem das linhas, colunas e threads da matriz por parametro na linha de execução
	//	se nada for passado, utilizar valores default
	//	caso contrario, executar apenas se todos os parametros forem passados
	if(argc == 5)
	{
		for(i=0; i<5; i++)
			printf("argv[%d]: %s ", i, argv[i]);

		printf("\n");

		//atribui os parametros apenas se forem positivos
		_nlin = (atoi(argv[2]) >= 0) ? atoi(argv[2]) : NLIN;
		printf("passou n_lin = %d\n", _nlin);
		_ncol = (atoi(argv[3]) >= 0) ? atoi(argv[3]) : NCOL;
		printf("passou n_col = %d\n", _ncol);
		_nthr = (atoi(argv[4]) >= 0) ? atoi(argv[4]) : NTHR;
		printf("passou n_thr = %d\n", _nthr);

		printf("lin: %d\n col: %d\n thr: %d\n", _nlin, _ncol, _nthr);

		//"-i" entra no modo de inserção: o usuario insere os numeros nas matrizes
		if(!strcmp(argv[1], "-i"))
			_insert = 1;

		//"-r" entra no modo randomico: o programa gera os numeros das matrizes
		if(!strcmp(argv[1], "-r"))
			_random = 1;
	}
	else if(argc == 2)
	{
		//exibe ajuda
		if(!strcmp(argv[1], "-h"))
		{
			printf("Uso: %s [-nl n_linhas] [-nc n_colunas] [-nt n_threads]" "[-r] //random [-i] //insercao\n", argv[0]);
			exit(0);
		}
		//roda o programa no modo default
		if(!strcmp(argv[1], "-d"))
		{
			_nlin = NLIN;
			_ncol = NCOL;
			_nthr = NTHR;
		}
		printf("Modo default!\n");
		printf("Numero de linhas: %d\n", _nlin);
		printf("Numero de colunas: %d\n", _ncol);
		printf("Numero de threads: %d\n", _nthr);
	}
	else
	{
		printf("Passagem de parametros incorreta!\n");
		exit(0);
	}


	//Alocação dinâmica de cada matriz utilizada no programa
	_A = (int**) malloc(_nlin * sizeof(int*));
	_B = (int**) malloc(_nlin * sizeof(int*));
	_C = (int**) malloc(_nlin * sizeof(int*));

	for (i=0; i<_nlin; i++)
	{
		_A[i] = (int*) malloc(_ncol * sizeof(int*));
		_B[i] = (int*) malloc(_ncol * sizeof(int*));
		_C[i] = (int*) malloc(_ncol * sizeof(int*));
	}

	if(_insert)
	{
		//População das matrizes no modo de inserção
		for(i=0; i<_nlin; i++)
		{
			for(j=0; j<_ncol; j++)
			{
				printf("A[%d][%d]: \n", i, j);
				scanf("%d", &_A[i][j]);
			}
		}

		for(i=0; i<_nlin; i++)
		{
			for(j=0; j<_ncol; j++)
			{
				printf("B[%d][%d]: \n", i, j);
				scanf("%d", &_B[i][j]);
			}
		}
	}
	else if(_random)
	{
		//Limpeza de buffer de sementes aleatórias
		srand(time(NULL));

		//População das matrizes com numeros aleatorios
		for(i=0; i<_nlin; i++)
		{
			for(j=0;j<_ncol;j++)
			{
				//Utilizaremos rand()%100 e assim os valores serão 
				//gerados no intervalo de 0 a 99
				_A[i][j] = rand()%100;
				_B[i][j] = rand()%100;
			}
		}
	}
	


	//Medição de tempo e consumo de recursos antes das operações
	gettimeofday(&inic, 0);
	getrusage(RUSAGE_SELF, &r1);

	//Calculo da multiplicacao de matrizes
	//Utilização de paralelismo por linhas da matriz
	#pragma omp for private(i, j, k)
	{
		for(i=0; i<_nlin; i++)
		{
			for(j=0; j<_ncol; j++)
			{
				_C[i][j] = 0;
				for(k=0; k<_nlin; k++)
				{
					temp = _A[i][j] * _B[i][j];
				}
				_C[i][j] = temp;
				temp = 0;
			}
		}
	}
	

	//Medição de tempo e consumo de recursos depois das operações
	gettimeofday(&fim, 0);
	getrusage(RUSAGE_SELF, &r2);

	//Exibição dos resultados
	printf("\n");
	printf("Tempo de processamento das operacoes: (%dx%d/%d threads): \n", _nlin, _ncol, _nthr);
	printf("Elapsed time: %.4fsec\n", toSeconds(fim)-toSeconds(inic));
	printf("User time: %.4fsec\n",toSeconds(r2.ru_utime)-toSeconds(r1.ru_utime));
	printf("System time: %.4f\n",toSeconds(r2.ru_stime)-toSeconds(r1.ru_stime));

	//Liberação do espaço alocado pelas matrizes
	for (i=0; i<_nlin; i++)
	{
		free(_A[i]);
		free(_B[i]);
		free(_C[i]);
	}
	free(_A);
	free(_B);
	free(_C);
} 