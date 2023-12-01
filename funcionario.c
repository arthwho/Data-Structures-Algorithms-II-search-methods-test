#include "funcionario.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "utils.h"

// Retorna tamanho do funcionario em bytes
int tamanho_registro() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cpf
           + sizeof(char) * 11 //data_nascimento
           + sizeof(double); //salario
}


// Cria funcionario.
TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    //inicializa espaco de memoria com ZEROS
    if (func) memset(func, 0, sizeof(TFunc));
    //copia valores para os campos de func
    func->cod = cod;
    strcpy(func->nome, nome);
    strcpy(func->cpf, cpf);
    strcpy(func->data_nascimento, data_nascimento);
    func->salario = salario;
    return func;
}


// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    //func->nome ao inves de &func->nome, pois string ja eh um ponteiro
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
    fwrite(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), out);
    fwrite(&func->salario, sizeof(double), 1, out);
}

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (0 >= fread(&func->cod, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(double), 1, in);
    return func;
}


// Imprime funcionario
void imprime(TFunc *func) {
    // printf("**********************************************");
    // printf("\nFuncionario de codigo ");
    // printf("%d", func->cod);
    // printf("\nNome: ");
    // printf("%s", func->nome);
    // printf("\nCPF: ");
    // printf("%s", func->cpf);
    // printf("\nData de Nascimento: ");
    // printf("%s", func->data_nascimento);
    // printf("\nSalario: ");
    // printf("%4.2f", func->salario);
    // printf("\n**********************************************\n\n");

    printf("%-10d %-20s %-20s %-10s %10.2f\n\n", func->cod, func->nome, func->cpf, func->data_nascimento, func->salario);
}


// Cria a base de dados
void criarBase(FILE *out, int tam){

    int vet[tam];
    TFunc *f;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet,tam,(tam*60)/100);

    printf("\nGerando a base de dados...\n");

    for (int i=0;i<tam;i++){
        f = funcionario(vet[i], "A", "000.000.000-00", "01/01/1980", 3000*i);
        salva(f, out);
    }

    free(f);

}

//embaralha base de dados
void shuffle(int *vet,int MAX,int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}


void imprimirBase(FILE *out){

system("cls");
gotoxy(10,1);
printf("\nImprimindo a base de dados...\n\n");
gotoxy(0,5);

    rewind(out);
    TFunc *f;
    printf("%-10s %-20s %-20s %-10s %-10s\n\n", "COD", "Funcionario", "CPF", "Data", "Salario");

    while ((f = le(out)) != NULL)

        imprime(f);

    free(f);

}
