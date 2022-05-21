#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <string.h>
#include<gtk/gtk.h>


typedef struct attributes
{
    int Strength, Agillity, Inteligence;
} Attributes;

Attributes Create_Attributes(int S, int A, int I);

