#include <iostream>

int main(void){
	int a = 2, b = 5;
	void swap1(int, int);
	void swap2(int*, int*);
	void swap3(int&, int&);
	std::cout<<"До обмена: a = "<< a <<"; b = "<<b<<std::endl;
	swap1(a, b);
	std::cout<<"После обмена 1: a = "<< a <<"; b = "<<b<<std::endl;
	swap2(&a, &b);
	std::cout<<"После обмена 2: a = "<< a <<"; b = "<<b<<std::endl;
	swap3(a, b);
	std::cout<<"После обмена 3: a = "<< a <<"; b = "<<b<<std::endl;
}


void swap1(int a, int b){
	int c;
	c = a;
	a = b;
	b = c;
}

void swap2(int* p_a, int* p_b){
	int p_c;
	p_c = *p_a;
	*p_a = *p_b;
	*p_b = p_c;
}

void swap3(int& na, int& nb){
	int nc = na;
	na = nb;
	nb = nc;
}
