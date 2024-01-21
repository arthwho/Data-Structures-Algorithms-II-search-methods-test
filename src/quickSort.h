#ifndef INSERTIONSORT_H_INCLUDED
#define INSERTIONSORT_H_INCLUDED
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include "funcionario.h"
#include "livro.h"

void quicksort_employees(FILE *arq, int tam);
void quicksort_books(FILE *arq, int tam);
void quicksort_both();
void printLivroCodes(FILE *arq, int tam);
void printFuncCodes(FILE *Larq, int tam);

#endif // INSERTIONSORT_H_INCLUDED