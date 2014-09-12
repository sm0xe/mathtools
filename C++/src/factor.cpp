#include <vector>
#include <future>
#include <thread>
#include <iostream>
#include <unistd.h>
using namespace std;

void prime_sieve(int limit, vector<int>* prime_array); //Prime generation function from primes.cpp

extern long int primecount; //How many primes have been generated
extern short int stats; //Whether user wants the prime generation statistics or not
extern short int factor_print_mode; //What kind of output user wants. 0 for only division, 1 for only a list of factors, 2 for both.
short int prime_finished=0; //Whether the prime generation function finished prematurely or not.
int lastprime; //Last generated prime. Used in statistics
short int quit_siever; //Prime generation stops when this is set to 1
vector<int> primes; //A vector to contain all generated primes.
void prime_sieve_wrapper(int arg){
	int num = arg;
	prime_sieve(num, &primes); //Fill vector with primes
}
int prime_find(int num){
	int prime; //The prime we will eventually find
	int prime_findcount = 0; //
	while(1){
		if(primecount == prime_findcount){ //If we have reached the end of the vector, wait a bit and try again
			usleep(1);
			continue;
		}
		if(num%primes.at(prime_findcount)==0){ //Try to divide the number by a prime. If it works, return the prime
			prime = primes.at(prime_findcount);
			return prime;
		}
		else{ //If not, try next prime in vector
			if(primes.at(prime_findcount) < num) prime_findcount++; //Increment counter as long as the current prime is less than the number we are trying to divide
			else if(primes.at(prime_findcount) > num) prime_findcount--; //Decrement counter if current prime is larger than the number. This should never occur.
		}
	}
}
int count_digits(int num){ //Self-explanatory function
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
	for(int i=0; i<(orig_num_digits - num_digits) ; i++){ //Pad the output with spaces
		cout << " ";
	}
}
void factor(int num){
	int orig_num = num; //Store original number for future reference.
	int prime; //The prime we will eventually find
	vector<int> factors; //Vector containing all found factors
	vector<int> results; //Vector containing all result of dividing by the found factors
	thread siever(&prime_sieve_wrapper, num); //Start a thread with the task of filling the "primes" vector with primes
	while(num>1){
		auto fut = async(prime_find, num); //Start a thread with the task of searching the primes for a prime that the number can be divided by.
		results.push_back(num); //Add the current number to the list of results
		prime = fut.get(); //Get the prime from the thread
		num/=prime;
		factors.push_back(prime);//Add the prime to the list
	}
	quit_siever = 1; //Stop the prime generation, if not already stopped
	if(stats){ //Produce statistics for this run
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
