#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif
int primes[100000];
void* prime_find(void* arg){
	long int num = *((int*) arg); //The number we have to divide.
	int prime; //The prime we will eventually find.
	/*A shitload of primes to check.*/
	int primcount=0;
	while(primes[primcount] != 0){
		if((num % primes[primcount])==0) //Try to divide the number by the largest prime.
		{
			prime = primes[primcount];//
			return (void*) prime;     //If it works, we return the prime.
		}
		primcount++; //If not, check the next prime in the array.
	}
	return NULL;
}
void addSpaces(int num){
	int number = num;
	short digits = 0; //A variable to hold the number of digits.
	char spaces[5] = "     ";
	while(number>=10){
		++digits;
		number/=10;
	}
	spaces[5-digits] = '\0'; //Terminate the string.
	printf("%s", spaces);
}
void factor(long int num){
	long int number = num; //The number to be factored.
	pthread_t thread; //The thread we use to find the prime.
	prime_sieve(num, 0, primes);
	int prime;
	while(number>1){
		pthread_create(&thread, NULL, &prime_find, &number); //Set the thread to work.
		addSpaces(number); //Align the numbers.
		printf("%d|", number);
		meaningOfLife(); //Think about the meaning of life while we wait for the thread to finish.
		pthread_join(thread, (void*) &prime); //get the prime from the thread.
		printf("%d\n", prime);
		number/=prime;
	}
	addSpaces(number);
	printf("1|\n");
	exit(0);
}
int meaningOfLife(){
	//return 42;
	return NULL;
}
