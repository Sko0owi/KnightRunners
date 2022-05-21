#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include "../Player/player.h"

void Create_Player(Attributes attributes)
{

    int x = PlayerStartX, y = PlayerStartY;
    MainPlayer.x = x;
    MainPlayer.y = y;

    MainPlayer.prevX = x;
    MainPlayer.prevY = y;

    MainPlayer.HP = 3;

    MainPlayer.HasKey = false;

    MainPlayer.Display = Create_Room('2',0,Create_Attributes(0,0,0));
    MainPlayer.WhereStanding = Map[y][x];
    Map[y][x] = MainPlayer.Display;

    MainPlayer.Attributes = attributes;
}
