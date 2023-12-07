#include "livro.h"

void shuffle_livro(int *vet, int size) {
    srand(time(NULL));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

int tamanho_registro_livro() {
    return sizeof(TLivro);
}

int tamanho_arquivo_livro(FILE *Larquivo) {
    fseek(Larquivo, 0, SEEK_END);
    int tam = ftell(Larquivo) / tamanho_registro_livro();
    return tam;
}

TLivro *criar_livro(int id, char *titulo, char *autor, TFunc funcionario) {
    
    TLivro *livro = (TLivro *) malloc(sizeof(TLivro));
    if (livro) memset(livro, 0, sizeof(TLivro));
    livro->id = id;
    strcpy(livro->titulo, titulo);
    strcpy(livro->autor, autor);

    livro->funcionario = funcionario;
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

    printf("%-10d %-20s %-20s %-10s\n\n", livro->id, livro->titulo, livro->autor, livro->funcionario.nome);
}

void criarBaseDeLivros(FILE *saida, int tamanho) {

    int vet[tamanho];
    TLivro *livro;
    TFunc *f /*= (TFunc *) malloc(sizeof(TFunc))*/;


    f = funcionario(1, "Funcionario", "000.000.000-00", "01/01/2000", 1000);
    salva(f, saida);

    for (int i = 0; i < tamanho; i++)
        vet[i] = i + 1;

    shuffle_livro(vet, tamanho);

    for (int i = 0; i < tamanho; i++) {
        livro = criar_livro(vet[i], "Titulo", "Autor Desconhecido", *f);
        salvaLivro(livro, saida);
    }
    free(livro);
}

void imprimirBaseDeLivros(FILE *saida) {

    if (saida == NULL) {
            printf("Erro ao abrir arquivo.\n");
            exit(1);
        }

    printf("\033[H\033[J");
    gotoxy(10,1);
    printf("\nImprimindo a base de dados de livros...\n\n");
    gotoxy(0,5);

        rewind(saida);
        TLivro *l;
        printf("%-10s %-20s %-20s %-10s\n\n", "ID", "Titulo", "Autor", "Funcionario");

        while ((l = leLivro(saida)) != NULL)

            imprimeLivro(l);

        free(l);

}
