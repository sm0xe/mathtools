#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>
extern long int primecount;
extern short int verbose;
int lastprime;
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
	return orig_num_digits-num_digits;
}
void factor(long long int num){
	long long int orig_num = num; //Store the original number for later usage.
	pthread_t siever; //The thread we use to fill the array with primes.
	pthread_t finder; //The thread we use to find the prime.
	long int prime; //A prime to divide number by.
	long int factors[20];
	int count=0;
	long int results[20];
	int spaces[20];
	primes = malloc(sizeof(long int) * num); //Give the array a size.
	pthread_create(&siever, NULL, &prime_sieve_wrapper, &num);//Set the thread to work.
	while(num>1){
		pthread_create(&finder, NULL, &prime_find, &num); //Set the thread to work.
		//meaningOfLife(); //Think about the meaning of life while we wait for the thread to finish.
		results[count] = num;
		spaces[count] = addSpaces(num, orig_num); //Align the numbers.
		pthread_join(finder, (void*) &prime); //get the prime from the thread.
		num/=prime;
		factors[count] = prime;
		count++;
	}
	quit_siever = 1; //Tell siever to stop.
	if(verbose){
		printf("%d primes generated. Last prime: %d\n\n", primecount, lastprime);
	}
	for(int i=0; i<count ; i++){
		for(int j=0; j<spaces[i] ; j++){
			printf(" ");//Print spaces to align the numbers
		}
		printf("%d|%d\n", results[i], factors[i]);
	}
	for(int i=0; i<addSpaces(num, orig_num) ; i++) {
		printf(" ");;//Align the number
	}
	printf("1|\n");
	pthread_join(siever, NULL);//Wait for the thread to finish
	free(primes); //Free up memory.
	exit(0);
}
int meaningOfLife(){
	return 42;
}
