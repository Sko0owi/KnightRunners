#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include "../Enemy/enemy.h"

char RoomDisplay[10];


typedef struct room
{
    char ID;
    Enemy Enemy;
} Room;

Room Create_Room(char id, int EnemyID, Attributes EnemyAttributes);
