#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
long int primecount;
extern short int quit_siever; //The siever thread stops when this is set to 1.
void prime_sieve(long int limit, ...){
	va_list argp; //The optional argument (...)
	va_start(argp, limit);
	long int prime_array = va_arg(argp, long int); //Get the array.
	va_end(argp); //Cleanup
	quit_siever = 0;
	int *array;
	short int print = 0;
	int *temp = NULL;
	if(prime_array == 0){ //If there were no arrays to get
		print = 1; //Go into print mode, instead of copying the primes to an array, they will be printed directly to the screen.
		if(limit==1){ //If we were told to find primes that are less or equal to 1, print polite error.
			printf("A prime number must be more than 1.\n");
			exit(0);
		}
		temp = malloc(sizeof(long int) * limit); //A temporary array where the primes will be stored temporarily.
		array = temp; //Points to the temporary array.
		*(array) = 2; //Put the first prime in the array.
		printf("2 "); //and print it to the screen.
	}else{
		array = (int *)prime_array; //Points to prime_array.
		*(array) = 2; //Put the first prime in the array.
	}
	int i=3;
	primecount=1;
	do{ //Iterate through every number until limit.
		int isPrime = 1; //If this stays 1, it means that the number is a prime.
		for(int j=1;*(array+j)!=0;j++){ //Iterate through every known prime.
			if((i % *(array+j)) == 0){ //And check for divisibility
				isPrime = 0; //Oops, the number is not a prime. Too bad.
				break; //We'll just check the next one.
			}
		}
		if(isPrime){ //Hooray, the number seems to be a prime.
			*(array+primecount) = i; //Add it to the list.
			primecount++; //And increment the number of primes.
			if(print == 1)
				printf("%d ", i);
		}
		i+=2;
	}while(i<=limit && (quit_siever == 0));
	if(print == 1) printf("\n"); //Newline for prettiness.

	free(temp); //Free up memory
}
