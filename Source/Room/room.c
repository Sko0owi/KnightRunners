#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include "../Room/room.h"

Room Create_Room(char id, int EnemyID, Attributes EnemyAttributes)
{
    Room newRoom;

    Enemy newEnemy;
    newEnemy = Create_Enemy(EnemyID, EnemyAttributes);

    newRoom.ID = id;
    newRoom.Enemy = newEnemy;
    return newRoom;
}
