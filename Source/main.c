#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GameManager/gamemanager.h"


GtkWidget* Creating_MainWindow()
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window),"Knight Runners");

    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);

    gtk_widget_set_size_request(window, 400, 300);

    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

    return window;
}
GtkWidget* Creating_Grid_For_Board()
{
    GtkWidget *grid = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(grid), 2);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 2);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    return grid;
}
GtkWidget* Creating_Grid_For_Buttons()
{
    GtkWidget *grid = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(grid), 2);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 2);
    //gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    return grid;
}

void Creating_Buttons(GtkWidget *grid)
{

    GtkWidget *buttonUp = gtk_button_new_with_label("Up");
    GtkWidget *buttonLeft = gtk_button_new_with_label("Left");
    GtkWidget *buttonDown = gtk_button_new_with_label("Down");
    GtkWidget *buttonRight = gtk_button_new_with_label("Right");

    g_signal_connect(G_OBJECT(buttonUp), "clicked", G_CALLBACK(Changing_Room),(gpointer)"up");
    g_signal_connect(G_OBJECT(buttonLeft), "clicked", G_CALLBACK(Changing_Room),(gpointer)"left");
    g_signal_connect(G_OBJECT(buttonDown), "clicked", G_CALLBACK(Changing_Room),(gpointer)"down");
    g_signal_connect(G_OBJECT(buttonRight), "clicked", G_CALLBACK(Changing_Room),(gpointer)"right");

    gtk_grid_attach(GTK_GRID(grid), buttonUp, 5, MapSizeY + 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), buttonLeft, 4, MapSizeY + 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), buttonDown, 5, MapSizeY + 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), buttonRight, 6, MapSizeY + 2, 1, 1);
}
void Creating_Attribute_Label(GtkWidget *grid)
{
    char text[MAKS_DL];
    int Where = 10;

    strcpy(text,"S:");
    GtkWidget *labelS = gtk_label_new(text);
    gtk_grid_attach(GTK_GRID(grid),labelS,Where - 1,MapSizeY + 1,1,1);

    strcpy(text,"A:");
    GtkWidget *labelA = gtk_label_new(text);
    gtk_grid_attach(GTK_GRID(grid),labelA,Where - 1,MapSizeY + 2,1,1);

    strcpy(text,"I:");
    GtkWidget *labelI = gtk_label_new(text);
    gtk_grid_attach(GTK_GRID(grid),labelI,Where - 1,MapSizeY + 3,1,1);


    sprintf(text,"%d",MainPlayer.Attributes.Strength);
    labelS = gtk_label_new(text);
    gtk_grid_attach(GTK_GRID(grid),labelS,Where,MapSizeY + 1,1,1);
    StrengthLabel = labelS;

    sprintf(text,"%d",MainPlayer.Attributes.Agillity);
    labelA = gtk_label_new(text);
    gtk_grid_attach(GTK_GRID(grid),labelA,Where,MapSizeY + 2,1,1);
    AgillityLabel = labelA;

    sprintf(text,"%d",MainPlayer.Attributes.Inteligence);
    labelI = gtk_label_new(text);
    gtk_grid_attach(GTK_GRID(grid),labelI,Where,MapSizeY + 3,1,1);
    InteligenceLabel = labelI;
}
void Creating_HP_Label(GtkWidget *grid)
{
    char text[MAKS_DL];

    strcpy(text,"HP: ");

    char tmp[MAKS_DL];
    sprintf(tmp,"%d",MainPlayer.HP);
    strcat(text,tmp);
    GtkWidget *label = gtk_label_new(text);
    gtk_grid_attach(GTK_GRID(grid),label,1,MapSizeY + 1,1,1);

    HPLabel = label;

}
void Creating_Search_Room_Button(GtkWidget *grid)
{

    GtkWidget *ButtonSearchRoom = gtk_button_new_with_label("Eksploruj Pokój");
    g_signal_connect(G_OBJECT(ButtonSearchRoom), "clicked", G_CALLBACK(Search_Room),(gpointer)"up");
    gtk_grid_attach(GTK_GRID(grid),ButtonSearchRoom,1,MapSizeY + 2,1,1);


}
int main(int argc, char*argv[])
{
    srand(time(NULL));

    if ((potoki=initPipes(argc,argv)) == NULL)
        return 1;
    if (argc == 2 && strcmp(argv[1],"A") == 0) { twoj_id="B"; moj_id="A"; }
    else { moj_id="B"; twoj_id="A"; }


    gtk_init(&argc, &argv);

    window = Creating_MainWindow();


    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box1);


    GtkWidget *gridBoard = Creating_Grid_For_Board();


    Init_Game(gridBoard);

    gtk_box_pack_start(GTK_BOX(box1), gridBoard, TRUE, TRUE, 0);

    GtkWidget *gridButtons = Creating_Grid_For_Buttons();




    Creating_Buttons(gridButtons);

    Creating_Attribute_Label(gridButtons);

    Creating_HP_Label(gridButtons);

    Creating_Search_Room_Button(gridButtons);

    gtk_box_pack_end(GTK_BOX(box1), gridButtons, TRUE, TRUE, 0);

    Update_Grid();

    g_timeout_add(10,Get_Turn_Info_From_Pipe,NULL);

    gtk_widget_show_all(window);
    gtk_main();
}

