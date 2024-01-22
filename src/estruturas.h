/*************************************************
 * 
 * modulo: estruturas.h
 * 
 * 
**************************************************/

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>

/*************************************************
 * Defines and utils
**************************************************/

#define EMPLOYEE_FILE_PATH "src/bin/window_employee.dat"
#define PARTITIONS_PATH "src/bin/partitions"
#define BOOK_FILE_PATH "src/bin/window_books.dat"
#define LOG_FILE_PATH "src/bin/window_log.dat"

int NUM_PARTITIONS;
int INT_MAX;

void gotoxy(int x,int y);

/*************************************************
 * Structs
**************************************************/

typedef struct livro{
    int id;
    char titulo[50];
    char autor[50];

    TFunc *funcionario;

} TLivro;


typedef struct funcionario{
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

/*************************************************
 * Funcoes de Livro
**************************************************/

int tamanho_registro_livro();
int tamanho_arquivo_livro(FILE *arquivo);

TLivro *livro(int id, char *titulo, char *autor, TFunc *funcionario);
TLivro *leLivro(FILE *entrada); // Ler o funcionario

void salvaLivro(TLivro *livro, FILE *saida); // Salvar o funcionario
void imprimeLivro(TLivro *livro); // Imprimir o funcionario
void criarBaseDeLivros(FILE *saida, int tamanho); // Incluir o funcionario
void shuffle_livro(int *vet, int size); // Muda se precisar
void imprimirBaseDeLivros(FILE *saida); // Mudar

/*************************************************
 * Funcoes de Funcionario
**************************************************/


int tamanho_registro();
int tamanho_arquivo(FILE *arquivo);

TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario);
TFunc *le(FILE *in);

void salva(TFunc *func, FILE *out);
void imprime(TFunc *func);
void criarBase(FILE *out, int tam);
void shuffle(int *vet, int size);
void imprimirBase(FILE *out);

#endif // ESTRUTURAS_H