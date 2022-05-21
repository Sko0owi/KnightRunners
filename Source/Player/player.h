#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<gtk/gtk.h>
#include "../Map/map.h"

typedef struct player
{
    int x, y;
    int prevX, prevY;
    int HP;
    bool HasKey;
    Room WhereStanding;
    Room Display;
    Attributes Attributes;
} Player;

Player MainPlayer;

void Create_Player(Attributes attributes);

