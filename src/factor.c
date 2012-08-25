#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void* prime_find(void* arg){
	int num = *((int*) arg);
	int prime;
	int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997 };
	short int primcount = (sizeof(primes) / sizeof(primes[0]));
	while(1){
		if((num % primes[primcount])==0)
		{
			prime = primes[primcount];
			return (void*) prime;
			break;
		}
		--primcount;
	}
	return NULL;
}
void addSpaces(int num){
	int number = num;
	short digits = 0; //a variable to hold the number of digits
	char spaces[5] = "     "; //a character string containing 5 spaces
	while(number>=10){
		++digits; //increment digits
		number/=10;  //and divide he number by 10
	}
	spaces[5-digits] = '\0'; //terminate the string
	printf("%s", spaces);
}
void factor(int num){
	long int number = num;
	pthread_t thread;
	int prime;
	while(number>1){
		pthread_create(&thread, NULL, &prime_find, &number);
		addSpaces(number);
		printf("%d|", number);
		pthread_join(thread, (void*) &prime);
		printf("%d\n", prime);
		number/=prime;
	}
	addSpaces(1);
	printf("1|\n");
	exit(0);
}
