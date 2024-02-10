#include "estruturas.h" 

int main()
{
    FILE *arq,*Larq,*log,*index;
    TFunc *f = (TFunc *)malloc(sizeof(TFunc));
    TLivro *l = (TLivro *)malloc(sizeof(TLivro));
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));

    clock_t start, end;
    double cpu_time_used;

    while (1){

        printf("\033[H\033[J");

        if ((arq = fopen(EMPLOYEE_FILE_PATH, "wb+")) == NULL) {
        printf("Erro ao abrir arquivo de funcionarios\n");
        exit(1);
        }
        if ((Larq = fopen(BOOK_FILE_PATH, "wb+")) == NULL) {
        printf("Erro ao abrir arquivo de livros\n");
        exit(1);
        }
        if ((log = fopen(LOG_FILE_PATH, "w+b")) == NULL) {
        printf("Erro ao abrir arquivo de logs\n");
        exit(1);
        }
        if ((index = fopen(INDEX_FILE_PATH, "w+b")) == NULL) {
        printf("Erro ao abrir arquivo Index\n");
        exit(1);
        }
        if (myHashTable == NULL) {
            myHashTable = loadHashTable(); // If the hash table is not initialized, initialize it from the file
            if (myHashTable == NULL) { // If the file does not exist, create a new hash table 
                    myHashTable = createHashTable();
                }
        }

        else{
            arq = fopen(EMPLOYEE_FILE_PATH, "rb+");
            Larq = fopen(BOOK_FILE_PATH, "rb+");

            int op;
            criarBase(arq, 10);
            criarBaseDeLivros(Larq, 10);
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
            gotoxy(70,11);
            printf("8. Realizar quick sort de funcionarios e livros:");
            gotoxy(15,13);
            printf("9. Realizar classificacao de funcionarios: ");
            gotoxy(70,13);
            printf("10. Realizar classificacao de livros: ");
            gotoxy(15,17);
            printf("11. Realizar intercalacao otima: ");
            gotoxy(15,19);
            printf("12. Inserir na tabela hash: ");
            gotoxy(70,17);
            printf("13. Pesquisar na tabela hash: ");
            gotoxy(70,19);
            printf("14. Remover da tabela hash: ");
            gotoxy(15,24);
            printf("0. Sair: ");
            gotoxy(15,26);
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
                f = buscarFuncionario_binariamente(0, arq, tamanho_arquivo(arq), log);
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
                l = buscarLivro_binariamente(10, Larq, tamanho_arquivo_livro(Larq), log);
                if (l != NULL) 
                    imprimeLivro(l);

                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nTempo de execucao: %f\n", cpu_time_used);
                fflush(stdout);
                break;

            case 7:
                printf("\033[H\033[J");
                insertionSort_livros(Larq, tamanho_arquivo_livro(Larq));
                imprimirBaseDeLivros(Larq);
                break;

            case 8:
                quicksort_both();
                //imprimirBase(arq);
                printLivroCodes(Larq, tamanho_arquivo_livro(Larq));
                //printFuncCodes(arq, tamanho_arquivo(arq));
                break;

            case 9:
                classificacao_interna_Func(EMPLOYEE_FILE_PATH,sizeof(TFunc));
                break;

            case 10:
                classificacao_interna_livro(BOOK_FILE_PATH,sizeof(TLivro));
                break;

            case 11:
                intercalacoes_otimas();
                break;

            case 12: {
                printf("\033[H\033[J");
                TLivro livroToInsert;
                gotoxy(10,3);
                printf("Digite o codigo do livro a ser inserido: ");
                scanf("%d", &livroToInsert.id);
                start = clock();
                insert_hash(hashTable, livroToInsert.id, livroToInsert);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nTempo de execucao: %f\n", cpu_time_used);
                break;
            }

            case 13: {
                printf("\033[H\033[J");
                gotoxy(10,3);
                printf("Digite o codigo do livro a ser pesquisado: ");
                int keyToSearch;
                scanf("%d", &keyToSearch);
                start = clock();
                TLivro foundLivro = search_hash(hashTable, keyToSearch);
                if (foundLivro.id != -1) {
                    // Print the found livro data
                    printf("Livro encontrado: %d\n", foundLivro.id);
                } else {
                    printf("Livro nao encontrado na tabela\n");
                }
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nTempo de execucao: %f\n", cpu_time_used);
                break;
            }

            case 14:
                printf("\033[H\033[J");
                gotoxy(10,3);
                printf("Digite o codigo do livro a ser removido: ");
                int keyToRemove;
                scanf("%d", &keyToRemove);
                start = clock();
                remove_hash(hashTable, keyToRemove);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nTempo de execucao: %f\n", cpu_time_used);
                break;

            default:
                break;
            }
            
            printf("Aperte enter para continuar...\n");
            getch();

        }
    }
}
