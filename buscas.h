#ifndef BUSCABINARIA_H_INCLUDED
#define BUSCABINARIA_H_INCLUDED

#include "utils.h"
#include "funcionario.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>

//Realiza uma busca binaria por um funcionario na base de dados
TFunc *buscarFuncionario_binariamente(int chave, FILE *arquivo, int tam);
//Realiza uma busca sequencial por um funcionario na base de dados
TFunc *buscaSequencial(int chave, FILE *in);

#endif // BUSCABINARIA_H_INCLUDED
