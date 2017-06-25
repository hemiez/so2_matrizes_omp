# Sistemas Operacionais 2
Trabalho da disciplina de Sistemas Operacionais 2, oferecida pelo Departamento de Computação da Universidade Federal de São Carlos

## 1. Objetivo
Utilizar as funções da biblioteca OpenMP para realizar o processamento de um programa que realiza o cálculo da multiplicação de matrizes.

### 1.1 Execução do código
Para a execuçã do código, deve se executar a extensão para que a bilbioteca OpenMP
seja executada junto da execução do programa.

```
$gcc paralelizacao_matrizes.c -o paralelizacao_matrizes -fopenmp
```
####1.1.1 Modo de Inserção
O programa pode ser executado de tal forma que o usuário pode inserir os valores desejados nas matrizes a serem multiplicadas. Para isso basta executar o programa, depois de compilado, da seguinte maneira:

```
$./paralelizacao_matrizes -i <numero_Linhas> <numero_Colunas> <numero_Threads>
```

####1.1.2 Modo Default
As variáveis principais do programa são setadas com os seguintes valores:
```c
#define NLIN 1000
#define NCOL 1000
#define NTHR 4
```
Caso o usuário deseje utilizar destes valores para a execução do código, basta rodar o seginte comando na linha de execução:
```
$./paralelizacao_matrizes -d
```
####1.1.3 Modo Randômico
Por fim, caso o usuário deseje indicar o número de linhas, colunas e threads, porém não queira especificar os campos da matriz, o programa gera matrizes aleatórias para o cálculo, já que o importante aqui é saber o tempo de processamento. Para executar o programa desta forma, basta utilizarmos:
```
$./paralelizacao_matrizes -r <numero_Linhas> <numero_Colunas> <numero_Threads>
```
####1.2 Menu de Ajuda
A qualquer momento você pode pela linha de comando solicitar a forma de passagem de parâmetros do programa, basta utilizar:
```
$./paralelizacao_matrizes -h
```
##2. Equipe
Os alunos desenvolvedores deste projeto são:

[Juliano Lanssarini](https://github.com/jlanssarini)

[Romão Martines](https://github.com/hemiez)
