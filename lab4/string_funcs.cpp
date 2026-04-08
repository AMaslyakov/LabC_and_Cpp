/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Пример сборки: make build string_funcs.cpp
Пример запуска: make run string_funcs.cpp
*/

#include <iostream>
#include "string.h"

int main(void){
	char line1[32]="abcdef", line2[]="1234567890";

	int length_1, length_2;
	
	length_1 = strlen(line1);
	length_2 = strlen(line2);
	
	std::cout<< "Длина первой строки:"<< line1 <<" " << length_1;
	std::cout<<std::endl;

	std::cout<< "Длина второй строки:"<< line2 <<" " << length_2;
	std::cout<<std::endl;

	char line3[] = "g";
	
	//Конкатенация строк
	char* new_line = strcat(line1, line3);
	
	std::cout<< "Cтрока 1:" << line1;
	std::cout<<std::endl;
	std::cout<< "Строка 2:" << line3;
	std::cout<<std::endl;
	std::cout<< "Объеденненые строки:" << new_line;
	std::cout<<std::endl;


	char copied_line[32];
	strcpy(copied_line, line2);

	std::cout<< "Исходная строка:" << line2;
	std::cout<<std::endl;
	std::cout<< "Скопированная строка:" << copied_line;
	std::cout<<std::endl;

	int cmp_line1_line2 = strcmp(line1, line2);
	int cmp_line2_copied = strcmp(line2, copied_line);

	std::cout<< "Сравнение line1 и line2 (strcmp): " << cmp_line1_line2;
	std::cout<<std::endl;
	std::cout<< "Сравнение line2 и copied_line (strcmp): " << cmp_line2_copied;
	std::cout<<std::endl;
	
	return 0;
}
