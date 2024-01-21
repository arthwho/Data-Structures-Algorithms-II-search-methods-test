#ifndef INTERCALACAO_H_INCLUDED
#define INTERCALACAO_H_INCLUDED

#include "utils.h"
#include "funcionario.h"
#include "livro.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>

/**
 * @brief enum para as funções genéricas de comparação
 * 
 * @param FUNCIONARIO TFunc
 * @param LIVRO TLivro
 */
typedef enum {
    FUNCIONARIO,
    LIVRO
} TipoRegistro;

typedef struct{

    float tempo;
    int num_registro_per_partition;
    int num_partitions;
} intercalacao_otima_struct;

int compare_records(const void *a, const void *b, TipoRegistro tipo);

void intercalacao_otima_Func();
void intercalacao_otima_Livro();
void intercalacoes_otimas();


intercalacao_otima_struct* save_intercalacao_otima_struct(int num_partitions, int num_registro_per_partition, float tempo);
#endif // INTERCALACAOBASICA_H_INCLUDEDcls