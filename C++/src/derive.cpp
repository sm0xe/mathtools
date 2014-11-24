#include <iostream>
#include <string>
#include <locale>
#include <sstream>
#include <vector>
using namespace std;
typedef struct{
	int coef;
	char var;
	int exp;
}term_s;
term_s deconstruct_term(string element){
	term_s term;
	int pos=0;
	pos = element.find_first_of("xyzt");
	if(element[pos-1]!='-' && element[pos-1]!='+'){
		stringstream(element.substr(0,pos)) >> term.coef;
	}
	else{
		term.coef=1;
	}
	if(pos!=string::npos){
		term.var = element[pos];
	}
	else{
		term.exp=0;
		term.var='-';
		return term;
	}
	if((pos+1)!=element.length()){
		stringstream(element.substr(pos+2)) >> term.exp;
	}
	else{
		term.exp=1;
	}
	return term;
}
string construct_term(term_s term){
	stringstream construct;
	if(term.coef>0 && term.coef!=0 )
		construct << '+';
	if((term.coef!=1 && term.coef!=0) || (term.coef==1 && term.exp==0))
		construct << term.coef;
	if(term.var!='-' && term.coef!=0 && term.exp!=0)
		construct << term.var;
	if(term.exp!=-1 && term.exp!=0 && term.exp!=1)
		construct << '^' << term.exp;
	return construct.str();
}
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
void derive(string element){
	vector<string> poly = parse_poly(element);
	string derived;
	for(int i=0;i<(poly.size());i++){
		term_s term = deconstruct_term(poly.at(i));
		term.coef*=term.exp;
		term.exp-=1;
		derived+=construct_term(term);
	}
	cout << derived << endl;
}
int main(){
	string element;
	cin >> element;
	derive(element);
	return 0;
}
