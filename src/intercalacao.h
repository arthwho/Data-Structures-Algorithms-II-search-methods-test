#ifndef INTERCALACAO_H_INCLUDED
#define INTERCALACAO_H_INCLUDED

#include "estruturas.h"

// enum para as funções genéricas de comparação
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