#ifndef LIVRO_H
#define LIVRO_H

#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include "funcionario.h"

typedef struct Livro{
    int id;
    char titulo[50];
    char autor[50];
} TLivro;

// Retorna tamanho do livro em bytes
int tamanho_registro_livro();

int tamanho_arquivo_livro(FILE *arquivo);

// Cria funcionario.
TLivro *livro(int id, char *titulo, char *autor);

// Salva funcionario no arquivo out, na posicao atual do cursor
void salvaLivro(TLivro *livro, FILE *saida);

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TLivro *leLivro(FILE *entrada);

// Imprime funcionario
void imprimeLivro(TLivro *livro);

// Cria a base de dados
void criarBaseDeLivros(FILE *saida, int tamanho);

//embaralha base de dados
void shuffle_livro(int *vet, int size);

// Imprime a base de dados
void imprimirBaseDeLivros(FILE *saida);

#endif // LIVRO_H