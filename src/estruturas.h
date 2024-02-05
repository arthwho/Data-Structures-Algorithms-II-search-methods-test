/*************************************************
 * 
 * modulo: estruturas.h
 * 
 * 
**************************************************/

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <conio.h>


/*************************************************
 * Defines and utils
**************************************************/

#define TABLE_SIZE 17 // hash table divisor
#define EMPLOYEE_FILE_PATH "src/bin/window_employee.dat"
#define PARTITIONS_PATH "src/bin/partitions"
#define BOOK_FILE_PATH "src/bin/window_books.dat"
#define LOG_FILE_PATH "src/bin/window_log.dat"
#define INDEX_FILE_PATH "src/bin/window_index.dat"
#define HASH_TABLE_PATH "src/bin/hashTable.dat" // Path da tabela hash
#define PARTITIONS_PER_STRUCTS 10
int NUM_PARTITIONS;
int INT_MAX;

void gotoxy(int x,int y);
int compare(const void *a, const void *b);

/*************************************************
 * Structs
**************************************************/

typedef struct funcionario{
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

typedef struct livro{
    int id;
    char titulo[50];
    char autor[50];
    TFunc *funcionario;
} TLivro;

typedef enum {
    FUNCIONARIO,
    LIVRO
} TipoRegistro;

typedef struct{

    float tempo;
    int num_registro_per_partition;
    int num_partitions;
} intercalacao_otima_struct;

typedef struct{

    float tempo;
    int num_registro_per_partition;
    int num_partitions;
} classificacao_struct;


typedef struct LogFileBinary{
    int iteracoes;
    double tempo_ms;
} TLogBinary;

typedef struct {
    int key;
    long position;
} Index;

// Nó para a lista encadeada
typedef struct Node {
    int key;
    TLivro livro;
    struct Node *next;
} Node;

// Tabela Hash
typedef struct HashTable {
    Node *table[TABLE_SIZE];
} HashTable;


/*************************************************
 * Funcoes de Funcionario
**************************************************/

int tamanho_registro();
int tamanho_arquivo(FILE *arquivo);

TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario);
TFunc *le(FILE *in);

void salva(TFunc *func, FILE *out);
void imprime(TFunc *func);
void shuffle(int *vet, int size);
void criarBase(FILE *out, int tam);
void imprimirBase(FILE *out);


/*************************************************
 * Funcoes de Livro
**************************************************/

int tamanho_registro_livro();
int tamanho_arquivo_livro(FILE *arquivo);

TLivro *livro(int id, char *titulo, char *autor, TFunc *funcionario);
TLivro *criar_livro(int id, char *titulo, char *autor);
TLivro *leLivro(FILE *entrada); // Ler o funcionario

void salvaLivro(TLivro *livro, FILE *saida); // Salvar o funcionario
void imprimeLivro(TLivro *livro); // Imprimir o funcionario
void criarBaseDeLivros(FILE *saida, int tamanho); // Incluir o funcionario
void shuffle_livro(int *vet, int size); // Muda se precisar
void imprimirBaseDeLivros(FILE *saida); // Mudar


/*************************************************
 * Funcoes de busca
**************************************************/

TFunc *buscarFuncionario_binariamente(int chave, FILE *arquivo, int tam, FILE *LogFileBinary);
TFunc *buscaSequencial(int chave, FILE *in);
TLivro *buscarLivro_binariamente(int chave, FILE *arquivo, int tam, FILE *LogFileBinary);

void salvar_log_file_binary(FILE *out, int iteracoes, double tempo_ms);


/*************************************************
 * Funcoes de ordenação
**************************************************/

void insertionSort(FILE *arq, int tam);
void insertionSort_livros(FILE *arq, int tam);

void quicksort_employees(FILE *arq, int tam);
void quicksort_books(FILE *arq, int tam);
void quicksort_both();
void printLivroCodes(FILE *arq, int tam);
void printFuncCodes(FILE *Larq, int tam);


/*************************************************
 * Funcoes de intercalacao
**************************************************/

int compare_records(const void *a, const void *b, TipoRegistro tipo);

intercalacao_otima_struct* save_intercalacao_otima_struct(int num_partitions, int num_registro_per_partition, float tempo);

void intercalacao_otima_Func();
void intercalacao_otima_Livro();
void intercalacoes_otimas();


/*************************************************
 * Funcoes de classificacao
**************************************************/

void classificacao_interna_Func(char* filename, int size);
void classificacao_interna_livro(char* filename, int size);
void classificacoes(int M);


/*************************************************
 * Funcoes hash
**************************************************/


int hash(int key);
void insert_hash(HashTable *ht, int key, TLivro livro);
TLivro search_hash(HashTable *ht, int key);
void remove_hash(HashTable *ht, int key);
void saveHashTable(HashTable *ht);
HashTable *loadHashTable();
void printLivroInfo(TLivro livro);
HashTable *createHashTable();

#define MY_HASH_TABLE_SIZE 10
HashTable *myHashTable;
#endif // ESTRUTURAS_H