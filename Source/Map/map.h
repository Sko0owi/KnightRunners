#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include<gtk/gtk.h>
#include "../Room/room.h"

#define MAX_MAP_SIZE 100
//int MapSize = 20;

int PlayerStartX, PlayerStartY;
int MapSizeX, MapSizeY;

Room Map[MAX_MAP_SIZE+1][MAX_MAP_SIZE+1];

GtkWidget*MapGtk[MAX_MAP_SIZE + 1][MAX_MAP_SIZE + 1];

void Get_Map(int id);

void Create_Map_GTK(GtkWidget *grid);
