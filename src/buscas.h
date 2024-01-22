#ifndef BUSCABINARIA_H_INCLUDED
#define BUSCABINARIA_H_INCLUDED

#include "estruturas.h"

//Realiza uma busca binaria por um funcionario na base de dados
TFunc *buscarFuncionario_binariamente(int chave, FILE *arquivo, int tam, FILE *LogFileBinary);
//Realiza uma busca sequencial por um funcionario na base de dados
TFunc *buscaSequencial(int chave, FILE *in);
void salvar_log_file_binary(FILE *out, int iteracoes, double tempo_ms);
TLivro *buscarLivro_binariamente(int chave, FILE *arquivo, int tam, FILE *LogFileBinary);

#endif // BUSCABINARIA_H_INCLUDED
