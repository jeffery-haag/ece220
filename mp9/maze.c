#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/* This code solves a maze. createMaze allocates memory for the maze structure and the 2D array for the actual maze.
 * It also pulls in a text file with the actual maze, and fills the structure with relevant info.
 * destroyMaze clears all memory associated with the maze.
 * printMaze prints the maze to console.
 * solveMazeDFS is a recursive function that goes through possible paths on the maze, eventually reaching the end.
 */

/*
* createMaze -- Creates and fills a maze structure from the given file
* INPUTS:       fileName - character array containing the name of the maze file
* OUTPUTS:      None
* RETURN:       A filled maze structure that represents the contents of the input file
* SIDE EFFECTS: None
*/
maze_t * createMaze(char * fileName)
{	
  // Your code here. Make sure to replace following line with your own code.
  char temp[4000];
  int i, j;
  //int wide, high;
  char more[4000];
 
  FILE* file = fopen(fileName, "r");
  while(fgets(&temp[i++], sizeof(char)+1, file) != NULL); //Get maze file
  i=0;

  fclose(file);
   
	char garb;
	maze_t * game = (maze_t*)malloc(   sizeof(maze_t) );

    sscanf(temp, "%d%d%c%[^@]s", &((*game).width), &((*game).height),&garb, more); //Get width/height and store the rest

	(*game).cells = (char**)malloc(((*game).width)*(sizeof(char*)+1)); //Create game cell columns
    for (i=0; i<((*game).width+1); i++)
    {
      (*game).cells[i] = (char*)malloc(((*game).height)*sizeof(char));	//Create game cell rows
    }
   
	

    for (i=0; i<=(*game).height; i++)
    {
      for (j=0; j<=(*game).width; j++)
      {
        (*game).cells[i][j] = more[( (i*  ((*game).width+1) )  +j   )]; //Fill Cells
      }
    }
    for (i=0; i<=(*game).height; i++)
    {
      for (j=0; j<((*game).width); j++)
      {
        if ((*game).cells[i][j] == 'S') //Find start cell
        {
          (*game).startColumn = j;
          (*game).startRow = i;
	
        }
        if ((*game).cells[i][j] == 'E') //Find ending cell
        {
          (*game).endColumn = j;
          (*game).endRow = i;
        }
      }
    }
    return game;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    int i;
    for (i=0; i<=(*maze).height; i++)
    {
      free(maze->cells[i]); //Free array rows
    }
    free(maze->cells);	//Free array columns
    free(maze); //Free maze structure
    maze=NULL;  //Free maze pointer
    return;
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int i, j;
    for (i=0; i<(*maze).height; i++)
    {
      for (j=0; j<(*maze).width; j++)
      {
        printf("%c", (*maze).cells[i][j]); //Print maze
      }
      printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int virgin=0;
int pass=1;
int solveMazeDFS(maze_t * maze, int col, int row)
{
    int y,x;
        if (virgin ==0)
    {
        x=(*maze).startColumn; //Set start point
              y=(*maze).startRow;
        virgin=1;
	pass=0;
    }
    else
    {
        y=row;
        x=col;
	pass=1;
    }


//&& (*maze).cells[y][x] !='S'
    if (y<0 || x<0 || y >= (*maze).height || x>=(*maze).width  )return 0; //Check for out ouf bounds
    else if ( (*maze).cells[y][x] !=' ' && (*maze).cells[y][x] !='E'   && (*maze).cells[y][x] !='S' )return 0; //Check if wall
    else if ((*maze).cells[y][x] =='S' && pass==1)return 0; //Check if S space
    else if (y==(*maze).endRow && x==(*maze).endColumn)return 1; //Check if E
    else if ((*maze).cells[y][x] =='E')return 1; //Check if E
  
    if ((*maze).cells[y][x]!='S' && (*maze).cells[y][x]!='E')(*maze).cells[y][x]='*'; //Fill with star for good space
  
    if (solveMazeDFS(maze, x, (y-1))==1)return 1;   //up
    if (solveMazeDFS(maze, x, (y+1))==1)return 1;  //down
    if (solveMazeDFS(maze, (x-1), y)==1)return 1;  //left
    if (solveMazeDFS(maze, (x+1), y)==1)return 1;    //right
    (*maze).cells[y][x]='~'; //Backtrack character
    return 0;

  
}


