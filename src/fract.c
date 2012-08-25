#include <stdio.h>
#include <stdlib.h>
void print_fraction(int whole, int nom, int denom){
	if(whole == 0){ //if there is no whole number
		printf("%d\n", nom);  //
		printf("-\n");          //print the fraction
		printf("%d\n", denom);//<
	}
	else if((nom == 0)||(denom == 0)){//if the fraction is only a whole number
		printf("\n");       //
		printf("%d", whole);//print it
		printf("\n\n");     //
	}
	else{//if the fraction contains both a whole number and a remainder
		char spaces[6] = "     "; //initializes a character string with spaces
		if(whole>9999){
			spaces[6] = '\0';
		}
		else if(whole>999){
			spaces[5] = '\0';
		}
		else if(whole>99){
			spaces[4] = '\0';
		}
		else if(whole>9){
			spaces[3] = '\0';
		}
		else{
			spaces[2] = '\0';
		}
		printf("%s%d\n", spaces, nom);  //
		printf("%d -\n", whole);        //print them and align the remaining fraction
		printf("%s%d\n", spaces, denom);//
	}
	exit(0);
}
void calc_simplify(int nom, int denom){
	int whole = nom / denom; //get the whole number
	int rem = nom % denom; //get the remainder
	
	for(int i=rem;i>1;i--){//simplify the fraction by checking for a common factor
			if((rem%i==0)&&(denom%i==0)){//if a common factor has been found
				rem/=i;   //
				denom/=i; //divide the remainder and denominator by the common factor
				break;
			}
		}
	print_fraction(whole, rem, denom);//pass the whole number, the remainder and the denominator to the printing function
}
