#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

//below is borrowed and modified code from the book Advanced Linux Programming http://www.advancedlinuxprogramming.com/
const char* prog_name;

void print_usage(FILE* stream, int exit_code){
	fprintf(stream, "Usage: %s options [ args ... ]\n", prog_name); 
	fprintf(stream,
			"	-h	--help		Display this usage information.\n" //print usage message
			"	-f	--fraction	Convert improper fractions into proper fractions and/or simplify them.\n");
	exit(exit_code);
}
//above is borrowed and modified code from the book Advanced Linux Programming http://www.advancedlinuxprogramming.com/

int main(int argc, char* argv[]){
	int next_option, nom, denom, delim;
	//* below is borrowed and modified code from the book Advanced Linux Programming http://www.advancedlinuxprogramming.com/
	const char* const short_options = "hf:"; //option flags the program can take

	const struct option long_options[] = {
		{ "help", 0, NULL, 'h' },
		{ "fraction", 1, NULL, 'f' }, //long options, synonyms and if they take an argument
		{ NULL, 0, NULL, 0 }
	};

	prog_name = argv[0];

	do{
		next_option = getopt_long(argc, argv, short_options, long_options, NULL); //get next option

		switch(next_option){
			case 'h':
				print_usage(stdout, 0);
			case 'f':
				sscanf(optarg, "%d%c%d", &nom, &delim, &denom); //get nom and denom and throw delim away
				calc_simplify(nom, denom);
				break;
			case '?': //oops, someone entered an invalid option
				print_usage(stderr, 1);
			case -1: //done, no more options to get
				break;
			default:
				abort();
		}
	}while(next_option != -1);
	//* above is borrowed and modified code from the book Advanced Linux Programming http://www.advancedlinuxprogramming.com/
	print_usage(stdout, 0);
}

