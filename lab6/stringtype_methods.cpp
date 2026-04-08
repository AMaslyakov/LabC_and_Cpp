/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Файл использует stringtype.h и собирается вместе с stringtype_main.cpp.
Пример сборки и запуска: make with stringtype_main.cpp
*/

#include "stringtype.h"

int StringType::calc_length(const char* line) const{
	int i = 0;
	while (line[i] != '\0'){
		i++;
	}
	return i;
}

char* StringType::make_copy(const char* line) const{
	int len = calc_length(line);
	char* new_str = new char[len + 1];

	for (int i = 0; i < len; i++){
		new_str[i] = line[i];
	}
	new_str[len] = '\0';

	return new_str;
}

StringType::StringType(){
	str_size = 1;
	str = make_copy("");
}

StringType::StringType(int size){
	if (size < 1){
		size = 1;
	}

	str_size = size;
	str = new char[str_size];
	str[0] = '\0';
}

StringType::StringType(const char* line){
	str_size = calc_length(line) + 1;
	str = make_copy(line);
}

StringType::StringType(const StringType& other){
	str_size = other.str_size;
	str = make_copy(other.str);
}

StringType::~StringType(){
	delete[] str;
}

StringType& StringType::operator=(const StringType& other){
	if (this != &other){
		delete[] str;
		str_size = other.str_size;
		str = make_copy(other.str);
	}
	return *this;
}

StringType StringType::operator+(const StringType& other) const{
	int len1 = length();
	int len2 = other.length();
	char* new_line = new char[len1 + len2 + 1];

	for (int i = 0; i < len1; i++){
		new_line[i] = str[i];
	}

	for (int i = 0; i < len2; i++){
		new_line[len1 + i] = other.str[i];
	}
	new_line[len1 + len2] = '\0';

	StringType result(new_line);
	delete[] new_line;
	return result;
}

bool StringType::operator==(const StringType& other) const{
	int i = 0;
	while (str[i] != '\0' && other.str[i] != '\0'){
		if (str[i] != other.str[i]){
			return false;
		}
		i++;
	}
	return str[i] == other.str[i];
}

int StringType::length(void) const{
	return calc_length(str);
}

void StringType::input(void){
	char line[256];
	std::cin.getline(line, 256);

	delete[] str;
	str_size = calc_length(line) + 1;
	str = make_copy(line);
}

void StringType::output(void) const{
	std::cout<< str;
}

std::ostream& operator<<(std::ostream& os, const StringType& line){
	os << line.str;
	return os;
}

std::istream& operator>>(std::istream& is, StringType& line){
	char buffer[256];
	is.getline(buffer, 256);

	delete[] line.str;
	line.str_size = line.calc_length(buffer) + 1;
	line.str = line.make_copy(buffer);

	return is;
}
