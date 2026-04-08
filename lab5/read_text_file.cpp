/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Пример сборки: make build read_text_file.cpp
Пример запуска: make run read_text_file.cpp
*/

#include "stdio.h"

int main(void){
	char ch, name[50];
	FILE *in;

	printf("Введите имя файла для просмотра: ");
	scanf("%s", name);

	if((in=fopen(name, "r"))==NULL)
		printf("Файл %s не открыт", name);
	else
		while(!feof(in)){
			ch=getc(in);
			putchar(ch);
		}
	return 0;
}

