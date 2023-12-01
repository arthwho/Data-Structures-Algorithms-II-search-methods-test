
#include "funcionario.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

//Realiza uma busca binaria por um funcionario na base de dados

TFunc *busca_binaria(int chave, FILE *in, int inicio, int fim) {

    TFunc *f = NULL;
    int cod = -1;

    while (inicio <= fim && cod != chave) {

        int meio = trunc((inicio + fim) / 2);
        printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
        fseek(in, (meio -1) * tamanho_registro(), SEEK_SET);
        f = le(in);
        cod = f->cod;

        if (f) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }

    if (cod == chave) {
        return f;
    }
    else return NULL;
}
