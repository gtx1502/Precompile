#include <iostream>
#include "test.h"
using namespace std;

#define SUM (a+b)

int main(){
#ifdef TEST_H
	a = 7;
	b = 8;
	int c = SUM;
	int d = product(a, b);
	
#endif

#define DEBUG

#ifdef DEBUG
	cout<<"DEBUG 1"<<endl;
#undef DEBUG
#endif

#ifdef DEBUG
	cout<<"DEBUG 2"<<endl;
#endif

#define NUM 42

#ifndef NUM
	cout<<"NUM NOT DEFINED!"<<endl;
#elif NUM>=50
	cout<<"NUM>=50"<<endl;
#elif NUM<50 && NUM>10
	cout<<"10<NUM<50"<<endl;
#elif NUM==10
	cout<<"NUM=10"<<endl;
#else
	cout<<"NUM<10"<<endl;
#endif


	cout<<"c="<<c<<" and d="<<d<<endl;
	return 0;
}

