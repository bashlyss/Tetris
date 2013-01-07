volatile int ticks = 0;  // for timer
volatile int ticks2 = 0;  // for other timer
volatile int close_button_pressed = FALSE; // for close button

void ticker ()
{
     ticks++;
}
END_OF_FUNCTION(ticker);

void ticker2 ()
{
     ticks2++;
}
END_OF_FUNCTION(ticker2);

void close_button_handler(void)
{
     close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

int rotate_realligned_sprite (BITMAP* screen, BITMAP* sprite, int x, int y, int angle)
{
      int size_x = sprite -> w, size_y = sprite -> h; 
      if (abs(angle) == 64 || abs(angle) == 192)
         rotate_sprite (screen, sprite, x+(size_y-size_x)/2, y+(size_y-size_x)/2+60-size_y, itofix (angle));
      else
          rotate_sprite (screen, sprite, x, y+60-size_y, itofix (angle)); 
}

void music (bool& playing)
{     
     // Play Song
     if (playing)
     {
        stop_sample (song);
        playing = false;
     }
     else
     {
         play_sample (song,255,127,1000,1);
         playing = true;
     }
}

void updateScreen()
{
     draw_sprite (buffer, background, 0, 0);  
     for (int i = 0; i < 29; i++)
         for (int j = 1; j < 16; j++)
             if (board[j][i])
             {
              if (colour[j][i] != -1)
                draw_sprite(buffer,square[colour[j][i]], j*20, 490-i*20);
              else
                  draw_sprite(buffer,bla, j*20, 490-i*20);
             }
     int x,y;
     pieces[pieces.size()-2].Get_Loc(x,y);
     rotate_realligned_sprite(buffer,pieces[pieces.size()-2].pic, x*20, 450-y*20, pieces[pieces.size()-2].Get_Rotate());
     draw_sprite (buffer,pieces[pieces.size()-1].pic, 410-(pieces[pieces.size()-1].pic -> w / 2), 70-(pieces[pieces.size()-1].pic -> h / 2));
     textprintf_ex(buffer, font, 350, 180, makecol(0,0,0), -1, "Level: %d", level);
     textprintf_ex(buffer, font, 350, 200, makecol(0,0,0), -1, "Score: %d", score);
     textprintf_ex(buffer, font, 350, 220, makecol(0,0,0), -1, "Lines: %d", lines);
     if (game_over())
        textprintf_ex(buffer, font, 350, 240, makecol(0,0,0), -1, "Game Over", lines);
        
     scare_mouse();
     acquire_screen();
     draw_sprite (screen, buffer,0,0);
     release_screen(); 
     unscare_mouse();
}

void start_allegro()
{
     allegro_init();
     
     install_mouse();
     install_keyboard();
     install_timer();
     install_sound(DIGI_AUTODETECT,MIDI_NONE,NULL);
     
     LOCK_VARIABLE(ticks);
     LOCK_FUNCTION(ticker);
     LOCK_VARIABLE(ticks2);
     LOCK_FUNCTION(ticker2);
     LOCK_FUNCTION(close_button_handler);
     set_close_button_callback(close_button_handler);
     
     set_color_depth (desktop_color_depth());
     set_gfx_mode( GFX_AUTODETECT, 480, 530, 0, 0); 
     
     show_mouse(screen);
     buffer=create_bitmap(480,530);
     set_keyboard_rate(20,0);
     
     // load pics
     background=load_bitmap("pics/Tetris Background.bmp",NULL);
     square[0]=load_bitmap("pics/0.bmp",NULL);
     square[1]=load_bitmap("pics/1.bmp",NULL);
     square[2]=load_bitmap("pics/2.bmp",NULL);
     square[3]=load_bitmap("pics/3.bmp",NULL);
     square[4]=load_bitmap("pics/4.bmp",NULL);
     square[5]=load_bitmap("pics/5.bmp",NULL);
     square[6]=load_bitmap("pics/6.bmp",NULL);
     bla=load_bitmap("pics/square.bmp",NULL);
     
     // Load music
     song=load_wav("pics/07. Mombassa-Part 1.wav");
     lock_sample (song);
     
}

void close_allegro()
{
     destroy_sample (song);
     destroy_bitmap(buffer);
     destroy_bitmap(background);
     destroy_bitmap(bla);
     for (int i = 0; i < 7; i++)
         destroy_bitmap(square[i]);
     for (int i = 0; i < pieces.size(); i++)
         destroy_bitmap (pieces[i].pic);
     allegro_exit();
}
