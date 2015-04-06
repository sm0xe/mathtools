#include <iostream>

int count_digits(long long int num);

using namespace std;
int gcd(int a, int b){
	if(a==0){
			return b;
		}
		else{
			return gcd(b%a, a);
		}
	}

void draw_vinculum(int num){
	for(int i=0; i<=num ; i++){
		cout << "-";
	}
}
void print_fraction(int whole, int nom, int denom){
	int whole_digits = count_digits(whole);
	int nom_digits = count_digits(nom);
	int denom_digits = count_digits(denom);
	int padding = (denom_digits-nom_digits)/2;

	if(whole==0){ //If there is no whole number
		for(int i=0; i<padding; i++){
			cout << " ";
		}
		cout << nom << endl;		//
		draw_vinculum(denom_digits);	//Print the fraction.
		cout << endl << denom << endl;		//
	}
	else if((nom == 0)||(denom == 0)){ //If the fraction is only a whole number.
		cout << whole << endl;
	}
	else{ //If the fraction contains both a whole number and a remainder.
		for(int i=0; i<=whole_digits+padding+1 ; i++){	//
			cout << " ";				//
		}						//
		cout << nom << endl;				//
		cout << whole << " ";				//
		draw_vinculum(denom_digits);			//Print them and align the remaining fraction
		cout << endl;					//
		for(int i=0; i<=whole_digits+1 ; i++){		//
			cout << " ";				//
		}						//
		cout << denom << endl;				//
	}
	exit(0);
}
void calc_simplify(int nom, int denom){
	int whole = nom / denom; //Get the whole number
	int rem = nom % denom; //Get the remainder
	int div = gcd(rem, denom); //Find greatest common divisor
	rem/=div; //Simplify fraction
	denom/=div;
	print_fraction(whole, rem, denom); //Pass the whole number, the remainder and the denominator to the printing function.
}
