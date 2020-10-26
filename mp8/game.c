#include "game.h"
/*This code is 2048. make_game and remake_game create a game board with a provided size. They initialize all cells to -1 and 
 *the score to 0. legal_move_check checks if there are any legal moves in any direction. get_cell gets a cell from a given
 *location. The move_(wasd) functions all move the board a given direction and combine the proper cells and increments  
 *the score
 *PARTNERS: jrhaag2, briants2
 */

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
        int i, j;
    (*mygame).rows = rows;
    (*mygame).cols = cols;
    for (i=0; i<rows; i++)
    {
        for (j=0; j<cols; j++)
        {
          (*mygame).cells[(i*cols)+j] = -1;
        }
    }
    (*mygame).score = 0;
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
    game structure to have the given number of rows and columns. Initialize
    the score and all elements in the cells to -1. Make sure that any
    memory previously allocated is not lost in this function.   
*/
{
    /*Frees dynamically allocated memory used by cells in previous game,
     then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
    free((*_cur_game_ptr)->cells);
    (*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

     //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
     int i, j;
     (**_cur_game_ptr).rows = new_rows;
     (**_cur_game_ptr).cols = new_cols;
     (**_cur_game_ptr).score = 0;
     for (i=0; i<new_rows; i++)
     {
       for (j=0; j<new_cols; j++)
       {
         (**_cur_game_ptr).cells[(i*new_cols)+j] = -1;
       }
     }
    return;      
}


void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
    if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    int temp;
    int col_size = (*cur_game).cols;
    temp = (*cur_game).cells[(row*col_size)+col];
    if (temp == -1 || temp%2==0) return (*cur_game).cells; //Get current cell if it exists
    return NULL;
}






int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
    int temp, i, j, down, cur;
    int num_rows;
    int num_cols;
    num_rows = (*cur_game).rows;
    num_cols = (*cur_game).cols;
    int size = (num_rows*num_cols);
    int next[size];
    int tally = 0;
    for (i=0; i<(num_rows); i++)
    {
      for (j=0; j<num_cols; j++)
      {
    	next[(i*num_cols)+j] = (*cur_game).cells[(i*num_cols)+j];
      }
    }

    temp = legal_move_check(cur_game); //Check if there are any legal moves
    if (temp == 0) return 0;


for (int boof=0;boof<num_rows;boof++)    //should clear whitespace
{
	for (int i=1; i<num_rows; i++)
    	{
	for (int j=0; j<num_cols; j++)
	{
		int down =next[((i-1)*num_cols)+j];
		int cur = next[(i*num_cols)+j];
		if (down<0)
		{
			next[((i-1)*(num_cols))+j] = cur;  //Move current cell up if empty
      			next[(i*(num_cols))+j] = -1;    //Reset current cell when combined
			
		}
	}
	}
}
	//Combine Numbers
  	for (int i=0; i<num_rows-1; i++)
    	{
	for (int j=0; j<num_cols; j++)
	{
       	 	down =next[((i+1)*num_cols)+j]; //really down
        	cur = next[(i*num_cols)+j];
        	if (down == cur && down >0)
        	{
          		next[((i)*num_cols)+j] = (2*down); //Combine current cell with upper cell
      	  		next[((i+1)*num_cols) +j] = -1;      //Reset current cell when combined
          		tally = tally + (2*down); //Increase score
			//deleteWhite(num_cols,next);
        	}
	

	}
   	}
for (int boof=0;boof<num_rows;boof++)    //should clear whitespace
{
	for (int i=1; i<num_rows; i++)
    	{
	for (int j=0; j<num_cols; j++)
	{
		int down =next[((i-1)*num_cols)+j];
		int cur = next[(i*num_cols)+j];
		if (down<0)
		{
			next[((i-1)*(num_cols))+j] = cur;  //Move current cell up if empty
      			next[(i*(num_cols))+j] = -1;    //Reset current cell when combined
			
		}
	}
	}
}




//compare new game to old game
    for (i=0; i<num_rows; i++)
    {
      for (j=0; j<num_cols; j++)
      {
    	if (next[(i*num_cols)+j] != (*cur_game).cells[(i*num_cols)+j]) break;
      }
    	if (next[(i*num_cols)+j] != (*cur_game).cells[(i*num_cols)+j]) break;
    }
	if ((i+1) == num_rows && (j+1) == num_cols) 
	{
	   if (next[(i*num_cols)+j] == (*cur_game).cells[(i*num_cols)+j]) return 0; //End if no change between games.
	}
//Merge games
    for (i=0; i<num_rows; i++)
    {
      for (j=0; j<num_cols; j++)
      {
    (*cur_game).cells[(i*num_cols)+j] = next[(i*num_cols)+j];
      }
    }
    (*cur_game).score = (*cur_game).score + tally; //Increase score

    
    return 1;
}

int move_s(game * cur_game) //slide down
{
    int temp, i, j, down, cur;
    int num_rows;
    int num_cols;
    num_rows = (*cur_game).rows;
    num_cols = (*cur_game).cols;
    int size = (num_rows*num_cols);
    int next[size];
    int tally = 0;
    for (i=0; i<(num_rows); i++)
    {
      for (j=0; j<num_cols; j++)
      {
    	next[(i*num_cols)+j] = (*cur_game).cells[(i*num_cols)+j];
      }
    }

    temp = legal_move_check(cur_game); //Check if there are any legal moves
    if (temp == 0) return 0;


for (int boof=0;boof<num_rows;boof++)    //should clear whitespace
{
	for (int i=0; i<(num_rows-1); i++)
    	{
	for (int j=0; j<num_cols; j++)
	{
		int down =next[((i+1)*num_cols)+j];
		int cur = next[(i*num_cols)+j];
		if (down<0)
		{
			next[((i+1)*(num_cols))+j] = cur;  //Move current cell up if empty
      			next[(i*(num_cols))+j] = -1;    //Reset current cell when combined
			
		}
	}
	}
}
	//Combine Numbers
  	for (int i=(num_rows-1); i>=0; i--)
    	{
	for (int j=(num_cols-1); j>=0; j--)
	{
       	 	down =next[((i-1)*num_cols)+j]; //really up
        	cur = next[(i*num_cols)+j];
        	if (down == cur && down >1)
        	{
          		next[((i)*num_cols)+j] = (2*down); //Combine current cell with upper cell
      	  		next[((i-1)*num_cols) +j] = -1;      //Reset current cell when combined
          		tally = tally + (2*down); //Increase score
			//deleteWhite(num_cols,next);
        	}
	

	}
   	}
for (int boof=0;boof<num_rows;boof++)    //should clear whitespace
{
	for (int i=0; i<(num_rows-1); i++)
    	{
	for (int j=0; j<num_cols; j++)
	{
		 down =next[((i+1)*num_cols)+j];
		int cur = next[(i*num_cols)+j];
		if (down<0)
		{
			next[((i+1)*(num_cols))+j] = cur;  //Move current cell up if empty
      			next[(i*(num_cols))+j] = -1;    //Reset current cell when combined
			
		}
	}
	}
}




//compare new game to old game
    for (i=0; i<num_rows; i++)
    {
      for (j=0; j<num_cols; j++)
      {
    	if (next[(i*num_cols)+j] != (*cur_game).cells[(i*num_cols)+j]) break;
      }
    	if (next[(i*num_cols)+j] != (*cur_game).cells[(i*num_cols)+j]) break;
    }
    	if ((i+1) == num_rows && (j+1) == num_cols) 
	{
	   if (next[(i*num_cols)+j] == (*cur_game).cells[(i*num_cols)+j]) return 0; //End if no change between games.
	}
//Merge games
    for (i=0; i<num_rows; i++)
    {
      for (j=0; j<num_cols; j++)
      {
    (*cur_game).cells[(i*num_cols)+j] = next[(i*num_cols)+j];
      }
    }
    (*cur_game).score = (*cur_game).score + tally; //Increase score

    //temp = legal_move_check(cur_game); //Check if there are any legal moves
    //if (temp == 1) move_w(cur_game);   //Run it again to move tiles again if there is space.
   //rand_new_tile(cur_game);
    return 1;
}

int move_a(game * cur_game) //slide left
{
    
    //YOUR CODE STARTS HERE

    int temp, i, j, left, cur;
    int num_rows;
    int num_cols;
    num_rows = (*cur_game).rows;
    num_cols = (*cur_game).cols;
    int size = (num_rows*num_cols);
    int next[size];
    int tally = 0;
    for (i=0; i<num_rows; i++)
    {
      for (j=0; j<num_cols; j++)
      {
    	next[(i*num_cols)+j] = (*cur_game).cells[(i*num_cols)+j];
      }
    }

    temp = legal_move_check(cur_game); //Check if there are any legal moves
    if (temp == 0) return 0;


for (int boof=0;boof<num_cols;boof++)    //should clear whitespace
{
	for (int j=1; j<num_cols; j++)
    	{
	for (int i=0; i<num_rows; i++)
	{
		int left =next[((i)*num_cols)+j-1];
		int cur = next[(i*num_cols)+j];
		if (left<0)
		{
			next[((i)*(num_cols))+j-1] = cur;  //Move current cell left if empty
      			next[(i*(num_cols))+j] = -1;    //Reset current cell when combined
			
		}
	}
	}
}
//Merge numbers	
  	for (int j=0; j<(num_cols-1); j++)
    	{
	for (int i=0; i<num_rows; i++)
	{
       	 	left =next[((i)*num_cols)+j+1];//really right
        	cur = next[(i*num_cols)+j];
        	if (left == cur && left >0)
        	{
          		next[((i)*num_cols)+j] = (2*left); //Combine current cell with upper cell
      	  		next[(i*num_cols)+j+1] = -1;      //Reset current cell when combined
          		tally = tally + (2*left); //Increase score
			//deleteWhite(num_cols,next);
        	}
	

	}
   	}
for (int boof=0;boof<num_cols;boof++)    //should clear whitespace
{
	for (int j=1; j<(num_cols); j++)
    	{
	for (int i=0; i<num_rows; i++)
	{
		int left =next[((i)*num_cols)+j-1];
		int cur = next[(i*num_cols)+j];
		if (left<0)
		{
			next[((i)*(num_cols))+j-1] = cur;  //Move current cell left if empty
      			next[(i*(num_cols))+j] = -1;    //Reset current cell when combined
			
		}
	}
	}
}




//compare new game to old game
    for (i=0; i<num_rows; i++)
    {
      for (j=0; j<num_cols; j++)
      {
    	if (next[(i*num_cols)+j] != (*cur_game).cells[(i*num_cols)+j]) break;
      }
    	if (next[(i*num_cols)+j] != (*cur_game).cells[(i*num_cols)+j]) break;
    }
    	if ((i+1) == num_rows && (j+1) == num_cols) 
	{
	   if (next[(i*num_cols)+j] == (*cur_game).cells[(i*num_cols)+j]) return 0; //End if no change between games.
	}

//Merge games
    for (i=0; i<num_rows; i++)
    {
      for (j=0; j<num_cols; j++)
      {
    (*cur_game).cells[(i*num_cols)+j] = next[(i*num_cols)+j];
      }
    }
    (*cur_game).score = (*cur_game).score + tally; //Increase score

    
    return 1;

}

int move_d(game * cur_game) //slide to the right
{
    //YOUR CODE STARTS HERE

    int temp, i, j, right, cur;
    int num_rows;
    int num_cols;
    num_rows = (*cur_game).rows;
    num_cols = (*cur_game).cols;
    int size = (num_rows*num_cols);
    int next[size];
    int tally = 0;
    for (i=0; i<num_rows; i++)
    {
      for (j=0; j<num_cols; j++)
      {
    	next[(i*num_cols)+j] = (*cur_game).cells[(i*num_cols)+j];
      }
    }

    temp = legal_move_check(cur_game); //Check if there are any legal moves
    if (temp == 0) return 0;


for (int boof=0;boof<num_cols;boof++)    //should clear whitespace
{
	for (int j=0; j<(num_cols-1); j++)
    	{
	for (int i=0; i<num_rows; i++)
	{
		int right =next[((i)*num_cols)+j+1];
		int cur = next[(i*num_cols)+j];
		if (right<0)
		{
			next[((i)*(num_cols))+j+1] = cur;  //Move current cell left if empty
      			next[(i*(num_cols))+j] = -1;    //Reset current cell when combined
			
		}
	}
	}
}
	//Merge numbers
  	for (int j=(num_cols-1); j>=0; j--)
    	{
	for (int i=0; i<num_rows; i++)
	{
       	 	right =next[((i)*num_cols)+j-1];//really left
        	cur = next[(i*num_cols)+j];
        	if (right == cur && right>0)
        	{
          		next[((i)*num_cols)+j] = (2*right); //Combine current cell with upper cell
      	  		next[(i*num_cols) +j-1] = -1;      //Reset current cell when combined
          		tally = tally + (2*right); //Increase score
			//deleteWhite(num_cols,next);
        	}
	

	}
   	}
for (int boof=0;boof<num_cols;boof++)    //should clear whitespace
{
	for (int j=0; j<(num_cols-1); j++)
    	{
	for (int i=0; i<num_rows; i++)
	{
		int right =next[((i)*num_cols)+j+1];
		int cur = next[(i*num_cols)+j];
		if (right<0)
		{
			next[((i)*(num_cols))+j+1] = cur;  //Move current cell up if empty
      			next[(i*(num_cols))+j] = -1;    //Reset current cell when combined
			
		}
	}
	}
}




//compare new game to old game
    for (i=0; i<num_rows; i++)
    {
      for (j=0; j<num_cols; j++)
      {
    	if (next[(i*num_cols)+j] != (*cur_game).cells[(i*num_cols)+j]) break;
      }
    	if (next[(i*num_cols)+j] != (*cur_game).cells[(i*num_cols)+j]) break;
    }
    	if ((i+1) == num_rows && (j+1) == num_cols) 
	{
	   if (next[(i*num_cols)+j] == (*cur_game).cells[(i*num_cols)+j]) return 0; //End if no change between games.
	}

//Merge games
    for (i=0; i<num_rows; i++)
    {
      for (j=0; j<num_cols; j++)
      {
    (*cur_game).cells[(i*num_cols)+j] = next[(i*num_cols)+j];
      }
    }
    (*cur_game).score = (*cur_game).score + tally; //Increase score

    //temp = legal_move_check(cur_game); //Check if there are any legal moves
    //if (temp == 1) move_w(cur_game);   //Run it again to move tiles again if there is space.
  // rand_new_tile(cur_game);
    return 1;
}

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
    Return 1 if there are possible legal moves, 0 if there are none.
 */
{
     //YOUR CODE STARTS HERE
    int i, j, temp, up, down, left, right;
    int col_size = (*cur_game).cols;
    int row_size = (*cur_game).rows;
    int size = (row_size*col_size);
    int filled=0;
    for (i=0; i<row_size; i++)
    {
      for (j=0; j<col_size; j++)
      {
        temp = (*cur_game).cells[(i*col_size)+j]; //Check if all cells are filled.
        if (temp >= 2) filled++;
      }
    }
    if (filled != size) return 1;
   
    for (i=0; i<row_size; i++)
    {
      for (j=0; j<col_size; j++)
      {
        temp = (*cur_game).cells[(i*col_size)+j];
        if (temp >= 2)
        {
          up = (*cur_game).cells[((i-1)*col_size)+j];
          down = (*cur_game).cells[((i+1)*col_size)+j];
          left = (*cur_game).cells[(i*col_size)+j-1];
          right = (*cur_game).cells[(i*col_size)+j+1];
          if (i==0 && j==0) //Check if I can move from top left box.
          {
            if (down == temp || down < 2) return 1;
            if (right == temp || right < 2) return 1;
          }
          else if (i==0 && j==(row_size-1)) //Check if I can move from top right box.
          {
            if (down == temp || down < 2) return 1;
            if (left == temp || left < 2) return 1;
          }
          else if (i==(col_size-1) && j==0) //Check if I can move from bottom left box.
          {
            if (up == temp || up < 2) return 1;
            if (right == temp || right < 2) return 1;
          }
          else if (i==(col_size-1) && j==(row_size-1)) //Check if I can move from bottom right box.
          {
            if (up == temp || up < 2) return 1;
            if (left == temp || left < 2) return 1;
          }
          else if (i==0) //Check top row
          {
            if (down == temp || down < 2) return 1;
            if (left == temp || left < 2) return 1;
            if (right == temp || right < 2) return 1;
          }
          else if (j==0) // Check left column
          {
            if (up == temp || up < 2) return 1;
            if (down == temp || down < 2) return 1;
            if (right == temp || right < 2) return 1;
          }
          else if (j==(row_size-1)) //Check right column
          {
            if (up == temp || up == -1) return 1;
            if (down == temp || down == -1) return 1;
            if (left == temp || left == -1) return 1;
          }
          else if (i==(col_size-1)) //Check bottom row
          {
            if (up == temp || up < 2) return 1;
            if (left == temp || left < 2) return 1;
            if (right == temp || right < 2) return 1;
          }
          else
          {
            if (up == temp || up < 2) return 1;
            if (down == temp || down < 2) return 1;
            if (left == temp || left < 2) return 1;
            if (right == temp || right < 2) return 1;
          }
        }
      }
    }
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
   
    cell * cell_ptr;
    cell_ptr =     cur_game->cells;
   
    if (cell_ptr == NULL){    
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
   
   
    //check for an empty cell
    int emptycheck = 0;
    int i;
   
    for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
        if ((*cell_ptr) == -1){
                emptycheck = 1;
                break;
        }       
        cell_ptr += 1;
    }
    if (emptycheck == 0){
        printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
        exit(0);
    }
   
    int ind,row,col;
      int num;
    do{
        ind = rand()%((cur_game->rows)*(cur_game->cols));
        col = ind%(cur_game->cols);
        row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
    num = rand()%20;
    if(num <= 1){
        *get_cell(cur_game, row, col) = 4; // 1/10th chance
    }
    else{
        *get_cell(cur_game, row, col) = 2;// 9/10th chance
    }
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr =     cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
   
    printf("\n\n\nscore:%d\n",cur_game->score);
   
   
    printf("\u2554"); // topleft box char
    for(i = 0; i < cols*5;i++)
        printf("\u2550"); // top box char
    printf("\u2557\n"); //top right char
   
   
    for(i = 0; i < rows; i++){
        printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    default:
                        printf("  X  ");

                }

            }
            cell_ptr++;
        }
    printf("\u2551\n"); //print right wall and newline
    }
   
    printf("\u255A"); // print bottom left char
    for(i = 0; i < cols*5;i++)
        printf("\u2550"); // bottom char
    printf("\u255D\n"); //bottom right char
   
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
    int rows,cols;
    char buf[200];
    char garbage[2];
    int move_success = 0;
   
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
    case 'n':
        //get row and col input for new game
        dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
        while (NULL == fgets(buf,200,stdin)) {
            printf("\nProgram Terminated.\n");
            return 0;
        }
       
        if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
        rows < 0 || cols < 0){
            printf("Invalid dimensions.\n");
            goto dim_prompt;
        }
       
        remake_game(&cur_game,rows,cols);
       
        move_success = 1;
       
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

   
   
   
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
         print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
	
	
	

