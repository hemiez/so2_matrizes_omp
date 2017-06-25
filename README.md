# Sistemas Operacionais 2
Trabalho da disciplina de Sistemas Operacionais 2, oferecida pelo Departamento de Computação da Universidade Federal de São Carlos

## 1. Objetivo
Utilizar as funções da biblioteca OpenMP para realizar o processamento de um programa que realiza o cálculo da multiplicação de matrizes.

### 1.1 Execução do código
Para a execuçã do código, deve se executar a extensão para que a bilbioteca OpenMP
seja executada junto da execução do programa.

```
$gcc omp_matrix.c -o omp_matrix -fopenmp
```

#### 1.1.1 Modo Default
As variáveis principais do programa são setadas com os seguintes valores:
```c
#define NLIN 1500
#define NCOL 1500
#define NTHR 4
```
Caso o usuário deseje utilizar destes valores para a execução do código, basta rodar o seginte comando na linha de execução:
```
$./omp_matrix -d
```
#### 1.1.3 Modo Randômico
As matrizes aqui são geradas de maneira randômica e a forma de paralelismo também é passada por parâmetro da seguinte forma:

##### a. Paralelização por linhas
```
$./omp_matrix -l <numero_Linhas> <numero_Colunas> <numero_Threads>
```
##### b. Paralelização por colunas
```
$./omp_matrix -c <numero_Linhas> <numero_Colunas> <numero_Threads>
```

##### c. Paralelização por operações
```
$./omp_matrix -c <numero_Linhas> <numero_Colunas> <numero_Threads>
```

#### 1.2 Menu de Ajuda
A qualquer momento você pode pela linha de comando solicitar a forma de passagem de parâmetros do programa, basta utilizar:
```
$./paralelizacao_matrizes -h
```
## 2. Equipe
Os alunos desenvolvedores deste projeto são:

[Juliano Lanssarini](https://github.com/jlanssarini)

[Romão Martines](https://github.com/hemiez)
