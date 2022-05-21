#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<gtk/gtk.h>
#include "../Attributes/attributes.h"

Attributes Create_Attributes(int S, int A, int I)
{
    Attributes newAttributes;
    newAttributes.Strength = S;
    newAttributes.Agillity = A;
    newAttributes.Inteligence = I;
    return newAttributes;
}
