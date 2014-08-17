#include <iostream>

int addSpaces(int num, int orig_num);

using namespace std;
void print_fraction(int whole, int nom, int denom){
	if(whole==0){ //If there is no whole number.
		cout << nom << endl;	//
		cout << "-" << endl;	//Print the fraction.
		cout << denom << endl;	//
	}
	else if((nom == 0)||(denom == 0)){ //If the fraction is only a whole number.
		cout << whole << endl;
	}
	else{ //If the fraction contains both a whole number and a remainder.
		for(int i=0 ; i<addSpaces(nom, whole) ; i++){	//
			cout << " ";				//
		}						//
		cout << " " << nom << endl;			//Print them and align the remaining fraction
		cout << whole << " -" << endl;			//
		for(int i=0; i<addSpaces(nom, whole) ; i++){	//
			cout << " ";				//
		}						//
		cout << " " << denom << endl;			//
	}
	exit(0);
}
void calc_simplify(int nom, int denom){
	int whole = nom / denom; //Get the whole number
	int rem = nom % denom; //Get the remainder

	for(int i=rem; i>1; i--){//Simplify the fraction by checking for a common factor
		if((rem%i==0)&&(denom%i==0)){ //If a common factor has been found
			rem/=i;
			denom/=i; //Divide the remainder and denominator by the common factor.
			break;
		}
	}
	print_fraction(whole, rem, denom); //Pass the whole number, the remainder and the denominator to the printing function.
}
