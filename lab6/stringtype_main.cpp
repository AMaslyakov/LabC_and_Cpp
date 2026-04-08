/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Файл использует stringtype.h и собирается вместе с stringtype_methods.cpp.
Пример сборки и запуска: make with stringtype_main.cpp
*/

#include "stringtype.h"

int main(void){
	StringType line1("abcdef");
	StringType line2("1234567890");
	StringType line3;
	StringType copied_line;
	StringType line_with_size(32);

	// присваиваем значение через оператор =
	copied_line = line1;

	std::cout<< "Строка 1:" << line1;
	std::cout<<std::endl;
	std::cout<< "Строка 2:" << line2;
	std::cout<<std::endl;
	std::cout<< "Скопированная строка:" << copied_line;
	std::cout<<std::endl;
	std::cout<< "Строка с выделенной памятью:" << line_with_size;
	std::cout<<std::endl;

	std::cout<< "Длина строки 1: " << line1.length();
	std::cout<<std::endl;
	std::cout<< "Длина строки 2: " << line2.length();
	std::cout<<std::endl;

	// сцепляем две строки
	line3 = line1 + line2;
	std::cout<< "Объеденненые строки:" << line3;
	std::cout<<std::endl;

	// сравниваем одинаковые и разные строки
	std::cout<< "line1 == copied_line: " << (line1 == copied_line);
	std::cout<<std::endl;
	std::cout<< "line1 == line2: " << (line1 == line2);
	std::cout<<std::endl;

	StringType input_line(64);
	std::cout<< "Введите строку: ";
	input_line.input();

	std::cout<< "Введенная строка методом output: ";
	input_line.output();
	std::cout<<std::endl;

	std::cout<< "Введите еще одну строку: ";
	StringType input_line2(64);
	std::cin >> input_line2;

	std::cout<< "Введенная строка оператором >> : " << input_line2;
	std::cout<<std::endl;

	return 0;
}
