#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>
extern long int primecount;
extern short int stats; //Whether verbose mode is set or not
extern short int factor_print_mode; //What kind of output is expected: 0 for only division, 1 for only a list of factors, 2 for both
short int prime_finished=0; //Whether prime generation finished prematurely (0) or because limit was reached (1)
int lastprime; //Last generated prime. Used in statistics.
short int quit_siever; //The siever thread stops when this is set to 1
int *primes; //An array for the primes we will use to factor the number.
void* prime_sieve_wrapper(void* arg){
	long int num = *((int*) arg);
	prime_sieve(num, primes); //Fill the array with primes.
	return NULL;
}
void* prime_find(void* arg){
	long int num = *((int*) arg); //The number we have to divide.
	long int prime; //The prime we will eventually find.
	int prime_findcount=0;
	while(1){
		if(primecount == prime_findcount){ //If there is no prime number to check, check again.
			usleep(1);
			continue;
		}
		//printf("DEBUG: Trying: %d\n", primes[prime_findcount]); //DEBUG
		if(num % primes[prime_findcount]==0){ //Try to divide the number by the smallest prime.
			prime = primes[prime_findcount];//
			return (void*) prime;     //If it works, we return the prime.
		}
		else{ //If not, try another prime
			if(primes[prime_findcount] < num) prime_findcount++; //If the primes is smaller than the number we are dividing, keep going..
			else if(primes[prime_findcount] > num) prime_findcount--; //If the primes is larger than the number, go back.
		}
	}
	return NULL;
}
int addSpaces(long int num, long int orig_num){
	short orig_num_digits = 0; //A variable to hold the number of digits in orig_num.
	short num_digits = 0; //A variable to hold the number of digits in num.
	while(orig_num>=10){//Count digits in orig_num.
		++orig_num_digits;
		orig_num/=10;
	}
	while(num>=10){ //Count digits in num. 
		++num_digits;
		num/=10;
	}
	return orig_num_digits-num_digits; //Return difference
}
void factor(long long int num){
	long long int orig_num = num; //Store the original number for later usage.
	pthread_t siever; //The thread we use to fill the array with primes.
	pthread_t finder; //The thread we use to find the prime.
	long int prime; //A prime to divide number by.
	long int factors[20]; //Array for storing the number's factors
	int count=0;
	long int results[20]; //Array for storing the results during division
	int spaces[20];
	primes = malloc(sizeof(long int) * num); //Give the array a size.
	pthread_create(&siever, NULL, &prime_sieve_wrapper, &num);//Set the thread to work.
	while(num>1){
		pthread_create(&finder, NULL, &prime_find, &num); //Set the thread to work.
		//meaningOfLife(); //Think about the meaning of life while we wait for the thread to finish.
		results[count] = num; //Add the current number to the result list
		spaces[count] = addSpaces(num, orig_num); //Align the numbers.
		pthread_join(finder, (void*) &prime); //get the prime from the thread.
		num/=prime;
		factors[count] = prime; //Add found prime number to list of factors
		count++;
	}
	quit_siever = 1; //Tell siever to stop.
	if(stats){ //If user has asked for statistics, print amount of primes generated, last generated prime and whether prime generation finished prematurely or not
		printf("%d primes generated. Last prime: %d.", primecount, lastprime);
		if(prime_finished) printf(" Prime generation reached set limit.");
		else printf(" Prime generation finished prematurely.");
		printf("\n\n");
	}
	if(factor_print_mode==0 || factor_print_mode==2){ //User wants only division or both
		for(int i=0; i<count ; i++){
			for(int j=0; j<spaces[i] ; j++){
				printf(" ");//Print spaces to align the numbers
			}
			printf("%d|%d\n", results[i], factors[i]); //Prints current number in the division and its factor
		}
		for(int i=0; i<addSpaces(num, orig_num) ; i++) {
			printf(" ");;//Align the number
		}
		printf("1|\n");
	}
	if(factor_print_mode==1 || factor_print_mode==2){ //User wants only a list of factors or both.
		if(factor_print_mode) printf("\n"); //If the user wants both, print a newline for prettiness.
		for(int i=0; i<count ; i++){
			printf("%d ", factors[i]); //Print all factors with a space between
		}
		printf("\n"); //Newline for prettiness
	}
	pthread_join(siever, NULL);//Wait for the thread to finish
	free(primes); //Free up memory.
	exit(0);
}
int meaningOfLife(){
	return 42;
}
