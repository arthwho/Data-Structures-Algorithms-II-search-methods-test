#include "buscas.h"
#include "funcionario.h"
#include "utils.h"
#include "insertionSort.h"


//code .
//gcc -o sistema ./*.c

int main()
{
    FILE *arq;
    TFunc *f;
    int codigoBusca;

    while (1){

        system("cls");
        if ((arq = fopen("funcionario.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
        }

        else{

            int op;
            criarBase(arq, 1000);
            system("pause");
            system("cls");
            gotoxy(20,10);
            printf("1. Imprimir base de dados: \n");
            gotoxy(20,12);
            printf("2. Realizar busca sequencial: \n");
            gotoxy(20,14);
            printf("3. Realizar busca binaria: \n");
            gotoxy(20,16);
            printf("0. Sair: \n");
            gotoxy(20,19);
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

            case 3:
                system("cls");
                insertionSort_funcionarios(arq, tamanho_registro(arq));
                printf("Imprimindo base de dados ordenada: \n");
                imprimirBase(arq);

                printf("\nDigite o codigo a ser buscado: ");
                scanf("%d",&codigoBusca);

                //f = busca_binaria(codigoBusca,arq,0,tamanho_registro(arq)-1);
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
