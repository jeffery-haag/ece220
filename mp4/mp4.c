#include <stdlib.h>
#include <stdio.h>



//THis will find the partial primes between two numbrs inputed by the user. It does it by checking the first number for being a prime by using the prime method, if not it will test to find the multoples of it, if there are only two and theyre both primes it outputs the number and increments to the next and checks it aswell.
//partners jrhaag2,briants1

int is_prime(int number);
int print_semiprimes(int a, int b);

int chk1,chk2;
int good;
int bol=0;
int primeChk;
int main()
{   
   int a, b;
   
   

   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   print_semiprimes(a,b);
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)  //this checks to see if prime and is referenced by others
{
int bolls=1;
  for (primeChk=2;primeChk<number;primeChk++)
	{
	
	int checker=number%primeChk;
	if (checker==0)bolls=0;
	
	}
return bolls;
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)          
{
	int num,chk;
	int good=0;
	int failsafe=0;
	bol=0;
	for(num=a;num<=b;num++)	//steps through a-b
	{
		chk=is_prime(num);
		if (chk==0)		//checks to see if its prime
		{   
			for(int c=2;c<=num;c++)		//steps through then finds the multiples
			{	
				if (bol==1)
				{
					failsafe=1;	//this tests to see if theres mroe than two multiples
					
					
					
				}
				else if (num%c==0)
				{
					chk=is_prime(c);		//checks to see if both multiples are primes
					chk2=is_prime(num/c);
					if(chk==1&&chk2==1)bol=1;
					
				}
				if(failsafe==0&&bol==1)
				{
					
					good=1;				//prints if it meets conditions
					printf("%d ",num);
				}	
				
				
			}	
			failsafe=0;
				bol=0;

		}
		
	}
	
	return (good);		//returns 1 if theres a partial prime 0 if not
}



