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
template<typename T> void prime_sieve(vector<T>* prime_array, T limit){
	vector<bool> isprime(limit+1,true);
	for(T i=2; i<=limit; i++){
	    if(isprime.at(i)==true){
	    	(*prime_array).push_back(i);
		for(T j=i*i; j<=limit; j+=i){
		    isprime.at(j)=false;
		}
	    }
	}
}
template<typename T> T mod_exp(T m, T e, T n){ //TODO: Convert to square-and-multiply algorithm
	T z=1;
	for(T i=0; i<e; i++){
	    z=(z*m)%n;
	}
	return z;
}
template<typename T> bool primecheck(T cand, T a, T u, T v){
	bool cont=false;
	long long int b=mod_exp<long long int>(a,u,cand);
	//cout << a << "^(" << u << ")=" << b <<" mod "<< cand << endl;
	if(b==1 || b==cand-1){return true;}
	for(int j=0;j<v;j++){
	    b=mod_exp<long long int>(b,2,cand);
	    //cout << a << "^(2^" << j+1<< "*" << u << ")=" << b <<" mod "<< cand << endl;
	    if(b==cand-1){
		return true;
	    }
	    else if(b==1){
		return false;
	    }
    	}
	return false;
}
// Miller-Rabin primality test run k times
bool primecheck_k(long long int cand, int k){
    	vector<int> primes;
	prime_sieve<int>(&primes,k);
	int v=0;
	long long int u=cand-1;
	while(!(u&1)){ // As long as candidate is even
	    v++;
	    u/=2;
	}
	//cout << "u: " << u << " v: " << v << endl;
	for(int i=0; i<primes.size(); i++){
	    if(!primecheck<long long int>(cand,primes.at(i),u,v)) return false;
	}
	return true;
}
