#include <iostream>
using namespace std;

#define SQUARE(x) (x*x)
#define CUBE(x) (SQUARE(x)*x)

int main(){
	int a = 2;
	int b = SQUARE(a);
	int c = CUBE(a);
	cout<<"b="<<b<<" and c="<<c<<endl;
	return 0;
}

