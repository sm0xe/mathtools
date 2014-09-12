#include "config.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <getopt.h>
using namespace std;

void factor(long long int);	//Factorization function from factor.cpp
void calc_simplify(int num, int denom);	//Fraction simplifier function from fract.cpp
void prime_sieve(long long int limit);	//Prime printing function from primes.cpp

const char* prog_name;

enum functions {simplify, prime_print, factorize} task; //What feature the user wants to use
int stats=0, factor_print_mode=0; //Flags for factorization function

void print_usage(int exit_code){
	cout << "Usage: " << prog_name << " options [ args ... ]\n";
	cout << "	-h      --help                  Display this usage information.\n";
	cout << "	-f      --fraction [fraction]   Convert improper fractions into proper fractions and/or simplify them.\n";
	cout << "	-F	--factor   [num]        Factorizes the number.\n";
	cout << "		--stats                 Prints statistics for prime generation. (Amount and last generated)\n";
	cout << "		--list                  Only list the factors (default is division).\n";
	cout << "		--div                   Only show the division (default).\n";
	cout << "		--both                  Show the division and list factors underneath.\n";
	cout << "	-p      --primes   [limit]      Prints all primes less than or equal to [limit].\n";
	cout <<	"\nExamples:\n";
	cout <<	"	" << prog_name <<" -f 4/12                      Simplifies the fraction 4/12\n";
	cout <<	"       " << prog_name << " -F 123                       Factorizes the number 123\n";
	cout <<	"	" << prog_name << " -p 123                       Prints all primes less than or equal to 123\n";
	exit(exit_code);
}

int main(int argc, char* argv[]){
	long long int x, y;

	prog_name = argv[0];

	int next_option;

	const char* short_options = "hf:F:p:"; //Option flags the program can take.

	const struct option long_options[] = {
		{ "div", 0, &factor_print_mode, 0},
		{ "list", 0, &factor_print_mode, 1},
		{ "both", 0, &factor_print_mode, 2},
		{ "stats", 0, &stats, 1 },
		{ "help", 0, NULL, 'h' },
		{ "fraction", 1, NULL, 'f' }, //Long options, synonyms and if they take an argument.
		{ "factor", 1, NULL, 'F' },
		{ "primes", 1, NULL, 'p' },
		{ NULL, 0, NULL, 0 }
	};
	while ((next_option = getopt_long(argc, argv, short_options, long_options, NULL)) != -1){
		string opt;
		switch(next_option){
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
			case '?': //Oops, someone entered an invalid option
				print_usage(1);
				break;
			case -1: //Done, no more options to get.
				break;
			default:
				abort();
		}
	}
	
	if(task == simplify){			//
		calc_simplify(x, y);		//
	}					//
	else if(task == factorize){		//
		factor(x);			//Run correct function
	}					//
	else if(task == prime_print){		//
		prime_sieve(x);			//
		exit(0);			//
	}					//
	print_usage(0);//If we actually come this far, it means that something went wrong.
}
