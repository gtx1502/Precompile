#include <iostream>
int a;
int b;
int product(int arg1, int arg2){
	return arg1 * arg2;
}
using namespace std;
int main(){
	a = 7;
	b = 8;
	int c = (a+b);
	int d = product(a, b);
	
	cout<<"DEBUG 1"<<endl;
	cout<<"10<NUM<50"<<endl;
	cout<<"c="<<c<<" and d="<<d<<endl;
	return 0;
}

