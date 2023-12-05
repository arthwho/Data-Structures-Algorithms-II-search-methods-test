#include "buscas.h"   

//Realiza uma busca binaria por um funcionario na base de dados
TFunc *buscarFuncionario_binariamente(int chave, FILE *arquivo, int tam) {
    TFunc *registro = (TFunc *)malloc(sizeof(TFunc));
    arquivo = fopen("funcionario.dat", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    int esq = 0;
    int dir = tam - 1;
    int iteracoes = 0;

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