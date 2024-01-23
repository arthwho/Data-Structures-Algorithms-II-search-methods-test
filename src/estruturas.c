#include "estruturas.h"

/*************************************************
 * Defines and utils
**************************************************/

void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}

/**************************************************************************************************
 * Funções de manipulação de funcionários
**************************************************************************************************/

// Retorna tamanho do funcionario em bytes
int tamanho_registro() {
    return sizeof(TFunc);
}

int tamanho_arquivo(FILE *arquivo) {
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1; // Indica erro
    }

    fseek(arquivo, 0, SEEK_END); // Move o cursor para o final do arquivo
    long tamanho_total = ftell(arquivo); 

    if (tamanho_total == -1) {
        perror("Erro ao obter o tamanho do arquivo");
        fclose(arquivo);
        return -1;
    }

    int num_registros = tamanho_total / tamanho_registro();

    fclose(arquivo);
    return num_registros;
}

// Cria funcionario.
TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario) {
    
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (!func) {
        perror("Erro ao alocar memória para funcionário");
        exit(EXIT_FAILURE);
    }
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
    fwrite(func, sizeof(TFunc), 1, out);
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
    TFunc *Z;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet, tam);

    printf("\nGerando a base de dados de funcionarios...\n");

    for (int i = 0; i < tam; i++) {
    Z = funcionario(i, "A", "000-XXXX-000", "01/01/1980", 0 * i);
    salva(Z, out);
    free(Z);  // Libera a cada iteração para evitar vazamento de memória
    }
}

//embaralha base de dados
void shuffle(int *vet, int size) {
    srand(time(NULL));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}


void imprimirBase(FILE *out){

printf("\033[H\033[J");
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


/*************************************************
 * Funções de manipulação de livros
**************************************************/

int tamanho_registro_livro() {
    return sizeof(TLivro);
}

int tamanho_arquivo_livro(FILE *Larquivo) {
    if (Larquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1; // Indica erro
    }

    fseek(Larquivo, 0, SEEK_END); // Move o cursor para o final do arquivo
    long tamanho_total = ftell(Larquivo); 

    if (tamanho_total == -1) {
        perror("Erro ao obter o tamanho do arquivo");
        fclose(Larquivo);
        return -1;
    }

    int num_registros = tamanho_total / tamanho_registro_livro();

    fclose(Larquivo);
    return num_registros;
}

TLivro *criar_livro(int id, char *titulo, char *autor, TFunc *func) {
    TLivro *livro = (TLivro *) malloc(sizeof(TLivro));
    TFunc *funcionario = (TFunc *) malloc(sizeof(TFunc));
    if (livro) memset(livro, 0, sizeof(TLivro));
    livro->id = id;
    strcpy(livro->titulo, titulo);
    strcpy(livro->autor, autor);
    strcpy(livro->funcionario->nome, func->nome);

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
    fread(&livro->funcionario, sizeof(TFunc), 1, entrada);
    return livro;
}

//Imprime um livro
void imprimeLivro(TLivro *j) {
    //printf("ID: %d\n", livro->id);
    //printf("Titulo: %s\n", livro->titulo);
    //printf("Autor: %s\n", livro->autor);
    //printf("Funcionario: %s\n", livro->funcionario->nome);
    
    printf("%-10d %-20s %-20s %-10s\n\n", j->id, j->titulo, j->autor, j->funcionario->nome);
}

void criarBaseDeLivros(FILE *saida, int tamanho) {

    int vet[tamanho];
    TLivro *K;
    TFunc *funcionario = (TFunc *) malloc(sizeof(TFunc));

    for (int i = 0; i < tamanho; i++)
        vet[i] = i + 1;

    shuffle(vet, tamanho);

    for (int i = 0; i < tamanho; i++) {
        K = criar_livro(vet[i], "Titulo", "Autor Desconhecido", funcionario);
        salvaLivro(K, saida);
    }

    free(K);
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
        printf("%-10s %-20s %-20s %-10s\n\n", "ID", "Titulo", "Autor", "Funcionario");

        while ((l = leLivro(saida)) != NULL)

            imprimeLivro(l);

        free(l);

}