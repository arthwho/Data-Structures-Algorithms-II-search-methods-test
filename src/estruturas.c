#include "estruturas.h"

/*************************************************
 * Defines and utils
**************************************************/

void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}

int compare(const void *a, const void *b) {
    int num1 = *(int *)a;
    int num2 = *(int *)b;
    return num1 - num2;
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

// Cria a base de dados
void criarBase(FILE *out, int tam){

    int vet[tam];
    TFunc *Z;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet, tam);

    printf("\nGerando a base de dados de funcionarios...\n");

    for (int i = 0; i < tam; i++) {
    Z = funcionario(vet[i], "A B da Silva", "000-XXXX-000", "01/01/1980", 0 * i);
    salva(Z, out);
    free(Z);  // Libera a cada iteração para evitar vazamento de memória
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

TLivro *criar_livro(int id, char *titulo, char *autor) {
    TLivro *livro = (TLivro *) malloc(sizeof(TLivro));
    TFunc *funcionario = (TFunc *) malloc(sizeof(TFunc));
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
    TLivro *K = (TLivro *) malloc(sizeof(TLivro));
    TFunc *funcionario = (TFunc *) malloc(sizeof(TFunc));

    funcionario->cod = 1;
    strcpy(funcionario->nome, "A B da Silva");
    strcpy(funcionario->cpf, "000-XXXX-000");
    strcpy(funcionario->data_nascimento, "01/01/1980");
    funcionario->salario = 0;

    for (int i = 0; i < tamanho; i++)
        vet[i] = i + 1;

    shuffle(vet, tamanho);

    for (int i = 0; i < tamanho; i++) {
        K = criar_livro(vet[i], "Titulo", "Autor Desconhecido");
        K->funcionario = funcionario;
        salvaLivro(K, saida);
        free(K);
    }

    //free(funcionario);
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
        TLivro *l = (TLivro *) malloc(sizeof(TLivro));
        printf("%-10s %-20s %-20s %-10s\n\n", "ID", "Titulo", "Autor", "Funcionario");

        while (fread(l, sizeof(TLivro), 1, saida))

            imprimeLivro(l);

        free(l);

}


/*************************************************
 * Funcoes de classificacao
**************************************************/

void classificacao_interna_Func(char* filename, int size) {
    char buf[size];
    int i = 0;
    FILE* source = fopen(filename, "rb");
    if (source == NULL) {
        printf("Arquivo fonte nao encontrado.\n");
        return;
    }
    while (!feof(source)) {
        char newFilename[64];
        sprintf(newFilename, "./src/bin/partitions/partition%d.txt", i);
        FILE* dest = fopen(newFilename, "wb");
        if (dest == NULL) {
            printf("Pasta destino nao encontrada.\n");
            return;
        }
        size_t count = fread(buf, 1, size, source);
        fwrite(buf, 1, count, dest);
        fclose(dest);
        i++;
    }
    fclose(source);
}

void classificacao_interna_livro(char* filename, int size) {
    char buf[size];
    int i = 0;
    FILE* source = fopen(filename, "rb");
    if (source == NULL) {
        printf("Arquivo fonte nao encontrado.\n");
        return;
    }
    size_t count;
    while ((count = fread(buf, 1, size, source)) > 0) {
        char newFilename[64];
        sprintf(newFilename, "./src/bin/partitions/partitionB%d.txt", i);
        FILE* dest = fopen(newFilename, "wb");
        if (dest == NULL) {
            printf("Pasta destino nao encontrada.\n");
            return;
        }
        fwrite(buf, 1, count, dest);
        fclose(dest);
        i++;
    }
    fclose(source);
}


/*************************************************
 * Funcoes hash
**************************************************/

int hash(int key) {
    return key % TABLE_SIZE;
}

// Inserir elemento

void insert_hash(HashTable *ht, int key, TLivro livro) {
    int index = hash(key);

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->livro = livro;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;

    printf("\nLivro inserido na tabela %d\n", index);
}

// Buscar elemento
TLivro search_hash(HashTable *ht, int key) {
    int index = hash(key);
    Node *node = ht->table[index];
    while (node != NULL) {
        if (node->key == key) {
            printf("Livro encontrado na tabela %d\n", index);
            return node->livro;
        }
        node = node->next;
    }

    // Retorna uma estrutura de livro com código -1 se não encontrado
    TLivro notFound;
    notFound.id = -1;
    return notFound;
}

// Remover elemento
void remove_hash(HashTable *ht, int key) {
    int index = hash(key);
    Node *node = ht->table[index];
    Node *prev = NULL;
    while (node != NULL) {
        if (node->key == key) {
            if (prev == NULL) {
                ht->table[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node);
            printf("Livro removido com sucesso.\n");
            return;
        }
        prev = node;
        node = node->next;
    }

    printf("Livro com código [%d] não encontrado.\n", key);
}

// Salvar tabela hash em um arquivo
void saveHashTable(HashTable *ht) {
    FILE *file = fopen(HASH_TABLE_PATH, "wb");
    if (file == NULL) {
        printf("[+] Debug: Não foi possível abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *node = ht->table[i];
        while (node != NULL) {
            fwrite(&(node->key), sizeof(int), 1, file);
            fwrite(&(node->livro), sizeof(TLivro), 1, file);
            node = node->next;
        }
    }

    fclose(file);
}

// Ler tabela hash de um arquivo
HashTable *loadHashTable() {
    FILE *file = fopen(HASH_TABLE_PATH, "rb");
    if (file == NULL) {
        printf("[+] Debug: Não foi possível abrir o arquivo.\n");
        return NULL;
    }

    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }

    int key;
    TLivro livro;
    while (fread(&key, sizeof(int), 1, file) && fread(&livro, sizeof(TLivro), 1, file)) {
        insert_hash(ht, key, livro);
    }

    fclose(file);
    return ht;
}

HashTable *createHashTable() {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}