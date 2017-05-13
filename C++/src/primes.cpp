#include <iostream>
#include <vector>
#include <signal.h>
#include <math.h>
using namespace std;
int primecount;
extern int lastprime;
extern short int stats;
extern sig_atomic_t quit_siever;
extern short int prime_finished;
extern long long int *limit;

void prime_sieve(long long int limit){
	if(limit==1){
		cout << "A prime number must be more than 1." << endl;
		exit(0);
	}
	primecount=1;
	vector<bool> isprime(limit,true);
	if(isprime.max_size()<limit){
	    limit = isprime.max_size();
	}
	for(long long int i=2; i<limit; i++){
	    if(isprime.at(i)==true){
		primecount++;
		cout << i << " ";
		for(long long int j=i*i; j<limit; j+=i){
		    isprime.at(j)=false;
		}
	    }
	}
	cout << endl;
}
void prime_sieve(vector<long long int>* prime_array){
	quit_siever = 0;
	primecount=0;
	vector<bool> isprime(*limit+1,true);
	for(long long int i=2; i<=*limit; i++){
	    if(isprime.at(i)==true){
	    	(*prime_array).push_back(i);
		primecount++;
		if(stats) lastprime=i;
		for(long long int j=i*i; j<=*limit; j+=i){
		    isprime.at(j)=false;
		}
	    }
	    if(quit_siever==1) break;
	}
	if(quit_siever==0) prime_finished=1;
}
