/*        
 *
 *
 * INTRO PARAGRAPH: This code seeds a random number generator, generates 4 random numbers, and accepts guesses from main.c. set_seed accepts a seed int from the user, and seeds a random number generator with
 * it. If the seed is bad, it asks for a new one. start_game generates 4 random solution numbers, and stores them in this program, and sends them to main.c as well. make_guess accepts 4 guess numbers from the
 * user. It provides feedback on whether the numbers are perfect or in the wrong spot, and passes the guesses back to main.c. It will deny any unnacptable guesses.
 * PARTNERS: briants2, jrhaag2
 *
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
    int seed,check;
    char post[2];
    check =sscanf(seed_str,"%d%1s", &seed, post);    //Accepts a seed value from user
    if (check !=1)
    {
        printf("set_seed: invalid seed\n");    //Ask for a new seed if original is invalid
        return 0;
    }
    else
    {
        srand(seed);    //Seed the random number generator.
        return 1;
    }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game (int* one, int* two, int* three, int* four)
{
    solution1=(rand()%8+1);    //Create 4 random numbers between 1 and 8
    solution2=(rand()%8+1);
    solution3=(rand()%8+1);
    solution4=(rand()%8+1);
 
    guess_number=1;    //Initialize guess counter
    *one=solution1;    //Pass solutions to main.c
    *two=solution2;
    *three=solution3;
    *four=solution4;
  
 
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
    int w,x,y,z;
    int perfect=0;
    int right=0;
    int sol1=solution1;
    int sol2=solution2;
    int sol3=solution3;
    int sol4=solution4;
 
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
    char postGuess[2];
    int check =sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, postGuess);    //Get guesses from user
    if (check !=4 || 8<w || w<1 || 8<x || x<1 || 8<y || y<1 || 8<z || z<1)
    {
        printf("make_guess: invalid guess\n");        //Ask for new guess if input is invalid
        return 0;
    }
    else
    {
//Pass guesses to main.c
    *one = w;
    *two = x;
    *three = y;
    *four = z;
    
//Check if guesses are perfect
        if (w==sol1)
        {
            perfect++;
        w=9;
            sol1=14;
        }
    
        if (x==sol2)
        {
            perfect++;
        x=10;
            sol2=100;
        }
    
        if (y==sol3)
        {
            perfect++;
            y=11;
        sol3=110;
        }
    
        if (z==sol4)
        {
            perfect++;
            z=12;
        sol4=120;
        }

//checking for rights for w
        if (w==sol2)
        {
            right++;
            sol2=23;
        }
    
        else if (w==sol3)
        {
            right++;
            sol3=22;
        }
        else if (w==sol4)
        {
            right++;
            sol4=21;
        }
//checking for rights with x
        if (x==sol1)
        {
            right++;
            sol1=23;
        }
    
        else if (x==sol3)
        {
            right++;
            sol3=22;
        }
        else if (x==sol4)
        {
            right++;
            sol4=21;
        }
//checking for rights with y
        if (y==sol1)
        {
            right++;
            sol1=23;
        }
    
        else if (y==sol2)
        {
            right++;
            sol2=22;
        }
        else if (y==sol4)
        {
            right++;
            sol4=21;
        }    
//checking for rights with z
        if (z==sol1)
        {
            right++;
            sol1=23;
        }
    
        else if (z==sol2)
        {
            right++;
            sol2=22;
        }
        else if (z==sol3)
        {
            right++;
            sol3=21;
        }

      
    

     }
 
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

//  Output status of user guesses.
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guess_number,perfect,right);
    //printf("%1s",guess_str);
        guess_number++;
    return 1;
}

	
	
	

