#ifndef BUSCABINARIA_H_INCLUDED
#define BUSCABINARIA_H_INCLUDED

#include "utils.h"
#include "funcionario.h"
#include "livro.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>

//Realiza uma busca binaria por um funcionario na base de dados
TFunc *buscarFuncionario_binariamente(int chave, FILE *arquivo, int tam, FILE *LogFileBinary);
//Realiza uma busca sequencial por um funcionario na base de dados
TFunc *buscaSequencial(int chave, FILE *in);
void salvar_log_file_binary(FILE *out, int iteracoes, double tempo_ms);
TLivro *buscarLivro_binariamente(int chave, FILE *arquivo, int tam, FILE *LogFileBinary);
TLivro *busca_binariaDeLivro(int chave, FILE *in, int inicio, int fim);

#endif // BUSCABINARIA_H_INCLUDED
