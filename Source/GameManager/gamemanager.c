#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../GameManager/gamemanager.h"

//FIFO
void Send_Turn_Info_To_Pipe(int TurnNumber)
{
    gchar entry[MAKS_DL];

    sprintf(entry,"%d",TurnNumber);
    strcat(entry,"\n");

    sendStringToPipe(potoki, entry);


    if(TurnNumber == -1)
    {
        GameEnded = true;
        HowGameEnded --;
    } else if(TurnNumber == 0)
    {
        GameEnded = true;
        HowGameEnded ++;
    } else
    {
        TurnHappened[TurnNumber] ++;

        if(TurnHappened[TurnNumber] == 2)
        {
            WaitingForOtherPlayer = 0;
            ChangedInMyTurn = 1;
            Turn++;
        }
    }
}
gboolean Get_Turn_Info_From_Pipe(gpointer data)
{
    gchar entry[MAKS_DL];

    if (getStringFromPipe(potoki,entry,MAKS_DL))
    {

        int tmp_turn = atoi(entry);


        if(tmp_turn == -1)
        {
            GameEnded = true;
            HowGameEnded++;
        } else if(tmp_turn == 0)
        {
            GameEnded = true;
            HowGameEnded--;
        } else
        {
            TurnHappened[tmp_turn] ++;
            if(TurnHappened[tmp_turn] == 2)
            {
                WaitingForOtherPlayer = 0;
                Update_Grid();
                Turn++;

            }
        }
    }
    if(GameEnded == true)
    {
        sleep(2);
        if (getStringFromPipe(potoki,entry,MAKS_DL))
        {
            int tmp_turn = atoi(entry);
            if(tmp_turn == -1)
            {
                HowGameEnded++;
            }
            if(tmp_turn == 0)
            {
                HowGameEnded--;
            }
        }
        if(HowGameEnded == -1)
        {
            End_Game("Przegrałeś!");

        } else if(HowGameEnded == 0)
        {
            End_Game("Zremisowałeś!");

        } else if(HowGameEnded == 1)
        {
            End_Game("Wygrałeś!");

        }
    }
  return TRUE;
}
void Pick_Map()
{
    if(strcmp(moj_id,"A") == 0)
    {
        int RandomInteger = rand()%3;

        Get_Map(RandomInteger + 1);

        gchar entry[MAKS_DL];
        sprintf(entry,"%d",RandomInteger + 1);
        strcat(entry,"\n");

        sendStringToPipe(potoki, entry);
    } else
    {
        gchar entry[MAKS_DL];
        while(true)
        {
            if (getStringFromPipe(potoki,entry,MAKS_DL))
            {
                int MapID = atoi(entry);
                Get_Map(MapID);
                break;
            }
        }

    }
}
//GtkCommunicates
void Show_Error(char *komunikat)
{
    GtkWidget *dialog;
    dialog=gtk_message_dialog_new (GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,
				   GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"%s",komunikat);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}
int Show_Room_Communicate(int id)
{
    if(id == 0)
    {
        return 0;
    }
    char message[MAKS_DL];
    if(id == 4)
    {

        strcpy(message,"Wchodzisz do pokoju i wygląda jak biblioteka! Przeszukanie tego miejsca to dobry pomysł!");
        Show_Communicate(message);
        return 0;
    }
    if(id == 5)
    {
        strcpy(message,"Wchodzisz do pokoju i wygląda jak pokój klucznika! Pewnie gdzieś zostawił klucz do komnaty księżniczki!");

        Show_Communicate(message);
        return 0;
    }
    strcpy(message,"Wchodzisz do pokoju i czujesz jak patrzy na ciebie ");
    if(id == 1)
    {
        strcat(message, "Wojownik!");
    } else if(id == 2)
    {
        strcat(message, "Zabójca!");
    } else if(id == 3)
    {
        strcat(message, "Mag!");
    }

    GtkWidget *dialog;
    char ButtonFirstName[2000];
    strcpy(ButtonFirstName,"Walcz z przeszkodą!");

    char ButtonSecondName[2000];
    strcpy(ButtonSecondName,"Spróbuj ominąć przeszkodę!");

    char ButtonThirdName[2000];
    strcpy(ButtonThirdName,"Wycofaj się skąd przybyłeś!");

    dialog=gtk_dialog_new();

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_container_set_border_width(GTK_CONTAINER(content_area),45);


    GtkWidget *label = gtk_label_new(message);
    gtk_label_set_line_wrap(GTK_LABEL(label),(gboolean)(TRUE));

    gtk_container_add(GTK_CONTAINER(content_area),label);

    GtkWidget *ButtonFirst = gtk_button_new_with_label(ButtonFirstName);
    GtkWidget *ButtonSecond = gtk_button_new_with_label(ButtonSecondName);
    GtkWidget *ButtonThird = gtk_button_new_with_label(ButtonThirdName);

    g_signal_connect(G_OBJECT(ButtonFirst), "clicked", G_CALLBACK(Fight_Enemy),(gpointer)dialog);
    g_signal_connect(G_OBJECT(ButtonSecond), "clicked", G_CALLBACK(Pass_Enemy),(gpointer)dialog);
    g_signal_connect(G_OBJECT(ButtonThird), "clicked", G_CALLBACK(Escape_Enemy),(gpointer)dialog);

    gtk_container_add(GTK_CONTAINER(content_area),ButtonFirst);

    gtk_container_add(GTK_CONTAINER(content_area),ButtonSecond);

    gtk_container_add(GTK_CONTAINER(content_area),ButtonThird);

    gtk_widget_show_all(dialog);



    gint Response = -1;

    while(Response < 0) Response = gtk_dialog_run (GTK_DIALOG (dialog));

    gtk_widget_destroy (dialog);


    return Response;
}
void Show_Communicate(char message[])
{
    GtkWidget *dialog;
    dialog=gtk_message_dialog_new (GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"%s",message);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}
void End_Game(char message[])
{
    Show_Communicate(message);
    gtk_main_quit();
}
void Update_Stats(int id)
{
    char message[MAKS_DL];
    strcpy(message,"Zwiększono ");

    if(id == 0)
    {
        strcat(message,"Siłę!");
    } else if(id == 1)
    {
        strcat(message,"Zręczność!");
    } else if(id == 2)
    {
        strcat(message,"Inteligencję!");
    }
    Show_Communicate(message);
}


//Game Update/init
void Init_Game(GtkWidget *grid)
{
    RoomDisplay[0] = 'R';
    RoomDisplay[1] = 'W';
    RoomDisplay[2] = 'Y';
    RoomDisplay[3] = 'K';
    RoomDisplay[5] = 'P';


    Attributes PlayerClass;
    PlayerClass = Pick_Class();

    WhichStatUpdated = -1;

    GameEnded = false;
    HowGameEnded = 0;

    WaitingForOtherPlayer = 0;
    ChangedInMyTurn = 0;

    Turn = 1;

    Pick_Map();

    Create_Map_GTK(grid);
    Create_Player(PlayerClass);

}
void Update_Grid()
{
    if(MainPlayer.WhereStanding.ID == '5')
    {
        if(MainPlayer.HasKey == false)
        {
            Show_Communicate("Nie posiadasz klucza, by otworzyć komnatę księżniczki!");
            Redo_Player_Move();
        } else
        {
            Send_Turn_Info_To_Pipe(0);          // win
        }

    }


    Update_Attributes();
    if(WhichStatUpdated != -1)
    {
        Update_Stats(WhichStatUpdated);       // sprawdza czy jakas stata sie nie zmienia
        WhichStatUpdated = -1;
    }

    sleep(0.5f);

    if(GameEnded != true && (MainPlayer.x != MainPlayer.prevX || MainPlayer.y != MainPlayer.prevY))
    {
        Room_With_Enemy();
    }

    //g_print("PO FUNKCJI: %d\n",MainPlayer.WhereStanding.Enemy.Defeated);

    int x = MainPlayer.x, y = MainPlayer.y;

    char buffer[MAKS_DL];

    int id = Map[y][x].ID-'0';

    buffer[0] = RoomDisplay[id];
    buffer[1] = '\0';

    gtk_label_set_text(GTK_LABEL(MapGtk[y][x]),buffer);

    char *format;
    gchar *markup;
    format="<span font_size =\"larger\" bgcolor =\"#00FF00\" underline =\"single\" >%s</span>";
    markup=g_markup_printf_escaped(format,buffer);

    gtk_label_set_markup(GTK_LABEL(MapGtk[y][x]), markup);

    int ChangeX = 0, ChangeY = 0;
    if(x > 1)
    {
        ChangeX = -1;

        int id = Map[y+ChangeY][x+ChangeX].ID-'0';

        buffer[0] = RoomDisplay[id];
        buffer[1] = '\0';

        if(Map[y+ChangeY][x+ChangeX].ID == '1')
        {
            format="<span font_size =\"larger\" bgcolor =\"#8a8a8a\">%s</span>";
        } else if(Map[y+ChangeY][x+ChangeX].ID == '5')
        {
            format="<span font_size =\"larger\" bgcolor =\"#ad9f00\">%s</span>";
        } else
        {
            format="<span font_size =\"larger\" bgcolor =\"#b3e6a5\">%s</span>";
        }

        markup=g_markup_printf_escaped(format,buffer);



        gtk_label_set_text(GTK_LABEL(MapGtk[y+ChangeY][x+ChangeX]),buffer);

        gtk_label_set_markup(GTK_LABEL(MapGtk[y+ChangeY][x+ChangeX]), markup);
        ChangeX = 0;
    }
    if(x < MapSizeX)
    {
        ChangeX = 1;

        int id = Map[y+ChangeY][x+ChangeX].ID-'0';

        buffer[0] = RoomDisplay[id];
        buffer[1] = '\0';

        if(Map[y+ChangeY][x+ChangeX].ID == '1')
        {
            format="<span font_size =\"larger\" bgcolor =\"#8a8a8a\">%s</span>";
        } else if(Map[y+ChangeY][x+ChangeX].ID == '5')
        {
            format="<span font_size =\"larger\" bgcolor =\"#ad9f00\">%s</span>";
        } else
        {
            format="<span font_size =\"larger\" bgcolor =\"#b3e6a5\">%s</span>";
        }

        markup=g_markup_printf_escaped(format,buffer);



        gtk_label_set_text(GTK_LABEL(MapGtk[y+ChangeY][x+ChangeX]),buffer);

        gtk_label_set_markup(GTK_LABEL(MapGtk[y+ChangeY][x+ChangeX]), markup);
        ChangeX = 0;
    }
    if(y > 1)
    {
        ChangeY = -1;

        int id = Map[y+ChangeY][x+ChangeX].ID-'0';

        buffer[0] = RoomDisplay[id];
        buffer[1] = '\0';


        if(Map[y+ChangeY][x+ChangeX].ID == '1')
        {
            format="<span font_size =\"larger\" bgcolor =\"#8a8a8a\">%s</span>";
        } else if(Map[y+ChangeY][x+ChangeX].ID == '5')
        {
            format="<span font_size =\"larger\" bgcolor =\"#ad9f00\">%s</span>";
        } else
        {
            format="<span font_size =\"larger\" bgcolor =\"#b3e6a5\">%s</span>";
        }

        markup=g_markup_printf_escaped(format,buffer);



        gtk_label_set_text(GTK_LABEL(MapGtk[y+ChangeY][x+ChangeX]),buffer);

        gtk_label_set_markup(GTK_LABEL(MapGtk[y+ChangeY][x+ChangeX]), markup);
        ChangeY = 0;
    }
    if(y < MapSizeY)
    {
        ChangeY = 1;

        int id = Map[y+ChangeY][x+ChangeX].ID-'0';

        buffer[0] = RoomDisplay[id];
        buffer[1] = '\0';

        if(Map[y+ChangeY][x+ChangeX].ID == '1')
        {
            format="<span font_size =\"larger\" bgcolor =\"#8a8a8a\">%s</span>";
        } else if(Map[y+ChangeY][x+ChangeX].ID == '5')
        {
            format="<span font_size =\"larger\" bgcolor =\"#ad9f00\">%s</span>";
        } else
        {
            format="<span font_size =\"larger\" bgcolor =\"#b3e6a5\">%s</span>";
        }

        markup=g_markup_printf_escaped(format,buffer);



        gtk_label_set_text(GTK_LABEL(MapGtk[y+ChangeY][x+ChangeX]),buffer);

        gtk_label_set_markup(GTK_LABEL(MapGtk[y+ChangeY][x+ChangeX]), markup);
        ChangeY = 0;
    }
}
void Update_Attributes()
{
    char A_buffer[MAKS_DL];

    sprintf(A_buffer,"%d",MainPlayer.Attributes.Strength);
    gtk_label_set_text(GTK_LABEL(StrengthLabel),A_buffer);

    sprintf(A_buffer,"%d",MainPlayer.Attributes.Agillity);
    gtk_label_set_text(GTK_LABEL(AgillityLabel),A_buffer);

    sprintf(A_buffer,"%d",MainPlayer.Attributes.Inteligence);
    gtk_label_set_text(GTK_LABEL(InteligenceLabel),A_buffer);

}
void HP_Loss()
{
    char buffer[MAKS_DL];

    strcpy(buffer,"HP: ");

    MainPlayer.HP--;

    char tmp[MAKS_DL];
    sprintf(tmp,"%d",MainPlayer.HP);

    strcat(buffer,tmp);

    if(MainPlayer.HP == 0)
    {
        Send_Turn_Info_To_Pipe(-1);
    }

    gtk_label_set_text(GTK_LABEL(HPLabel),buffer);
}
void Changing_Room(GtkWidget *widget, gpointer*data)
{
    if(WaitingForOtherPlayer) return;

    DidMoveInTurn[Turn] = 1;

    WaitingForOtherPlayer = 1;

    int x = MainPlayer.x;
    int y = MainPlayer.y;

    int ChangeX = 0, ChangeY = 0;

    if(strcmp((gchar*)data,"down") == 0 && y < MapSizeY && Map[y+1][x].ID != '1')
    {
        ChangeY = 1;
    } else if(strcmp((gchar*)data,"up") == 0 && y > 1 && Map[y-1][x].ID != '1')
    {
        ChangeY = -1;
    } else if(strcmp((gchar*)data,"left")== 0 && x > 1 && Map[y][x-1].ID != '1')
    {
        ChangeX = -1;
    } else if(strcmp((gchar*)data,"right")== 0 && x < MapSizeX && Map[y][x+1].ID != '1')
    {
        ChangeX = 1;
    } else
    {

    }

    Map[y][x] = MainPlayer.WhereStanding;

    MainPlayer.WhereStanding = Map[y+ChangeY][x+ChangeX];

    Send_Turn_Info_To_Pipe(Turn);

    Map[y+ChangeY][x+ChangeX] = MainPlayer.Display;


    MainPlayer.prevX = MainPlayer.x;
    MainPlayer.prevY = MainPlayer.y;

    MainPlayer.x += ChangeX;
    MainPlayer.y += ChangeY;





    if(ChangedInMyTurn)
    {
        Update_Grid();
        ChangedInMyTurn = 0;
    }
    return;
}


void Redo_Player_Move()
{
    int prevX = MainPlayer.prevX;
    int prevY = MainPlayer.prevY;

    int x = MainPlayer.x;
    int y = MainPlayer.y;

    Map[y][x] = MainPlayer.WhereStanding;

    MainPlayer.WhereStanding = Map[prevY][prevX];


    Map[prevY][prevX] = MainPlayer.Display;


    MainPlayer.x = prevX;
    MainPlayer.y = prevY;

}

//Room Interactions
void Room_With_Enemy()
{
    Enemy RoomEnemy = MainPlayer.WhereStanding.Enemy;
    int EnemyType = RoomEnemy.EnemyID;

    Attributes EnemyAttributes = RoomEnemy.Attributes;

    if(RoomEnemy.Defeated == false)
    {
        int PlayerChoosing = Show_Room_Communicate(EnemyType);

        if(PlayerChoosing == 2)     // Gracz Wybral Walke
        {
            MainPlayer.WhereStanding.Enemy.Defeated = true;
            if(EnemyType == 1)      // Przeciwnik na sile
            {
                if(MainPlayer.Attributes.Strength < EnemyAttributes.Strength)
                {
                    HP_Loss();
                }
            }
            else if(EnemyType == 2)   //Przeciwnik na zrecznosc
            {
                if(MainPlayer.Attributes.Agillity < EnemyAttributes.Agillity)
                {
                    HP_Loss();
                }
            }
            else if(EnemyType == 3)   //Przeciwnik na inteligencje
            {
                if(MainPlayer.Attributes.Inteligence < EnemyAttributes.Inteligence)
                {
                    HP_Loss();
                }
            }
        }
        else if(PlayerChoosing == 3)  //Gracz ryzykuje
        {
            MainPlayer.WhereStanding.Enemy.Defeated = true;

            int RandInteger = rand()%10;

            if(RandInteger%2 == 0)
            {
                HP_Loss();
            }
        }
        else if(PlayerChoosing == 4)    //Ucieczka
        {
            Redo_Player_Move();
        }
    }
}
void Search_Room (GtkWidget *widget, gpointer*data)
{
    if(WaitingForOtherPlayer) return;

    MainPlayer.prevX = MainPlayer.x;
    MainPlayer.prevY = MainPlayer.y;

    DidMoveInTurn[Turn] = 1;

    WaitingForOtherPlayer = 1;

    Send_Turn_Info_To_Pipe(Turn);

    if(MainPlayer.WhereStanding.Enemy.EnemyID == 4)
    {
        int tmp = rand()%4;
        if(tmp == 0)
        {
            WhichStatUpdated = 0;
            MainPlayer.Attributes.Strength ++;
        } else if(tmp == 1)
        {
            WhichStatUpdated = 1;
            MainPlayer.Attributes.Agillity ++;
        } else
        {
            WhichStatUpdated = 2;
            MainPlayer.Attributes.Inteligence ++;
        }
    } else if(MainPlayer.WhereStanding.Enemy.EnemyID == 5)
    {
        MainPlayer.HasKey = true;
        Show_Communicate("Zdobyłeś Klucz!");
    }

    if(ChangedInMyTurn)
    {
        Update_Grid();
        ChangedInMyTurn = 0;
    }


}


Attributes Pick_Class()
{
    GtkWidget *dialog;
    char ButtonFirstName[MAKS_DL];
    strcpy(ButtonFirstName,"Wojownik");

    char ButtonSecondName[MAKS_DL];
    strcpy(ButtonSecondName,"Złodziej");

    char ButtonThirdName[MAKS_DL];
    strcpy(ButtonThirdName,"Czarownik");

    dialog=gtk_dialog_new();

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_container_set_border_width(GTK_CONTAINER(content_area),45);


    GtkWidget *label = gtk_label_new("Wybierz klase z jaką zaczniesz przygode!");
    gtk_label_set_line_wrap(GTK_LABEL(label),(gboolean)(TRUE));

    gtk_container_add(GTK_CONTAINER(content_area),label);

    GtkWidget *ButtonFirst = gtk_button_new_with_label(ButtonFirstName);
    GtkWidget *ButtonSecond = gtk_button_new_with_label(ButtonSecondName);
    GtkWidget *ButtonThird = gtk_button_new_with_label(ButtonThirdName);

    g_signal_connect(G_OBJECT(ButtonFirst), "clicked", G_CALLBACK(Warrior_Choosed),(gpointer)dialog);
    g_signal_connect(G_OBJECT(ButtonSecond), "clicked", G_CALLBACK(Thief_Choosed),(gpointer)dialog);
    g_signal_connect(G_OBJECT(ButtonThird), "clicked", G_CALLBACK(Mage_Choosed),(gpointer)dialog);


    gtk_container_add(GTK_CONTAINER(content_area),ButtonFirst);
    gtk_container_add(GTK_CONTAINER(content_area),ButtonSecond);
    gtk_container_add(GTK_CONTAINER(content_area),ButtonThird);


    gtk_widget_show_all(dialog);

    gint Response = -1;

    while(Response < 0) Response = gtk_dialog_run (GTK_DIALOG (dialog));

    gtk_widget_destroy (dialog);

    Attributes Class;
    if(Response == 1)       // Gracz Wybral Wojownika
    {
        Class.Strength = 15;
        Class.Agillity = 7;
        Class.Inteligence = 5;
    }
    if(Response == 2)       // Gracz Wybral Zlodzieja
    {
        Class.Strength = 4;
        Class.Agillity = 16;
        Class.Inteligence = 8;
    }
    if(Response == 3)       // Gracz Wybral Czarownika
    {
        Class.Strength = 2;
        Class.Agillity = 5;
        Class.Inteligence = 25;
    }

    return Class;
}

//Button Functions
void Fight_Enemy(GtkWidget *widget, gpointer dialog)
{
    gtk_dialog_response(GTK_DIALOG(dialog),2);
}
void Pass_Enemy(GtkWidget *widget, gpointer dialog)
{
    gtk_dialog_response(GTK_DIALOG(dialog),3);
}
void Escape_Enemy(GtkWidget *widget, gpointer dialog)
{
    gtk_dialog_response(GTK_DIALOG(dialog),4);
}
void Warrior_Choosed(GtkWidget *widget, gpointer dialog)
{
    gtk_dialog_response(GTK_DIALOG(dialog),1);
}
void Thief_Choosed(GtkWidget *widget, gpointer dialog)
{
    gtk_dialog_response(GTK_DIALOG(dialog),2);
}
void Mage_Choosed(GtkWidget *widget, gpointer dialog)
{
    gtk_dialog_response(GTK_DIALOG(dialog),3);
}
