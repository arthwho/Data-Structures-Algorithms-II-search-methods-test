#include "buscas.h"
#include "funcionario.h"
#include "utils.h"
#include "insertionSort.h"

//code .
//gcc -o main ./*.c

int main()
{
    FILE *arq;
    TFunc *f;
    f = (TFunc *)malloc(sizeof(TFunc));
    int codigoBusca;

    while (1){

        printf("\033[H\033[J");
        if ((arq = fopen("funcionario.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
        }

        else{

            int op;
            criarBase(arq, 1000);
            printf("\033[H\033[J"); // Limpa a tela, melhor que system("cls") e é multiplataforma.
            gotoxy(20,10);
            printf("1. Imprimir base de dados: \n");
            gotoxy(20,12);
            printf("2. Realizar busca sequencial: \n");
            gotoxy(20,14);
            printf("3. Realizar busca binaria: \n");
            gotoxy(20,16);
            printf("4. Realizar insertion sort: \n");
            gotoxy(20,18);
            printf("0. Sair: \n");
            gotoxy(20,20);
            printf("Digite a opcao desejada: ");
            scanf("%d", &op);

            switch (op){
            case 0:
                exit(0);
                free(f);
                break;

            case 1:
                imprimirBase(arq);
                break;

            case 2:
                f = buscaSequencial(0, arq);
                imprime(f);
                break;

            case 3:
                f = buscarFuncionario_binariamente(0, arq, tamanho_arquivo(arq));
                if (f != NULL)   
                    imprime(f);
                    
                break;

            case 4:
                insertionSort(arq, tamanho_arquivo(arq));
                imprimirBase(arq);
                break;

            default:
                break;
            }
            printf("Aperte enter para continuar...\n");
            getch();

        }
    }
}
