#include <vector>
#include <future>
#include <thread>
#include <iostream>
#include <unistd.h>
using namespace std;

void prime_sieve(int limit, vector<int>* prime_array);

extern long int primecount;
extern short int stats;
extern short int factor_print_mode;
short int prime_finished=0;
int lastprime;
short int quit_siever;
vector<int> primes;
void prime_sieve_wrapper(int arg){
	int num = arg;
	prime_sieve(num, &primes);
}
int prime_find(int num){
	int prime;
	int prime_findcount = 0;
	while(1){
		if(primecount == prime_findcount){
			usleep(2);
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
int count_digits(int num){
	short digits = 0;
	while(num>=10){
		++digits;
		num/=10;
	}
	return digits;
}
void addSpaces(int num, int orig_num){
	short orig_num_digits = count_digits(orig_num); //A variable to hold the number of digits in orig_num
	short num_digits = count_digits(num); //A variable to hold the number of digits in num
	for(int i=0; i<(orig_num_digits - num_digits) ; i++){
		cout << " ";
	}
}
void factor(int num){
	int orig_num = num;
	int prime;
	vector<int> factors;
	vector<int> results;
	vector<int> spaces;
	thread siever(&prime_sieve_wrapper, num);
	while(num>1){
		auto fut = async(prime_find, num);
		results.push_back(num);
		prime = fut.get();
		num/=prime;
		factors.push_back(prime);
	}
	quit_siever = 1;
	if(stats){
		cout << primecount << " primes generated. Last prime: " << lastprime;
		if(prime_finished) cout << ". Prime generation reached set limit. " << endl << endl;
		else cout << ". Prime generation finished prematurely." << endl << endl;
	}
	if(factor_print_mode == 0 || factor_print_mode==2){
		for(int i=0; i<results.size(); i++){
			addSpaces(results.at(i), orig_num);
			cout << results.at(i) << "|" << factors.at(i) << endl;
		}
		addSpaces(1, orig_num);
		cout << "1|\n";
	}
	if(factor_print_mode == 1 || factor_print_mode == 2){
		if(factor_print_mode==2) cout << endl;
		for(int i=0 ; i<factors.size(); i++){
			cout << factors.at(i) << " ";
		}
		cout << endl;
	}
	siever.join();
	exit(0);
}
