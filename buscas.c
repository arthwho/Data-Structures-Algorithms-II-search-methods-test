#include "buscas.h"   

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
    printf("HELLO");
    if (cod == chave) {
        return f;
    }
    else return NULL;

}

//Realiza uma busca sequencial por um funcionario na base de dados
TFunc *buscaSequencial(int chave, FILE *in){

    TFunc *f;
    int achou;

    system("cls");
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
}