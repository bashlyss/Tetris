string highscore_name ()
{
       vector <char> word;
       string t;
       char c = ' ';
       set_keyboard_rate(50,1);
     //  bool flag = false;
       for (;;)
       {
           updateScreen();
           textprintf_ex(buffer, font, 50, 100, makecol(255,255,255), -1, "Enter your name", lines);
           textprintf_ex(buffer, font, 50, 120, makecol(255,255,255), -1, t.c_str(), lines);
           acquire_screen();
     draw_sprite (screen, buffer,0,0);
     release_screen(); 
           readkey();
           for (int i = 0; i < 26; i++)
               if (key[KEY_A+i] && c != 'a'+i)
               {
                  word.push_back('a'+i);
                  c = 'a'+i;
                  break;
               }
               else if (!key[KEY_A+i] && c == 'a'+i)
               {
                    c = ' ';
               }
                   
           if (key[KEY_BACKSPACE] && word.size() > 0 && c != '.')
           { 
              word.pop_back();
              c = '.'; 
           }
           else if (!key[KEY_BACKSPACE] && c == '.')
           { 
              c = ' '; 
           }
           else if (key[KEY_ENTER] || key[KEY_ESC]) break;
           
           /*    else if (key[KEY_B]) word.push_back('b'); 
               else if (key[KEY_C]) word.push_back('c'); 
               else if (key[KEY_D]) word.push_back('d'); 
               else if (key[KEY_E]) word.push_back('e'); 
               else if (key[KEY_F]) word.push_back('f'); 
               else if (key[KEY_G]) word.push_back('g'); 
               else if (key[KEY_H]) word.push_back('h'); 
               else if (key[KEY_I]) word.push_back('i'); 
               else if (key[KEY_J]) word.push_back('j'); 
               else if (key[KEY_K]) word.push_back('k'); 
               else if (key[KEY_L]) word.push_back('l'); 
               else if (key[KEY_M]) word.push_back('m'); 
               else if (key[KEY_N]) word.push_back('n'); 
               else if (key[KEY_O]) word.push_back('o'); 
               else if (key[KEY_P]) word.push_back('p'); 
               else if (key[KEY_Q]) word.push_back('q'); 
               else if (key[KEY_R]) word.push_back('r'); 
               else if (key[KEY_S]) word.push_back('s'); 
               else if (key[KEY_T]) word.push_back('t'); 
               else if (key[KEY_U]) word.push_back('u'); 
               else if (key[KEY_V]) word.push_back('v'); 
               else if (key[KEY_W]) word.push_back('w'); 
               else if (key[KEY_X]) word.push_back('x'); 
               else if (key[KEY_Y]) word.push_back('y'); 
               else if (key[KEY_Z]) word.push_back('z'); */
               
          //     flag = true;
         //  }
       //    else if (!readkey()) flag = false;
           t = "";
           for (int i = 0; i < word.size(); i++)
               t += word[i];
       }
       if (t == "")
          return " ";
       return t;
}

void highscore_import ()
{
    ifstream Highscores_In;
    ifstream Highscores_Lines_In;
    ifstream Highscores_Level_In;
    Highscores_In.open ("Highscores/Highscores.txt");
    Highscores_Lines_In.open ("Highscores/Highscore Lines.txt");
    Highscores_Level_In.open ("Highscores/Highscore Level.txt");
    for (int i = 0; i < 10; i++)
    {
        Highscores_In >> highscore_nums[0][i];
        Highscores_In >> highscore_names[0][i];
    }
    for (int i = 0; i < 10; i++)
    {
        Highscores_Lines_In >> highscore_nums[1][i];
        Highscores_Lines_In >> highscore_names[1][i];
    }
    for (int i = 0; i < 10; i++)
    {
        Highscores_Level_In >> highscore_nums[2][i];
        Highscores_Level_In >> highscore_names[2][i];
    }
    Highscores_In.close();
    Highscores_Lines_In.close();
    Highscores_Level_In.close();
}

void highscore_export ()
{
    ofstream Highscores_Out;
    ofstream Highscores_Lines_Out;
    ofstream Highscores_Level_Out;
    Highscores_Out.open ("Highscores/Highscores.txt");
    Highscores_Lines_Out.open ("Highscores/Highscore Lines.txt");
    Highscores_Level_Out.open ("Highscores/Highscore Level.txt");
    for (int i = 0; i < 10; i++)
        Highscores_Out << highscore_nums[0][i] << " " << highscore_names[0][i] << "\n";
    for (int i = 0; i < 10; i++)
        Highscores_Lines_Out << highscore_nums[1][i] << " " << highscore_names[1][i] << "\n";
    for (int i = 0; i < 10; i++)
        Highscores_Level_Out << highscore_nums[2][i] << " " << highscore_names[2][i] << "\n";
    Highscores_Out.close();
    Highscores_Lines_Out.close();
    Highscores_Level_Out.close();    
}

void highscore_update ()
{
     highscore_import();  
     string name = highscore_name();   
     for (int i = 0; i < 10; i++)
         if (score > highscore_nums[0][i])
         {
            for (int j = 8; j >= i; j--)
            {
                highscore_nums[0][j+1] = highscore_nums[0][j];
                highscore_names[0][j+1] = highscore_names[0][j];
            }
            highscore_nums[0][i] = score;
            highscore_names[0][i] = name;
            break;
         }
     for (int i = 0; i < 10; i++)
         if (lines > highscore_nums[1][i])
         {
            for (int j = 8; j >= i; j--)
            {
                highscore_nums[1][j+1] = highscore_nums[1][j];
                highscore_names[1][j+1] = highscore_names[1][j];
            }
            highscore_nums[1][i] = lines;
            highscore_names[1][i] = name;
            break;
         }
     for (int i = 0; i < 10; i++)
         if (level > highscore_nums[2][i])
         {
            for (int j = 8; j >= i; j--)
            {
                highscore_nums[2][j+1] = highscore_nums[2][j];
                highscore_names[2][j+1] = highscore_names[2][j];
            }
            highscore_nums[2][i] = level;
            highscore_names[2][i] = name;
            break;
         }
     highscore_export();
}
