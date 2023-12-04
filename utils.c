#include "utils.h"
#include <stdio.h>

//Fun��o que define para onde o cursor vai escrever na tela
void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}
