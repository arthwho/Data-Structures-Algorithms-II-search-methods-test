#ifndef CLASSIFICACAO_H
#define CLASSIFICACAO_H

#include "utils.h"
#include "funcionario.h"
#include "livro.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>

typedef struct{

    float tempo;
    int num_registro_per_partition;
    int num_partitions;
} classificacao_struct;

int classificacao_interna_Func(int M);
int classificacao_interna_Livro(int M);
void classificacoes(int M);

#endif
