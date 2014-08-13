#include "config.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
//Below is borrowed and modified code from the book Advanced Linux Programming http://www.advancedlinuxprogramming.com/.
const char* prog_name;

short int stats=0, simplify=0, prime_print=0, factorize=0; //Program flags
short int factor_print_mode=0; //What kind of output is expected of the factorization feature: 0 for only division, 1 for only a list of factors, 2 for both

void print_usage(FILE* stream, int exit_code){
	fprintf(stream, "Usage: %s options [ args ... ]\n", prog_name); 
	fprintf(stream,	"       -h      --help                  Display this usage information.\n"
			"       -f      --fraction [fraction]   Convert improper fractions into proper fractions and/or simplify them.\n"
			"       -F      --factor   [num]        Factorizes the number.\n"
			"		--stats			Prints statistics for prime generation. (Amount and last generated)\n"
			"		--list			Only list the factors (default is division).\n"
			"		--div			Only show the division (default).\n"
			"		--both			Show the division and list factors underneath.\n"
       			"	-p      --primes   [limit]      Prints all primes less than or equal to [limit].\n"
			"\nExamples:\n"
			"       %s -f 4/12                      Simplifies the fraction 4/12\n"
			"       %s -F 123                       Factorizes the number 123\n"
			"       %s -p 123                       Prints all primes less than or equal to 123\n", prog_name, prog_name, prog_name);
	exit(exit_code);
}
//Above is borrowed and modified code from the book Advanced Linux Programming http://www.advancedlinuxprogramming.com/.

int main(int argc, char* argv[]){
	int next_option;
	int x, y;
	//Below is borrowed and modified code from the book Advanced Linux Programming http://www.advancedlinuxprogramming.com/
	const char* const short_options = "hf:F:p:"; //Option flags the program can take.

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

	prog_name = argv[0];

	do{
		next_option = getopt_long(argc, argv, short_options, long_options, NULL); //Get next option.

		switch(next_option){
			case 0: //Option sets a flag, do nothing
				break;
			case 'h': //Print TFM to be R'd
				print_usage(stdout, 0);
				break;
			case 'f': //Fraction
				sscanf(optarg, "%d%*c%d", &x, &y); //Get nom and denom and throw delim away.
				simplify = 1;
				prime_print = 0;
				factorize = 0;
				break;
			case 'F': //Factorization
				sscanf(optarg, "%d", &x); //Get the number to factor
				simplify = 0;
				prime_print = 0;
				factorize = 1;
				break;
			case 'p': //Prime generation
				sscanf(optarg, "%d", &x);//Get the limit
				simplify = 0;
				prime_print = 1;
				factorize = 0;
				break;
			case '?': //Oops, someone entered an invalid option.
				print_usage(stderr, 1);
				break;
			case -1: //Done, no more options to get.
				break;
			default:
				abort();
		}
	}while(next_option != -1);
	//Above is borrowed and modified code from the book Advanced Linux Programming http://www.advancedlinuxprogramming.com/
	if(simplify){			//
		calc_simplify(x, y);	//
	}				//
	else if(factorize){		//
		factor(x);		//Run correct function
	}				//
	else if(prime_print){		//
		prime_sieve(x);		//
		exit(0);		//
	}				//
	print_usage(stderr, 0);//If we actually come this far, it means that something went wrong.
}

