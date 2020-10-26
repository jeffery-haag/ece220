/* This program creates funtions that run The Game of Life. countLiveNeighbor counts the number of living creatures next
 * to a given cell. updateBoard loads the next board state in, using countLiveNeighbor to get the neighbor info. Depending on 
 * how many cells are alive, it sets the current cell to alive or dead. aliveStatus figures out when the game ends.
 * Partners: jrhaag2, briants2
 */ 
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col)
{

    int liveNeighbors=0;
    int chkr=0;
    //top left
    if (row==0&&col==0)
    {
        //check to right
        chkr=board[(row*boardColSize+(col+1))];
        liveNeighbors=liveNeighbors+chkr;
        //check beneath
        chkr=board[(((row+1)*boardColSize)+col)];
        liveNeighbors=liveNeighbors+chkr;
        //check beneath and right
        chkr=board[((row+1)*boardColSize)+(col+1)];
        liveNeighbors=liveNeighbors+chkr;
	
        return liveNeighbors;  
    }
    //top right
    else if(row==0&&col==(boardColSize-1))
    {
        //check to left
        chkr=board[((row*boardColSize)+(col-1))];
        liveNeighbors=liveNeighbors+chkr;
        //chck beanth and left
        chkr=board[(((row+1)*boardColSize)+(col-1))];
        liveNeighbors=liveNeighbors+chkr;
        //check beneath
        chkr=board[(((row+1)*boardColSize)+col)];
        liveNeighbors=liveNeighbors+chkr;
	
        return liveNeighbors;
    }
    //bottom left
    else if(col==0&&row==(boardRowSize-1))
    {
        //one above our target
        chkr=board[(((row-1)*boardColSize)+col)];
        liveNeighbors=liveNeighbors+chkr;
        //check right and above target
        chkr=board[(((row-1)*boardColSize)+(col+1))];
        liveNeighbors=liveNeighbors+chkr;
        //check to right
        chkr=board[(row*boardColSize+(col+1))];
        liveNeighbors=liveNeighbors+chkr;

        return liveNeighbors;
    }
    //bottom right
    else if(col==(boardColSize-1)&&row==(boardRowSize-1))
    {
        //check left and above target
        chkr=board[(((row-1)*boardColSize)+(col-1))];
        liveNeighbors=liveNeighbors+chkr;
        //one above our target
        chkr=board[(((row-1)*boardColSize)+col)];
        liveNeighbors=liveNeighbors+chkr;
        //check to left
        chkr=board[((row*boardColSize)+(col-1))];
        liveNeighbors=liveNeighbors+chkr;

        return liveNeighbors;
    }
    //check top
    else if(row==0)
    {
        //check to left
        chkr=board[((row*boardColSize)+(col-1))];
        liveNeighbors=liveNeighbors+chkr;
        //check to right
        chkr=board[(row*boardColSize+(col+1))];
        liveNeighbors=liveNeighbors+chkr;
        //chck beanth and left
        chkr=board[(((row+1)*boardColSize)+(col-1))];
        liveNeighbors=liveNeighbors+chkr;
        //check beneath
        chkr=board[((((row+1)*boardColSize)+col))];
        liveNeighbors=liveNeighbors+chkr;
        //check beneath and right
        chkr=board[(((row+1)*boardColSize)+(col+1))];
        liveNeighbors=liveNeighbors+chkr;

        return liveNeighbors;
    }
    //right side
    else if(col==(boardColSize-1))
    {
        //check left and above target
        chkr=board[(((row-1)*boardColSize)+(col-1))];
        liveNeighbors=liveNeighbors+chkr;
        //one above our target
        chkr=board[(((row-1)*boardColSize)+col)];
        liveNeighbors=liveNeighbors+chkr;
        //check to left
        chkr=board[((row*boardColSize)+(col-1))];
        liveNeighbors=liveNeighbors+chkr;
        //chck beanth and left
        chkr=board[(((row+1)*boardColSize)+(col-1))];
        liveNeighbors=liveNeighbors+chkr;
        //check beneath
        chkr=board[(((row+1)*boardColSize)+col)];
        liveNeighbors=liveNeighbors+chkr;
        return liveNeighbors;
    }
    //left side
    else if(col==0)
    {
        //one above our target
        chkr=board[(((row-1)*boardColSize)+col)];
        liveNeighbors=liveNeighbors+chkr;
        //check right and above target
        chkr=board[(((row-1)*boardColSize)+(col+1))];
        liveNeighbors=liveNeighbors+chkr;
        //check to right
        chkr=board[(row*boardColSize+(col+1))];
        liveNeighbors=liveNeighbors+chkr;
        //check beneath
        chkr=board[(((row+1)*boardColSize)+col)];
        liveNeighbors=liveNeighbors+chkr;
        //check beneath and right
        chkr=board[(((row+1)*boardColSize)+(col+1))];
        liveNeighbors=liveNeighbors+chkr;
      
        return liveNeighbors;
    }
    //bottom
    else if(row==(boardRowSize-1))
    {
        //check left and above target
        chkr=board[(((row-1)*boardColSize)+(col-1))];
        liveNeighbors=liveNeighbors+chkr;
        //one above our target
        chkr=board[(((row-1)*boardColSize)+col)];
        liveNeighbors=liveNeighbors+chkr;
        //check right and above target
        chkr=board[(((row-1)*boardColSize)+(col+1))];
        liveNeighbors=liveNeighbors+chkr;
        //check to left
        chkr=board[((row*boardColSize)+(col-1))];
        liveNeighbors=liveNeighbors+chkr;
        //check to right
        chkr=board[(row*boardColSize+(col+1))];
        liveNeighbors=liveNeighbors+chkr;

        return liveNeighbors;
    }
    else
    {

    //check left and above target
    chkr=board[(((row-1)*boardColSize)+(col-1))];
    liveNeighbors=liveNeighbors+chkr;
    //one above our target
    chkr=board[(((row-1)*boardColSize)+col)];
    liveNeighbors=liveNeighbors+chkr;
    //check right and above target
    chkr=board[(((row-1)*boardColSize)+(col+1))];
    liveNeighbors=liveNeighbors+chkr;
    //check to left
    chkr=board[((row*boardColSize)+(col-1))];
    liveNeighbors=liveNeighbors+chkr;
    //check to right
    chkr=board[((row*boardColSize)+(col+1))];
    liveNeighbors=liveNeighbors+chkr;
    //chck beanth and left
    chkr=board[(((row+1)*boardColSize)+(col-1))];
    liveNeighbors=liveNeighbors+chkr;
    //check beneath
    chkr=board[((((row+1)*boardColSize)+col))];
    liveNeighbors=liveNeighbors+chkr;
    //check beneath and right
    chkr=board[(((row+1)*boardColSize)+(col+1))];
    liveNeighbors=liveNeighbors+chkr;


    return liveNeighbors;
    }
    return liveNeighbors;
}

/*-
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize)
{
    int col, row, i;
    int numNeigh;
    int boardSize = ((boardColSize)*(boardRowSize));
    int boardNew[boardSize];

    for (row=0; row<boardRowSize; row++)	//Iterate through all rows
    {
        for(col=0; col<boardColSize; col++)	//Iterate through all columns
        {
            numNeigh = countLiveNeighbor(board, boardRowSize, boardColSize, row, col); //Get number of living neighbors
          
            if (numNeigh<2 || numNeigh>3)
            {
                boardNew[((row*boardColSize)+col)] = 0;	//Kill cell if <2 or >3 living neighbors
            }	
            else if (numNeigh == 3)
            {
                boardNew[((row*boardColSize)+col)] = 1;	//Make cell alive of 3 living neighbors
            }
        else if (numNeigh == 2)
            {
                boardNew[((row*boardColSize)+col)] = board[((row*boardColSize)+col)];	//Keep current cell status if 2 neighbors
            }
        }
    }

    for (i=0;i<boardSize;i++)
    {
    board[i] = boardNew[i];	//Update board
    }

}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize)
{
    int count=0;
    int i, j;
    int boardSize=(((boardRowSize)*(boardColSize)));
    int boardCopy[boardSize];
   
    for(j=0; j<boardSize; j++)
    {
    boardCopy[j] = board[j];	//Copy current board into temp array
    }

    updateBoard(boardCopy, boardRowSize, boardColSize);	//Update current board

    for (i=0;i<boardSize;i++)
        {
            //boardCopy[i]=board[i];
            count=(boardCopy[i]-board[i]);	//check if all cells keep current status for next board
            //board[i]=boardCopy[0];
            if (count!=0)return 0;
        }
    return 1;
}
