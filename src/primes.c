#include <stdio.h>
#include <stdlib.h>
int prime_sieve(long int limit, short int print, int array[]){
	int temp[1000];
	temp[0] = 2;
	int primcount = 1;
	int size = sizeof(temp) / sizeof(temp[0]);
	for(int i=2;i<=limit;i++){
		int isPrime = 1;
		for(int j=0;temp[j]!=0;j++){
			if((i % temp[j]) == 0){
				isPrime = 0;
				break;
			}
		}
		if(isPrime){
			temp[primcount] = i;
			primcount++;
		}
	}
	temp[primcount+1] = 0;
	if(print == 1){
		int count;
		while(temp[count] != 0){
			printf("%d ", temp[count]);
			count++;
		}
		printf("\n");
	}else{
		for(int i=0;i<=primcount;i++){
			array[i] = temp[i];
		}
	}
}
