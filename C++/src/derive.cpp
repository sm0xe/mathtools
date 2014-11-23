#include <iostream>
#include <string>
#include <locale>
#include <sstream>
#include <vector>
using namespace std;
typedef struct{
	int factor;
	char var;
	int exp;
}elements;
elements extract(string element){
	elements parts;
	int pos=0;
	pos = element.find_first_of("xyzt");
	stringstream(element.substr(0,pos)) >> parts.factor;
	if(pos!=string::npos){
		parts.var = element[pos];
	}
	else{
		parts.exp=0;
		parts.var='-';
		return parts;
	}
	if((pos+1)!=element.length()){
		stringstream(element.substr(pos+2)) >> parts.exp;
	}
	else{
		parts.exp=1;
	}
	return parts;
}
vector<string> parse_poly(string poly){
	vector<string> elements;
	size_t pos = poly.find_first_of("+-",1);
	do{
		string element = poly.substr(0,pos);
		elements.push_back(element);
		poly = poly.substr(pos);
		pos = poly.find_first_of("+-",1);
	}while(pos!=string::npos);
	string element = poly.substr(0,pos);
	elements.push_back(element);
	return elements;
}
int derive(string element){
	vector<string> polynomial = parse_poly(element);
	for(int i=0; i<polynomial.size(); i++){
		elements poly = extract(polynomial.at(i));
		cout << poly.factor << endl;
		cout << poly.var << endl;
		cout << poly.exp << endl;
		cout << "---" << endl;
	}
	return 0;
}
int main(){
	string element;
	cin >> element;
	derive(element);
	return 0;
}
