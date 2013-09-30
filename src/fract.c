#include <stdio.h>
#include <stdlib.h>
void print_fraction(int whole, int nom, int denom){
	if(whole == 0){ //If there is no whole number.
		printf("%d\n", nom);  //
		printf("-\n");        //Print the fraction.
		printf("%d\n", denom);//
	}
	else if((nom == 0)||(denom == 0)){//If the fraction is only a whole number.
		printf("%d\n", whole);//Print it.
	}
	else{//If the fraction contains both a whole number and a remainder.
		addSpaces(nom, whole);          //
		printf("  %d\n", nom);          //
		printf("%d -\n", whole);        //Print them and align the remaining fraction.
		addSpaces(denom, whole);        //
		printf("  %d\n", denom);        //
	}
	exit(0);
}
void calc_simplify(int nom, int denom){
	int whole = nom / denom; //Get the whole number.
	int rem = nom % denom; //Get the remainder.
	
	for(int i=rem;i>1;i--){//Simplify the fraction by checking for a common factor.
			if((rem%i==0)&&(denom%i==0)){//If a common factor has been found.
				rem/=i;   //
				denom/=i; //Divide the remainder and denominator by the common factor.
				break;
			}
		}
	print_fraction(whole, rem, denom);//Pass the whole number, the remainder and the denominator to the printing function.
}
