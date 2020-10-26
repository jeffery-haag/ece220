#include "sudoku.h"
/*
 * This program solves a sudoku puzzle. Three functions check if the given value  is valid, and are combined
 * into is_val_valid, which returns 1 if the given value valid. solve_sudoku solves a given sudoku puzzle recursively. 
 * It uses is_val_valid to test an iterated value. 
 * Partners: briants2, jrhaag2
 */

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int rowRest;
int colRest;
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  int k;
  for (k=0; k<9; k++)
  {
     if (val == sudoku[i][k]) return 1;
  }
  return 0;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  int k;
  for (k=0; k<9; k++)
  {
     if (val == sudoku[k][j]) return 1;
  }
  return 0;
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
  
  assert(i>=0 && i<9);

  int k,h;
  if (i<3 && j<3)
  {
    for (k=0; k<3; k++)
    {
        for (h=0; h<3; h++)
        {
        if (val == sudoku[k][h]) return 1;
        }
     }
  }
  if (i<6 && i>=3 && j<3)
  {
    for (k=3; k<6; k++)
    {
        for (h=0; h<3; h++)
        {
        if (val == sudoku[k][h]) return 1;
        }
     }
  }
  if (i<9 && i>=6 && j<3)
  {
    for (k=6; k<9; k++)
    {
        for (h=0; h<3; h++)
        {
        if (val == sudoku[k][h]) return 1;
        }
     }
  }
  if (i<3 && j<6 && j>=3)
  {
    for (k=0; k<3; k++)
    {
        for (h=3; h<6; h++)
        {
        if (val == sudoku[k][h]) return 1;
        }
     }
  }
  if (i<6 && i>=3 && j<6 && j>=3)
  {
    for (k=3; k<6; k++)
    {
        for (h=3; h<6; h++)
        {
        if (val == sudoku[k][h]) return 1;
        }
     }
  }
  if (i<9 && i>=6 && j<6 && j>=3)
  {
    for (k=6; k<9; k++)
    {
        for (h=3; h<6; h++)
        {
        if (val == sudoku[k][h]) return 1;
        }
     }
  }
  if (i<3 && j<9 && j>=6)
  {
    for (k=0; k<3; k++)
    {
        for (h=6; h<9; h++)
        {
        if (val == sudoku[k][h]) return 1;
        }
     }
  }
  if (i<6 && i>=3 && j<9 && j>=6)
  {
    for (k=3; k<6; k++)
    {
        for (h=6; h<9; h++)
        {
        if (val == sudoku[k][h]) return 1;
        }
     }
  }
  if (i<9 && i>=6 && j<9 && j>=6)
  {
    for (k=6; k<9; k++)
    {
        for (h=6; h<9; h++)
        {
        if (val == sudoku[k][h]) return 1;
        }
     }
  }
  return 0;
}

// Function: is_val_valid
// Return 1 if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  int temp;
  temp = is_val_in_row(val, i, sudoku);
  if (temp != 0)return 0;
  temp = is_val_in_col(val, j, sudoku);
  if (temp != 0)return 0;
  temp = is_val_in_3x3_zone(val, i, j, sudoku);
  if (temp != 0) return 0;

  return 1;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) //TWOFIX
{

  int row, col, temp, k, check=0;
  int row1=-1;
  int col1=-1;

//Check if board is filled.
  temp = 0;
  for (row=0; row<9; row++)
  {
     for (col=0; col<9; col++)
     {
    temp = temp + sudoku[row][col];
     }
  }
  if (temp == 405) return 1;

//Find first empty space
  for (row=0; row<9; row++)
  {
     for (col=0; col<9; col++)
     {
    	if ((sudoku[row][col]) == 0)
    	{
         	row1 = row;
          	col1 = col;
         	
    	}
	if(col1 > -1)break;
     }
	if (row1 > -1)break;
  }

//Fill a number at the empty space
  for (k=1; k<=9; k++)
  {
     temp = is_val_valid(k, row1, col1, sudoku);
     if (temp == 1)
     {
         sudoku[row1][col1] = k;	//Fill board with guessed answer
         if (solve_sudoku(sudoku) == 1) return 1;  //Recursion
         sudoku[row1][col1] = 0;    //Backtracking
	
     }
  }

  return 0;
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
