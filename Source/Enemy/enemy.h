#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<gtk/gtk.h>

#include"../Attributes/attributes.h"

typedef struct enemy
{
    int EnemyID;
    Attributes Attributes;
    bool Defeated;

} Enemy;

Enemy Create_Enemy(int ID, Attributes attributes);
