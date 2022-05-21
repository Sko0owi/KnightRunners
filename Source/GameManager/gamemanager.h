#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Player/player.h"
#include "../Fifo/fifo.h"

#define MAKS_DL 200

//GTK Widgets (UI)
GtkWidget *HPLabel;
GtkWidget *window;

GtkWidget *StrengthLabel;
GtkWidget *AgillityLabel;
GtkWidget *InteligenceLabel;


int WhichStatUpdated;


bool GameEnded;
int HowGameEnded;
bool WaitingForOtherPlayer;

GtkWidget *window;
char *moj_id, *twoj_id;

// Fifo
PipesPtr potoki;
void Send_Turn_Info_To_Pipe();
gboolean Get_Turn_Info_From_Pipe(gpointer data);
void Pick_Map();

//Turn Managment
int TurnHappened[2000];
bool DidMoveInTurn[2000];
int Turn;
bool ChangedInMyTurn;

//GtkStuff
void Show_Error(char *komunikat);
void Show_Communicate(char message[]);
int Show_Room_Communicate(int id);
void End_Game(char message[]);

void HP_Loss();


//Start Game or Updating
void Init_Game();
void Update_Grid();
void Update_Attributes();
void Update_Stats(int id);
void Changing_Room(GtkWidget *widget, gpointer*data);

void Redo_Player_Move();


//Interacting with Rooms
void Room_With_Enemy();
void Search_Room(GtkWidget *widget, gpointer*data);


//Starting Screen
Attributes Pick_Class();

//Functions for buttons
void Fight_Enemy(GtkWidget *widget, gpointer dialog);
void Pass_Enemy(GtkWidget *widget, gpointer dialog);
void Escape_Enemy(GtkWidget *widget, gpointer dialog);

void Warrior_Choosed(GtkWidget *widget, gpointer dialog);
void Thief_Choosed(GtkWidget *widget, gpointer dialog);
void Mage_Choosed(GtkWidget *widget, gpointer dialog);

