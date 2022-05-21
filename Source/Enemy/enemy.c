#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<gtk/gtk.h>

#include "../Enemy/enemy.h"

Enemy Create_Enemy(int ID, Attributes attributes)
{
    Enemy newEnemy;
    newEnemy.EnemyID = ID;
    newEnemy.Defeated = false;
    newEnemy.Attributes = attributes;
    return newEnemy;
}
