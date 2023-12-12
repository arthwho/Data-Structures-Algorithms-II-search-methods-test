#include "buscas.h"
#include "funcionario.h"
#include "utils.h"
#include "insertionSort.h"
#include "livro.h"

//code .
//gcc -o main ./*.c

int main()
{
    FILE *arq,*Larq;
    TFunc *f;
    TLivro *l;
    f = (TFunc *)malloc(sizeof(TFunc));
    l = (TLivro *)malloc(sizeof(TLivro));
    clock_t start, end;
    double cpu_time_used;

    while (1){

        printf("\033[H\033[J");

        if ((arq = fopen("funcionario.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo de funcionarios\n");
        exit(1);
        }
        if ((Larq = fopen("livro.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo de livros\n");
        exit(1);
        }

        else{

            int op;
            criarBase(arq, 1000);
            criarBaseDeLivros(Larq, 1000);
            printf("\033[H\033[J"); // Limpa a tela, melhor que system("cls") e é multiplataforma.
            gotoxy(15,5);
            printf("1. Imprimir base de dados de funcionarios: ");
            gotoxy(15,7);
            printf("2. Realizar busca sequencial de funcionario: ");
            gotoxy(15,9);
            printf("3. Realizar busca binaria de funcionario: ");
            gotoxy(15,11);
            printf("4. Realizar insertion sort de funcionarios: ");
            gotoxy(70,5);
            printf("5. Imprimir base de dados de livros: ");
            gotoxy(70,7);
            printf("6. Realizar busca binaria de livro: ");
            gotoxy(70,9);
            printf("7. Realizar insertion sort de livros: ");
            gotoxy(15,17);
            printf("0. Sair: ");
            gotoxy(15,20);
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
                start = clock();
                f = buscaSequencial(0, arq);
                imprime(f);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nTempo de execucao: %f\n", cpu_time_used);
                fflush(stdout);
                break;

            case 3:
                start = clock();
                f = buscarFuncionario_binariamente(0, arq, tamanho_arquivo(arq));
                if (f != NULL)   
                    imprime(f);

                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nTempo de execucao: %f\n", cpu_time_used);
                fflush(stdout);
                break;

            case 4:
                insertionSort(arq, tamanho_arquivo(arq));
                imprimirBase(arq);
                break;

            case 5:
                imprimirBaseDeLivros(Larq);
                break;

            case 6:
                start = clock();
                l = buscarLivro_binariamente(0, Larq, tamanho_arquivo_livro(Larq), NULL);
                if (l != NULL)   
                    imprimeLivro(l);

                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nTempo de execucao: %f\n", cpu_time_used);
                fflush(stdout);
                break;

            case 7:
                insertionSort_livros(Larq, tamanho_arquivo_livro(Larq));
                imprimirBaseDeLivros(Larq);
                break;

            default:
                break;
            }
            printf("Aperte enter para continuar...\n");
            getch();

        }
    }
}
