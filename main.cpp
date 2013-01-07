#include <allegro.h>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

bool game_over();

BITMAP* buffer;
BITMAP* background;
BITMAP* square[7];
BITMAP* bla;
SAMPLE* song;

int highscore_nums[3][10];
string highscore_names[3][10];

bool board [17][29]; // Actually 15*25 but with 3 hidden rows for the top of pieces
int colour [17][29]; // for drawing graphics purposes
int score = 0, lines = 0, level = 1; // score related variables

#include "piece.h"

vector <Piece> pieces; // contains a record of all pieces

#include "Allegro functions.h"
#include "Highscores.h"


bool collide (int active)
{
     int x,y;
     pieces[active].Get_Loc(x,y);
     for (int i = 0; i < 4; i++)
         for (int j = 0; j < 4; j++)
             if ((board[x+i][y+j-1]|| y+j==0) && pieces[active].In_Spot(i,j))
             {
                for (int k = 0; k < 4; k++)
                    for (int h = 0; h < 4; h++)
                        if (pieces[active].In_Spot(k,h))
                        {
                           board[x+k][y+h] = true;
                           colour[x+k][y+h] = pieces[active].Get_Type();
                        }
                score += 10;
                return true;
             }
     return false;
}

void complete_row ()
{
     int c = 1;
     bool complete;
     for (int i = 0; i < 25; i++)
     {
         complete = true;
         for (int j = 1; j < 16; j++)
             if (!board[j][i])
             {
                complete = false;
                break;
             }
         if (complete)
         {
            score += 50*c;
            c++;
            lines++;
            for (int j = i+1; j < 27; j++)
                for (int k = 1; k < 16; k++)
                {
                    colour[k][j-1] = colour[k][j];
                    board[k][j-1] = board [k][j];
                }
            i--;
         }
     }
     
}

bool game_over ()
{
     for (int i = 1; i < 16; i++)
         if (board[i][24])
            return true;
     return false;
}

void instructions ()
{
     draw_sprite (buffer, background, 0, 0);  
     
     textprintf_centre_ex(buffer, font, 220, 140, makecol(255,255,255), -1, "Instructions");
     textprintf_centre_ex(buffer, font, 220, 160, makecol(255,255,255), -1, "A piece in the darker blue area will end the game");
     textprintf_centre_ex(buffer, font, 220, 180, makecol(255,255,255), -1, "Rotate Clockwise - Down Arrow Key");
     textprintf_centre_ex(buffer, font, 220, 200, makecol(255,255,255), -1, "Rotate Counter Clockwise - Up Arrow Key");
     textprintf_centre_ex(buffer, font, 220, 220, makecol(255,255,255), -1, "Move Left - Left Arrow Key");
     textprintf_centre_ex(buffer, font, 220, 240, makecol(255,255,255), -1, "Move Right - Right Arrow Key");
     textprintf_centre_ex(buffer, font, 220, 260, makecol(255,255,255), -1, "Hard Drop - Space Bar");
     textprintf_centre_ex(buffer, font, 220, 280, makecol(255,255,255), -1, "Press Any Key to Continue");
     textprintf_centre_ex(buffer, font, 220, 300, makecol(255,255,255), -1, "M to play/stop music");
     textprintf_centre_ex(buffer, font, 220, 320, makecol(255,255,255), -1, "Escape to Quit");
     
     acquire_screen();
     draw_sprite (screen, buffer,0,0);
     release_screen(); 

     readkey();
     clear_keybuf();
}

int main(int argc, char *argv[])
{
    srand(time(0));
    start_allegro();
    
    for (int i = 0; i < 17; i++)
        for (int j = 0; j < 29; j++)
            board[i][j] = false;
    for (int i = 0; i < 17; i++)
        for (int j = 0; j < 29; j++)
            colour[i][j] = -1;
    
    int movement, active, x, y;
    active = 0;
    
    bool playing = false; // if music is playing
    
    // Initialize the first 2 pieces
    for (int i = 0; i < 2; i++)
    {
        Piece temp;
        pieces.push_back(temp);
    }
    
    pieces[active].Set_Active();
    
    
    music(playing);
    instructions();
    if (key[KEY_ESC])
    {
       close_allegro();
       return 0;
    }
    
    install_int (ticker, 400); // initialize timer
    int oldticks, oldticks2,oldlevel;
    bool dropped = false, move[4] = {false,false,false,false};
    
    while (!close_button_pressed)
    {
        oldlevel = level;
        level = (lines*25+score)/500+1;
        if (level > oldlevel && level < 31) // speeding game up over time
        {
           install_int (ticker, 408-level*8); // initialize timer
        }
        
        
        // If piece is on another piece
      /*  if (collide(active))
        {
           Piece temp;p
           pieces.push_back(temp);
           active++;
           complete_row();
           if (game_over())
              break;
           pieces[active].Set_Active();
        }*/
        
        // timers
        while (ticks == 0)
        {     rest (1); }
        
        while (ticks > 0)
        {
            oldticks = ticks;
            
            // Movement of the piece.  Rotate or horizontal
            movement = 0;
            
            if (key[KEY_UP] && !move[0])
            {
               movement = 2;
               move[0] = true;
            }
            else if (!key[KEY_UP] && move[0])
                 move[0] = false;
            if (key[KEY_DOWN] && !move[1])
            {
                 movement = 1;
                 move[1] = true;
            }
            else if (!key[KEY_DOWN] && move[1])
                 move[1] = false;
            if (movement == 1 || movement == 2)
               pieces[active].Rotate(movement);
               
               
            if (key[KEY_LEFT] && !move[2])
            {
               movement = 3;
               move[2] = true;
            }
            else if (!key[KEY_LEFT] && move[2])
                 move[2] = false;
            
            if (key[KEY_RIGHT] && !move[3])
            {
                 movement = 4;
                 move[3] = true;
            }
            else if (!key[KEY_RIGHT] && move[3])
                 move[3] = false;
            
            if (movement == 3 || movement == 4)
               pieces[active].Move_Over(movement-2);
               
            if (key[KEY_SPACE] && !dropped)
            {
               dropped = true;
               pieces[active].Get_Loc(x,y);
               score+=y/4;
               for(;;)
                   if (!collide(active))
                       pieces[active].Move_Down();
                   else
                   {
                      Piece temp;
                      pieces.push_back(temp);
                      active++;
                      complete_row();
                      if (game_over())
                         break;
                      pieces[active].Set_Active();
                      break;
                   }
               break;
            }
            else if (!key[KEY_SPACE])
                 dropped = false;
            
            if (key[KEY_M])
               music(playing);
            
            if (game_over())
               break;
               
            if (key[KEY_ESC])
            {
               close_allegro();
               return 0;
            }
               
            updateScreen();
            
            if (oldticks+1 <= ticks)
               break;
        }
        if (game_over())
           break;
            
        if (!collide(active))
           pieces[active].Move_Down();
        else
        {
           Piece temp;
           pieces.push_back(temp);
           active++;
           complete_row();
           if (game_over())
              break;
           pieces[active].Set_Active();
        }
        
        updateScreen();
      //  rest(180);
    }
    clear_keybuf();
    updateScreen();
    if (!close_button_pressed)
       highscore_update();
       
    while (!close_button_pressed && !readkey())
    {
          readkey();
    }
    close_allegro();
    return 0; 
}
END_OF_MAIN();
