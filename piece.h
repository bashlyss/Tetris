class Piece
{
      private:
              int type; // I J L O S T Z
              bool grid[4][4]; // The shape of the piece on the board
              // 0,0 is bottom left corner of piece
              int loc[2]; // coordinate of bottom middle of  x,y
              int size; // the size of the grid that the object is using
              int rotateamount; // how much to rotate a pic
              
              // Colours - Red, Green, Blue, Purple, Yellow, Orange, White
      public:
             Piece();
             void Set_Active();
             void Rotate(int direction);
             void Move_Down();
             void Move_Over(int direction);
             int Get_Rotate();
             int Get_Type();
             bool In_Spot(int x, int y); // If the piece occupies a spot of grid array
             void Get_Loc(int& x, int& y); // Collecting the x,y coordinates
             BITMAP* pic;
             
};

Piece::Piece () // Initialize
{
     type = rand() % 7; // Type of piece
     rotateamount = 0;     
     /////////////////////////////////////////////
     for (int i = 0; i < 4; i++) // Assigning Grid
        for (int j = 0; j < 4; j++)
            grid[j][i] = 0;
     if (type == 0) // I
     {
        for (int i = 0; i < 4; i++)
            grid[0][i] = 1;
        size = 4;
        pic=load_bmp("pics/I.bmp",NULL);
     }
     else if (type == 1) // J
     {
        for (int i = 0; i < 3; i++)
            grid[0][i] = 1;
        grid[1][2] = 1;
        size = 3;
        pic=load_bmp("pics/J.bmp",NULL);
     }
     else if (type == 2) // L
     {
        for (int i = 0; i < 3; i++)
            grid[1][i] = 1;
        grid[0][2] = 1;
        size = 3;
        pic=load_bmp("pics/L.bmp",NULL);
     }
     else if (type == 3) // O
     {
        for (int i = 0; i < 2; i++)
        {
            grid[1][i] = 1;
            grid[0][i] = 1;
        }
        size = 2;
        pic=load_bmp("pics/O.bmp",NULL);
     }
     else if (type == 4) // S
     {
        for (int i = 0; i < 2; i++)
        {
            grid[1][i] = 1;
            grid[0][i+1] = 1;
        }
        size = 3;
        pic=load_bmp("pics/S.bmp",NULL);
     }
     else if (type == 5) // T
     {
        for (int i = 0; i < 3; i++)
            grid[0][i] = 1;
        grid[1][1] = 1;
        size = 3;
        pic=load_bmp("pics/T.bmp",NULL);
     }
     else if (type == 6) // Z
     {
        for (int i = 0; i < 2; i++)
        {
            grid[0][i] = 1;
            grid[1][i+1] = 1;
        }
        size = 3;
        pic=load_bmp("pics/Z.bmp",NULL);
     }
     /////////////////////////////////////////////
}

void Piece::Set_Active()
{
     loc[0] = 7;
     loc[1] = 25;
}


void Piece::Rotate(int direction)
{
     //size = 4;
     bool ok = true;
     bool rotation[size][size];
     if (direction == 1) // clockwise
     {
        if (loc[0] < 1)  // colliding with left edge
        {
           for (int i = loc[0]; i < 1; i++)
               for (int j = 0; j < 4; j++)
                   if (grid[j][i-loc[0]])
                      ok = false;
        }
        else if (loc[0] > 12)  // right edge
           for (int i = loc[0]; i > 12; i--)
               for (int j = 0; j < 4; j++)
                   if (grid[j][3-(i-loc[0])])
                      ok = false;
        if (loc[1] < 0)  // colliding with bottom
        {
           for (int i = loc[1]; i < 0; i++)
               for (int j = 0; j < 4; j++)
                   if (grid[3-(i-loc[1])][j])
                      ok = false;
        }
        if (ok)
        {
            for (int i = 0; i < size; i++) // rotating
                for (int j = 0; j < size; j++)
                    rotation[i][size-j-1] = grid[j][i];
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    grid[i][j] = rotation[i][j];
                    
                    
            for (int i = 0; i < 4; i++) // collide with other pieces
                for (int j = 0; j < 4; j++)
                    if (board[loc[0]+i][loc[1]+j] && In_Spot(i,j))
                       ok=false;
            if (ok)
               rotateamount+=64;
            else
            {
                for (int i = 0; i < size; i++) // unrotate
                    for (int j = 0; j < size; j++)
                        rotation[j][i] = grid[i][size-j-1];
                for (int i = 0; i < size; i++)
                    for (int j = 0; j < size; j++)
                        grid[i][j] = rotation[i][j];
            }
        }
     }
     else if (direction == 2) // counter clockwise
     {
          if (loc[0] < 1) // left edge collision
          {
             for (int i = loc[0]; i < 1; i++)
                 for (int j = 0; j < 4; j++)
                     if (grid[j][3-(i-loc[0])])
                        ok = false;
          }
          else if (loc[0] > 12) // right edge
               for (int i = loc[0]; i >= 12; i--)
                   for (int j = 0; j < 4; j++)
                       if (grid[j][i-loc[0]])
                          ok = false;
          if (loc[1] < 0)  // colliding with bottom
          {
             for (int i = loc[1]; i < 0; i++)
                 for (int j = 0; j < 4; j++)
                     if (grid[i-loc[1]][j])
                        ok = false;
          }
          
          if (ok)
          {
              for (int i = 0; i < size; i++) // rotate
                  for (int j = 0; j < size; j++)
                      rotation[j][i] = grid[i][size-j-1];
              for (int i = 0; i < size; i++)
                  for (int j = 0; j < size; j++)
                      grid[i][j] = rotation[i][j];
                      
              for (int i = 0; i < 4; i++) // check against other pieces
                for (int j = 0; j < 4; j++)
                    if (board[loc[0]+i][loc[1]+j] && In_Spot(i,j))
                       ok=false;
              if (ok)         
                 rotateamount-=64;
              else
              {
                  for (int i = 0; i < size; i++) // rotate back
                      for (int j = 0; j < size; j++)
                          rotation[i][size-j-1] = grid[j][i];
                  for (int i = 0; i < size; i++)
                      for (int j = 0; j < size; j++)
                          grid[i][j] = rotation[i][j];
              }
          }
     }
     bool empty;
     for (int i = 0; i < 4; i++)
     {
         empty = true;
         for (int j = 0; j < 4; j++)
             if (grid[0][j])
                empty = false;
         if (empty)
         {
            for (int k = 1; k < 4; k++)
                for (int j = 0; j < 4; j++)
                    grid[k-1][j] = grid[k][j];
            for (int j = 0; j < 4; j++)
                    grid[3][j] = false;
         }
     }
     for (int i = 0; i < 4; i++)
     {
         empty = true;
         for (int j = 0; j < 4; j++)
             if (grid[j][0])
                empty = false;
         if (empty)
         {
            for (int k = 1; k < 4; k++)
                for (int j = 0; j < 4; j++)
                    grid[j][k-1] = grid[j][k];
            for (int j = 0; j < 4; j++)
                    grid[j][3] = false;
         }
     }
     
}

void Piece::Move_Down ()
{
     loc[1]--;
}

void Piece::Move_Over (int direction)
{
     bool ok = true;
     int min=4,max=-1; // find edges to prevent going outside walls
     for (int i = 0; i < 4; i++)
         for (int j = 0; j < 4; j++)
             if (grid[i][j])
             {
                if (i > max)
                   max = i;
                if (i < min)
                   min = i;
             }
     if (direction == 1 && loc[0]+min > 1) // Left
     {
        for (int i = 0; i < 4; i++) // check against other pieces
            for (int j = 0; j < 4; j++)
                if (board[loc[0]+i-1][loc[1]+j] && In_Spot(i,j))
                   ok=false;
        if (ok)
           loc[0]--;
     }
     else if (direction == 2 && loc[0]+max < 15) // Right
     {
          for (int i = 0; i < 4; i++) // check against other pieces
            for (int j = 0; j < 4; j++)
                if (board[loc[0]+i+1][loc[1]+j] && In_Spot(i,j))
                   ok = false;
          if (ok)
             loc[0]++;
     }
}

int Piece::Get_Rotate ()
{
    return rotateamount%256;
  //return rotateamount;
}

int Piece::Get_Type ()
{
    return type;
}

bool Piece::In_Spot (int x, int y)
{
     return grid[x][y];
}

void Piece::Get_Loc (int& x, int& y)
{
     x = loc[0];
     y = loc[1];
}
