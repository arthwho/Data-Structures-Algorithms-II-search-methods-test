#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>

typedef struct Funcionario {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;


// Retorna tamanho do funcionario em bytes
int tamanho_registro();

// Cria funcionario.
TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario);


// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out);


// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in);


// Imprime funcionario
void imprime(TFunc *func);


// Cria a base de dados
void criarBase(FILE *out, int tam);

//embaralha base de dados
void shuffle(int *vet,int MAX,int MIN);

// Imprime a base de dados
void imprimirBase(FILE *out);


#endif // FUNCIONARIO_H
