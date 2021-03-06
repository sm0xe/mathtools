#include "config.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <getopt.h>
#include <math.h>
using namespace std;

void single_factor(long long int);		//Factorization function from factor.cpp
void multi_factor(long long int);		//Factorization function from factor.cpp
void calc_simplify(int num, int denom);		//Fraction simplifier function from fract.cpp
void prime_sieve(long long int limit);		//Prime printing function from primes.cpp
bool primecheck_k(long long int prime, int k);	//Miller-Rabin primality test from primes.cpp
void derive(string polynomial);			//Polynomial derivation from derive.cpp

const char* prog_name;

enum functions {help, simplify, prime_print, factorize, derivation,primality} task; //What feature the user wants to use
int stats=0, factor_print_mode=0, factor_mode=1; //Flags for factorization function

void print_usage(int exit_code){
	cout << "Usage: " << prog_name << " options [ args ... ]\n";
	cout << "	-h      --help                  Display this usage information.\n";
	cout << "	-f      --fraction [fraction]   Convert improper fractions into proper fractions and/or simplify them.\n";
	cout << "	-F	--factor   [num]        Factorizes the number.\n";
	cout << "		--simple		Factorize using a single process. Slower, but less resource-intensive.\n";
	cout << "		--multi			Use multi-threaded factorization. Faster, but more resource-intensive. (default)\n";
	cout << "		--stats                 Prints statistics for prime generation. (Amount and last generated)\n";
	cout << "		--list                  Only list the factors (default is division).\n";
	cout << "		--div                   Only show the division (default).\n";
	cout << "		--both                  Show the division and list factors underneath.\n";
	cout << "	-p      --primes   [limit]      Prints all primes less than or equal to [limit].\n";
	cout << "	-d	--derive   [polynomial]	Derives the polynomial function.\n";
	cout << "	-c	--primality[num]	Tests the number for primality (Miller-Rabin).\n";
	cout << "	-k	--iter     [limit]	How many times the Miller-Rabin primality test should run.\n";
	cout <<	"\nExamples:\n";
	cout <<	"	" << prog_name << " -f 4/12			Simplifies the fraction 4/12\n";
	cout <<	"	" << prog_name << " -F 123			Factorizes the number 123\n";
	cout <<	"	" << prog_name << " -p 123			Prints all primes less than or equal to 123\n";
	cout << "	" << prog_name << " -d 2x^2-x+12		Prints the derivative of 2x^2-x+12\n";
	cout << "	" << prog_name << " -c 561			Returns whether 561 is a prime or composite. Run 7 times.\n";
	cout << "	" << prog_name << " -c 1105 -k 2		Returns whether 1105 is a prime or composite. Run 2 times.\n";
	exit(exit_code);
}

int main(int argc, char* argv[]){
	long long int x, y;
	string z;

	prog_name = argv[0];

	int next_opt;

	const char* short_opt = "hf:F:p:d:c:k:"; //Option flags the program can take.

	const struct option long_opt[] = {
		{ "div", 0, &factor_print_mode, 0},
		{ "list", 0, &factor_print_mode, 1},
		{ "both", 0, &factor_print_mode, 2},
		{ "simple", 0, &factor_mode, 0},
		{ "multi", 0, &factor_mode, 1},
		{ "stats", 0, &stats, 1 },
		{ "help", 0, NULL, 'h' },
		{ "fraction", 1, NULL, 'f' }, //Long options, synonyms and if they take an argument.
		{ "factor", 1, NULL, 'F' },
		{ "primes", 1, NULL, 'p' },
		{ "derive", 1, NULL, 'd' },
		{ "primality", 1, NULL, 'c' },
		{ "iter", 1, NULL, 'k' },
		{ NULL, 0, NULL, 0 }
	};
	while ((next_opt=getopt_long(argc,argv,short_opt,long_opt, NULL))!=-1){
		string opt;
		switch(next_opt){
			case 0: //Option sets a flag, do nothing
				break;
			case 'h':
				print_usage(0); //Print TFM to be R'd
				break;
			case 'f': //Fraction
				char delim;
				opt = optarg;
				stringstream(opt) >> x >> delim >> y; //Get nominator and denominator and throw delim ("/") away.
				task = simplify;
				break;
			case 'F': //Factorization
				opt = optarg;
				stringstream(opt) >> x; //Get the number to factorize
				task = factorize;
				break;
			case 'p': //Prime generation
				opt = optarg;
				stringstream(opt) >> x; //Get the limit
				task = prime_print;
				break;
			case 'd': //Derivative
				z = optarg;
				task = derivation;
				break;
			case 'c': //Primality test
				opt = optarg;
				stringstream(opt) >> x;
				y=7;
				task = primality;
				break;
			case 'k': //Extra argument for primality test
				opt = optarg;
				stringstream(opt) >> y;
				task = primality;
				break;
			case '?': //Oops, someone entered an invalid option
				print_usage(1);
				break;
			case -1: //Done, no more options to get.
				break;
			default:
				abort();
		}
	}
	if(task == simplify){						//
		calc_simplify(x, y);					//
	}								//
	else if(task == factorize){					//
		switch(factor_mode){					//
			case 0:						//
				single_factor(x);			//
			case 1:						//
				multi_factor(x);			//Run correct function
		}							//
	}								//
	else if(task == prime_print){					//
		prime_sieve(x);						//
		exit(0);						//
	}								//
	else if(task == derivation){					//
		derive(z);						//
		exit(0);						//
	}
	else if(task == primality){
	    	if(primecheck_k(x,y)){
			cout << "Probable prime with probability " << 1-pow(0.25,y) << endl;
		}
		else{
		    cout << "Composite" << endl;
		}
		exit(0);
	}
	print_usage(0);//If we actually come this far, it means that something went wrong.
}
