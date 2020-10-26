#include <stdio.h>
#include <stdlib.h>

//this code will print a given line of pascals triangle speicified by the user by calculating each one while stepping through a for loop. FIrst one is outputted because the formula doesnt work for one
//then is stepds through until the counter is the same nunber as the specified row. It adds a spacer after each number for asthetic and readability.
// At the end it outputs another one just in case the equation doesnt work that high
//partners jrhaag2, briants2


int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);
  if(row<0)printf("Invalid Input!");//gets the number



  unsigned long value=1;
  for (int i=0;i<row;i++)//loop to calculate number
    {
      if (i==0)printf("1 ");//just outs a one for i=0 because equation broken
      else{
     
	value=((value*(row+1-i))/i);//calculating the number in row
      printf("%lu",value);
      printf(" ");
      }
    }
  printf("1"); //finsihes line   

  return 0;
}
