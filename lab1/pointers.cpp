/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Пример сборки: make build FILE=pointers.cpp
Пример запуска: make run FILE=pointers.cpp
*/

#define PR(x) printf("x=%p, *x=%d, &x=%p\n", x, *x, &x)
#include <stdio.h>
int main(void){
	int mas[]={100, 200, 300};
	int *ptr1, *ptr2;
	ptr1 = mas;
	ptr2 = &mas[2];
	PR(ptr1);
	ptr1++;
	PR(ptr1);
	PR(ptr2);
	++ptr2;
	printf("ptr2-ptr1=%td\n", ptr2-ptr1);
}
