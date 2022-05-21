#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "../Player/player.h"

GtkWidget *HPLabel;
GtkWidget *window;

GtkWidget *StrengthLabel;
GtkWidget *AgillityLabel;
GtkWidget *InteligenceLabel;

void GUI_init();

void CreatingButtons(GtkWidget *grid);

void CreateAttributeLabel(GtkWidget *grid);

void CreateHPLabel(GtkWidget *grid);

void CreateSearchRoom(GtkWidget *grid);

void Create_Map_GTK(GtkWidget *grid);

void Update_Grid();


GtkWidget* CreatingGrid();

GtkWidget* CreatingMainWindow();
