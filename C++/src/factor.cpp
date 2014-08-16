#include <vector>
#include <thread>
#include <future>
#include <iostream>

using namespace std;
extern long int primecount;
extern short int stats;
extern short int factor_print_mode;
short int prime_finished=0;
int lastprime;
short int quit_siever;
vector<int> primes;
void* prime_sieve_wrapper(void* arg){
	int num = *((int*) arg);
	prime_sieve(num, primes);
	return NULL;
}
int prime_find(int num){
	int prime;
	int prime_findcount = 0;
	while(1){
		if(primecount == prime_findcount){
			continue;
		}
		if(num%primes.at(prime_findcount)==0){
			prime = primes.at(prime_findcount);
			return prime;
		}
		else{
			if(primes.at(prime_findcount) < num) prime_findcount++;
			else if(primes.at(prime_findcount) > num) prime_findcount--;
		}
	}
}
int addSpaces(int num, int orig_num){
	short orig_num_digits = 0; //A variable to hold the number of digits in orig_num
	short num_digits = 0; //A variable to hold the number of digits in num
	while(orig_num>=10){//Count digits in orig_num
		++orig_num_digits;
		orig_num/=10;
	}
	while(num>=10){ //Count digits in num
		++num_digits;
		num/=10;
	}
	return orig_num_digits-num_digits; //Return difference
}
void factor(int num){
	int orig_num = num;
	int prime;
	vector<int> factors;
	vector<int> results;
	vector<int> spaces;
	thread siever(&prime_sieve_wrapper, num);
	while(num>1){
		future<int> fut = async(prime_find, num);
		results.push_back(num);
		spaces.push_back(addSpaces(num, orig_num));
		prime = fut.get();
		num/=prime;
		factors.push_back(prime);
	}
	quit_siever = 1;
	if(stats){
		cout << primecount << " primes generated. Last prime: " << lastprime << endl;
		if(prime_finished) cout << " Prime generation reached set limit. " << endl << endl;
		else cout << " Prime generation finished prematurely." << endl << endl;
	}
	if(factor_print_mode == 0 || factor_print_mode==2){
		for(int i=0; i<results.size(); i++){
			for(int j=0; j<spaces.size(); j++){
				cout << " ";
			}
			cout << results.at(i) << "|" << factors.at(i) << endl;
		}
		for(int i=0; i<addSpaces(num, orig_num) ; i++){
			cout << " ";
		}
		cout << "1|\n";
	}
	if(factor_print_mode == 1 || factor_print_mode == 2){
		if(factor_print_mode) cout << endl;
		for(int i=0 ; i<factors.size(); i++){
			cout << factors.at(i) << " ";
		}
		cout << endl;
	}
	siever.join();
	exit(0);
}
