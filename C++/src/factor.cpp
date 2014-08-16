using namespace std;
int addSpaces(int num, int orig_num){
	short orig_num_digits = 0; //A variable to hold the number of digits in orig_num
	short num_digits = 0; //A variable to hold the number of digits in num
	while(orig_num>=10){//Count digits in orig_num
		++orig_num_digits;
		orig_num/=10;
	}
	while(num>=10){ //Count digits in num
		++num_digits;
		num/=10;
	}
	return orig_num_digits-num_digits; //Return difference
}
