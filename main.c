#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"
#include "buscaSequencial.h"
#include "utils.h"

//code .
//gcc -o sistema ./*.c

int main()
{
    FILE *arq;
    TFunc *f;

    while (1){
        if ((arq = fopen("funcionario.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
        }

        else{

            int op;
            criarBase(arq, 1000);
            system("pause");
            printf("1. Imprimir base de dados: \n");
            printf("2. Buscar funcionario: \n");
            printf("0. Sair: \n");

            printf("Digite a opcao desejada: ");
            scanf("%d", &op);

            switch (op){
            case 0:
                exit(0);
                break;

            case 1:
                imprimirBase(arq);
                break;

            case 2:
                f = buscaSequencial(0, arq);
                imprime(f);
                free(f);
                break;

            default:
                break;
            }
            printf("Aperte enter para continuar...\n");
            getch();

        }
    }
}
