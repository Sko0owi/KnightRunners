#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include"../Map/map.h"
void Get_Map(int id)
{
    //id = 2;
    //g_print("TAKA MAPA MA BYC: %d\n",id);

    FILE * mapfile;

    char name[20];
    strcpy(name,"./bin/maps/map");
    char tmp[20];
    sprintf(tmp,"%d",id);
    strcat(name,tmp);
    strcat(name,".txt\0");


    if((mapfile=fopen(name,"r")) == NULL)
    {
        g_print("NIE MA TAKIEGO PLIKU\n");
        return;
    }


    fscanf(mapfile,"%d %d",&MapSizeX,&MapSizeY);

    //g_print("%d %d\n",MapSizeX,MapSizeY);

    fscanf(mapfile,"%d %d",&PlayerStartX,&PlayerStartY);

    //g_print("%d %d\n",PlayerStartX,PlayerStartY);


    for(int i = 1; i <= MapSizeY; i++)
    {
        char MapLength[MapSizeX + 1];
        fscanf(mapfile,"%s",MapLength);
        for(int j = 1; j <= MapSizeX; j++)
        {
            Map[i][j] = Create_Room(MapLength[j-1],0,Create_Attributes(0,0,0));
            //g_print("%c",Map[i][j].ID);
        }
        //g_print("\n");
    }

    char ile_specjal[200];
    fscanf(mapfile,"%s",ile_specjal);

    int n = atoi(ile_specjal);

    //g_print("SPECJALE%d\n",n);

    for(int i = 0 ; i < n ; i++)
    {
        int X,Y,EnemyType,EnemyStrength,EnemyAggility,EnemyInteligence;
        fscanf(mapfile,"%d %d %d %d %d %d",&X,&Y,&EnemyType,&EnemyStrength,&EnemyAggility,&EnemyInteligence);

        Map[Y][X] = Create_Room(Map[Y][X].ID,EnemyType,Create_Attributes(EnemyStrength,EnemyAggility,EnemyInteligence));
    }

    fclose(mapfile);
}

void Create_Map_GTK(GtkWidget *grid)
{
    for(int i = 1 ; i <= MapSizeY; i++)
    {
        for(int j = 1 ; j <= MapSizeX; j++)
        {
            char Display[2];
            Display[0] = '?';

            GtkWidget *label = gtk_label_new(Display);


            MapGtk[i][j] = label;


            gtk_grid_attach(GTK_GRID(grid), label, j, i, 1, 1);
            //gtk_widget_set_hexpand(label,GTK_ALIGN_CENTER);
        }
    }
}
