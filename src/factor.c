#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif
int* primes; //An array for the primes we will use to factor the number.
void* prime_find(void* arg){
	long int num = *((int*) arg); //The number we have to divide.
	long int prime; //The prime we will eventually find.
	int primecount=0;
	while(primes[primecount] != 0){
		if((num % primes[primecount])==0){ //Try to divide the number by the smallest prime.
			prime = primes[primecount];//
			return (void*) prime;     //If it works, we return the prime.
		}
		primecount++; //If not, check the next prime in the array.
	}
	return NULL;
}
void addSpaces(int num, long int orig_num){
	short orig_num_digits = 1; //A variable to hold the number of digits in orig_num.
	short num_digits = 1; //A variable to hold the number of digits in num.
	while(orig_num>=10){//Count digits in orig_num.
		++orig_num_digits;
		orig_num/=10;
	}
	while(num>=10){ //Count digits in num. 
		++num_digits;
		num/=10;
	}
	for(int i=0;i<orig_num_digits - num_digits;i++){
		printf(" ");//Print spaces to align the numbers
	}
}
void factor(long int num){
	long int orig_num = num; //Store the original number for later usage.
	pthread_t finder; //The thread we use to find the prime.
	long int prime; //A prime to divide number by.
	primes = malloc(sizeof(long int) * num); //Give the array a size.
	prime_sieve(num, primes); //Fill the array with primes.
	while(num>1){
		pthread_create(&finder, NULL, &prime_find, &num); //Set the thread to work.
		addSpaces(num, orig_num); //Align the numbers.
		printf("%d|", num);
		meaningOfLife(); //Think about the meaning of life while we wait for the thread to finish.
		pthread_join(finder, (void*) &prime); //get the prime from the thread.
		printf("%d\n", prime);
		num/=prime;
	}
	addSpaces(num, orig_num);//Align the number
	printf("1|\n");
	free(primes); //Free up memory.
	exit(0);
}
int meaningOfLife(){
	return 42;
}
