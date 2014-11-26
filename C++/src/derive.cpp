#include <iostream>
#include <string>
#include <locale>
#include <sstream>
#include <vector>
using namespace std;
bool first = true;
typedef struct{	//Structure containing the elements of a term in the polynomial. Ex. 3x^2
	int coef;//Ex. 3
	char var;//Ex. x
	int exp;//Ex. 2
}term_s;
//Deconstructs a term of type string into the structure above.
term_s deconstruct_term(string element){
	term_s term;
	int pos=0;
	pos = element.find_first_of("xyzt"); //Finds the variable
	if(element[pos-1]=='-'){ //No coefficient, only '-'?
		term.coef=-1;
	}
	else if(element[pos-1]=='+'){ //No coefficient, only '+'?
		term.coef=1;
	}
	else{
		stringstream(element.substr(0,pos)) >> term.coef; //Get coef.
	}
	if(pos!=string::npos){//If variable is found
		term.var = element[pos]; //Get variable (x/y/z/t)
	}
	else{ //If variable is not found, ex: -7
		term.exp=0;
		term.var='-';
		return term;
	}
	if((pos+1)!=element.length()){ //If there is an exponent
		stringstream(element.substr(pos+2)) >> term.exp; //Get it
	}
	else{//If not, it has probably been omitted. Ex: x instead of x^1
		term.exp=1;
	}
	return term;
}
//Constructs the term from structure into a string again
string construct_term(term_s term){
	stringstream construct;
	if(term.coef>0&&term.coef!=0&&!first)
		construct << '+'; //Add a '+'-sign before the term
	if((term.coef!=1&&term.coef!=0)||(term.coef==1&&term.exp==0))
		construct << term.coef; //Add the coefficient to the term
	if(term.var!='-' && term.coef!=0 && term.exp!=0)
		construct << term.var; //Add the variable to the term
	if(term.exp!=-1 && term.exp!=0 && term.exp!=1)
		construct << '^' << term.exp; //Add the exponent to the term
	return construct.str();
}
//Split the polynomial into a vector containing the individiual terms in order
vector<string> parse_poly(string poly){
	vector<string> elements;
	size_t pos = poly.find_first_of("+-",1);
	while(pos!=string::npos){
		string element = poly.substr(0,pos);
		elements.push_back(element);
		poly = poly.substr(pos);
		pos = poly.find_first_of("+-",1);
	};
	string element = poly;
	elements.push_back(element);
	return elements;
}
void derive(string polynomial){
	vector<string> poly = parse_poly(polynomial); //Parse
	string derived;
	for(int i=0;i<(poly.size());i++){
		term_s term = deconstruct_term(poly.at(i));
		term.coef*=term.exp;	//Simple
		term.exp-=1;		//derivation
		derived+=construct_term(term);
		first=false;
	}
	cout << derived << endl;
}
