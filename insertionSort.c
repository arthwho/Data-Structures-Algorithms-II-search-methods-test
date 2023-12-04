#include "insertionSort.h"

void insertionSort(FILE *arq, int tam) {
    TFunc *funcionarios = (TFunc *)malloc(tam * sizeof(TFunc));
    fopen("funcionario.dat", "w+b");
    printf("Debug: Insertion Sort Funcionarios Iniciado, tam = %d\n", tam);

    // Read all records into an array
    fseek(arq, 0, SEEK_SET);
    for (int i = 0; i < tam; i++) {
        fread(&funcionarios[i].cod, sizeof(int), 1, arq);
        fread(funcionarios[i].nome, sizeof(char), sizeof(funcionarios[i].nome), arq);
        fread(funcionarios[i].cpf, sizeof(char), sizeof(funcionarios[i].cpf), arq);
        fread(funcionarios[i].data_nascimento, sizeof(char), sizeof(funcionarios[i].data_nascimento), arq);
        fread(&funcionarios[i].salario, sizeof(double), 1, arq);
    }

    // Perform insertion sort on the array
    for (int j = 1; j < tam; j++) {
        TFunc key = funcionarios[j];
        int i = j - 1;

        while (i >= 0 && funcionarios[i].cod > key.cod) {
            funcionarios[i + 1] = funcionarios[i];
            i--;
        }

        funcionarios[i + 1] = key;
    }

    // Write the sorted array back to the file
    
    fseek(arq, 0, SEEK_SET);
    for (int i = 0; i < tam; i++) {
        fwrite(&funcionarios[i].cod, sizeof(int), 1, arq);
        fwrite(funcionarios[i].nome, sizeof(char), sizeof(funcionarios[i].nome), arq);
        fwrite(funcionarios[i].cpf, sizeof(char), sizeof(funcionarios[i].cpf), arq);
        fwrite(funcionarios[i].data_nascimento, sizeof(char), sizeof(funcionarios[i].data_nascimento), arq);
        fwrite(&funcionarios[i].salario, sizeof(double), 1, arq);
    }

    free(funcionarios);

    printf("Debug: Insertion Sort Funcionarios Finalizado\n");
    fflush(arq);
}


