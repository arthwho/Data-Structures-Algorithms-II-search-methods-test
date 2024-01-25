#include "estruturas.h"

void insertionSort(FILE *arq, int tam) {
    TFunc *funcionarios = (TFunc *)malloc(tam * sizeof(TFunc));
    arq = fopen("funcionario.dat", "r+b");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }
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

    //printf("Debug: Insertion Sort Funcionarios Finalizado\n");
    fflush(arq);
}

void insertionSort_livros(FILE *arq, int tam) {
    // Allocate memory for an array of TLivro structures
    TLivro *livros = (TLivro *)malloc(tam * sizeof(TLivro));

    arq = fopen(BOOK_FILE_PATH, "r+b");

    // Read all records into an array
    fseek(arq, 0, SEEK_SET);
    for (int i = 0; i < tam; i++) {
        fread(&livros[i], sizeof(TLivro), 1, arq);
    }

    // Filter out books with invalid IDs
    int validCount = 0;
    for (int i = 0; i < tam; i++) {
        if (livros[i].id > 0 && livros[i].id <= tam) {
            livros[validCount] = livros[i];
            validCount++;
        }
    }

    // Perform insertion sort on the array
    for (int j = 1; j < validCount; j++) {
        TLivro key = livros[j];
        int i = j - 1;

        while (i >= 0 && livros[i].id > key.id) {
            livros[i + 1] = livros[i];
            i--;
        }

        livros[i + 1] = key;
    }

    arq = fopen(BOOK_FILE_PATH, "w+b");

    // Write the sorted array back to the file
    fseek(arq, 0, SEEK_SET);
    for (int i = 0; i < validCount; i++) {
        fwrite(&livros[i], sizeof(TLivro), 1, arq);
    }

    // Free the array of TLivro structures
    free(livros);

    // Flush changes to the file
    fflush(arq);

    printf("Debug: Insertion Sort Livros Finalizado\n");
}
