#include <stdio.h>
#include <stdlib.h>
int prime_sieve(long int limit, short int print, int array[]){
	int temp[100000]; //A temporary array where the primes will be stored until copied to another array.
	temp[0] = 2; //Put the first prime in the array.
	int primecount = 1;
	int size = sizeof(temp) / sizeof(temp[0]); //Get the size of the temporary array.
	for(int i=2;i<=limit;i++){ //Iterate through every number until limit.
		int isPrime = 1; //If this stays 1, it means that the numbe is a prime.
		for(int j=0;temp[j]!=0;j++){ //Iterate through evey known prime.
			if((i % temp[j]) == 0){ //And check for divisibility
				isPrime = 0; //Oops, the number is not a prime. Too bad.
				break; //We'll just check the next one.
			}
		}
		if(isPrime){ //Hooray, the number seems to be a prime.
			temp[primecount] = i; //Add it to the list.
			primecount++; //And increment the number of primes.
		}
	}
	temp[primecount+1] = 0; //Make sure the element after the last prime is 0.
	if(print == 1){ //If we're told to print the primes.
		int count;
		while(temp[count] != 0){           //
			printf("%d ", temp[count]);//Print the primes until we reach a 0, the last element.
			count++;                   //
		}
		printf("\n"); //Newline for prettiness.
	}else{
		for(int i=0;i<=primecount;i++){ //
			array[i] = temp[i];    //Copy every prime to the array.
		}
	}
}
