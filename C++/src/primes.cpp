#include <iostream>
#include <vector>
#include <signal.h>
using namespace std;
int primecount;
extern int lastprime;
extern short int stats;
extern sig_atomic_t quit_siever;
extern short int prime_finished;

void prime_sieve(long long int limit){
	if(limit==1){
		cout << "A prime number must be more than 1." << endl;
		exit(0);
	}
	vector<int> temp;
	temp.push_back(2);
	cout << "2 ";
	int i=3;
	primecount=1;
	do{
		short int isPrime = 1;
		for(int j=0; j<temp.size(); j++){
			if((i % temp.at(j)) == 0){
				isPrime = 0;
				break;
			}
		}
		if(isPrime){
			temp.push_back(i);
			primecount++;
			cout << i << " ";
		}
		i+=2;
	}while(i<=limit);
	cout << endl;
}
void prime_sieve(long long int limit, vector<long long int>* prime_array){
	quit_siever = 0;
	(*prime_array).push_back(2);
	int i=3;
	primecount=1;
	do{
		short int isPrime = 1;
		for(int j=0; j<(*prime_array).size(); j++){
			if((i % (*prime_array).at(j)) == 0){
				isPrime = 0;
				break;
			}
			else if(quit_siever == 1) break;
		}
		if(isPrime){
			(*prime_array).push_back(i);
			primecount++;
			if(stats) lastprime = i;
		}
		i+=2;
	}while(i<=limit && (quit_siever == 0));
	if(quit_siever==0) prime_finished=1;
}
