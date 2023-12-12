#include "livro.h"

// void shuffle_livro(int *vet, int size) {
//     srand(time(NULL));
//     for (int i = size - 1; i > 0; i--) {
//         int j = rand() % (i + 1);
//         int tmp = vet[j];
//         vet[j] = vet[i];
//         vet[i] = tmp;
//     }
// }

int tamanho_registro_livro() {
    return sizeof(TLivro);
}

int tamanho_arquivo_livro(FILE *Larquivo) {
    fseek(Larquivo, 0, SEEK_END);
    int tam = ftell(Larquivo) / tamanho_registro_livro();
    return tam;
}

TLivro *criar_livro(int id, char *titulo, char *autor) {
    
    TLivro *livro = (TLivro *) malloc(sizeof(TLivro));
    if (livro) memset(livro, 0, sizeof(TLivro));
    livro->id = id;
    strcpy(livro->titulo, titulo);
    strcpy(livro->autor, autor);

    return livro;
}

void salvaLivro(TLivro *livro, FILE *saida) {
    fwrite(livro, sizeof(TLivro), 1, saida);
}

TLivro *leLivro(FILE *entrada) {
    TLivro *livro = (TLivro *) malloc(sizeof(TLivro));
    if (0 >= fread(&livro->id, sizeof(int), 1, entrada)) {
        free(livro);
        return NULL;
    }
    fread(livro->titulo, sizeof(char), sizeof(livro->titulo), entrada);
    fread(livro->autor, sizeof(char), sizeof(livro->autor), entrada);
    return livro;
}

void imprimeLivro(TLivro *livro) {
    //printf("ID: %d\n", livro->id);
    //printf("Titulo: %s\n", livro->titulo);
    //printf("Autor: %s\n", livro->autor);
    //printf("Funcionario: %s\n", livro->funcionario->nome);

    printf("%-10d %-20s %-20s\n\n", livro->id, livro->titulo, livro->autor);
}

void criarBaseDeLivros(FILE *saida, int tamanho) {

    int vet[tamanho];
    TLivro *K;

    for (int i = 0; i < tamanho; i++)
        vet[i] = i + 1;

    shuffle(vet, tamanho);

    for (int i = 0; i < tamanho; i++) {
        K = criar_livro(vet[i], "Titulo", "Autor Desconhecido");
        salvaLivro(K, saida);
        free(K);
    }
}

void imprimirBaseDeLivros(FILE *saida) {
    
    system("cls");
    printf("\033[H\033[J");
    gotoxy(10,1);
    printf("\nImprimindo a base de dados de livros...\n\n");
    gotoxy(0,5);

    // if (saida == NULL) {
    //         printf("Erro ao abrir arquivo.\n");
    //         exit(1);
    //     }

        rewind(saida);
        TLivro *l;
        printf("%-10s %-20s %-20s\n\n", "ID", "Titulo", "Autor");

        while ((l = leLivro(saida)) != NULL)

            imprimeLivro(l);

        free(l);

}
