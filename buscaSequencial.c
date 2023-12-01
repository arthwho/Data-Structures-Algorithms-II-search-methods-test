#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "utils.h"
#include "funcionario.c"

//Realiza uma busca sequencial por um funcionario na base de dados
TFunc *buscaSequencial(int chave, FILE *in){

    TFunc *f;
    int achou;

    system("cls");
    gotoxy(10,3);
    printf("Digite o codigo do funcionario: ");
    scanf("%d", &chave);

    gotoxy(0,5);
    printf("%-10s %-20s %-20s %-10s %-10s\n\n", "COD", "Funcionario", "CPF", "Data", "Salario");

    rewind(in);

    while ((f = le(in)) != NULL){

        if(f->cod == chave){
           //return f;
           achou = 1;
           break;
        }
    }
        if(achou == 1)
            return f;
        else printf("Funcionario nao encontrado");

    free(f);
}
