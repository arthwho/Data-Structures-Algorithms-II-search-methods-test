#include "estruturas.h"   

void salvar_log_file_binary(FILE *out, int iteracoes, double tempo_ms) {
    TLogBinary *e = (TLogBinary *)malloc(sizeof(TLogBinary));
    e->iteracoes = iteracoes;
    e->tempo_ms = tempo_ms;
    fwrite(&e->iteracoes, sizeof(int), 1, out);
    fwrite(&e->tempo_ms, sizeof(int), 1, out);

    free(e);
}

//Realiza uma busca binaria por um funcionario na base de dados
TFunc *buscarFuncionario_binariamente(int chave, FILE *arquivo, int tam, FILE *LogFileBinary) {
    TFunc *registro = (TFunc *)malloc(sizeof(TFunc));
    arquivo = fopen(EMPLOYEE_FILE_PATH, "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    int esq = 0;
    int dir = tam - 1;
    int iteracoes = 0;
    clock_t start_time = clock(); // Marca o início do tempo de execução

    printf("\033[H\033[J");
    gotoxy(10,3);
    printf("Digite o codigo a ser buscado: ");
    scanf("%i",&chave);

    gotoxy(0,5);
    printf("%-10s %-20s %-20s %-10s %-10s\n\n", "COD", "Funcionario", "CPF", "Data", "Salario");

    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        fseek(arquivo, meio * tamanho_registro(), SEEK_SET);
        fread(registro, sizeof(TFunc), 1, arquivo);
        iteracoes++;

        if (registro->cod == chave) {
            double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC * 1000.0;
            salvar_log_file_binary(LogFileBinary, iteracoes, elapsed_time);
            return registro;
        } else if (registro->cod < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    free(registro);
    fclose(arquivo);
    return NULL;
}

//Realiza uma busca sequencial por um funcionario na base de dados
TFunc *buscaSequencial(int chave, FILE *in){

    TFunc *f;
    int achou;

    printf("\033[H\033[J");
    gotoxy(10,3);
    printf("Digite o codigo a ser buscado: ");
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
    fclose(in);
    
}

TLivro *buscarLivro_binariamente(int chave, FILE *Larquivo, int siz, FILE *LogFileBinary) {
    TLivro *book = (TLivro *)malloc(sizeof(TLivro));
    Larquivo = fopen(BOOK_FILE_PATH, "r+b");
    if (Larquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    int esq = 0;
    int dir = siz - 1;
    int iteracoes = 0;

    printf("\033[H\033[J");
    gotoxy(10,3);
    printf("Digite o codigo a ser buscado: ");
    scanf("%i",&chave);

    gotoxy(0,5);
    printf("%-10s %-20s %-20s\n\n", "COD", "Titulo", "Autor");

    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        fseek(Larquivo, meio * tamanho_registro_livro(), SEEK_SET);
        fread(book, sizeof(TLivro), 1, Larquivo);
        iteracoes++;

        if (book->id == chave) {
            return book;
        } else if (book->id < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    free(book);
    fclose(Larquivo);
    return NULL;
}
