/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Пример сборки: make build custom_string_funcs.cpp
Пример запуска: make run custom_string_funcs.cpp
*/

#include <iostream>

int string_length(char* str){
	int i = 0;
	// перебераем все символы пока не достигнем конца строки \0
	// считаем количество символов
	while (str[i] != '\0'){
		i++;
	}
	return i;
}

char* string_cat(char* str1, char* str2){
	//Определяем количество символов в первой строке
	int i = 0;
	while (str1[i] != '\0'){
		i++;
	}
	
	// добавляем в первую строку смиволы из второй
	int j = 0;
	while (str2[j] != '\0'){
		str1[i + j] = str2[j];
		j++;
	}
	// конец строки 
	str1[i + j] = '\0';
	return str1;
}

void string_copy(char* dest, char* src){
	int i = 0;
	// перебираем все символы их src и записываеи их в dest
	while (src[i] != '\0'){
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int string_compare(char* str1, char* str2){
	int i = 0;
	// если все символы равны вернется 0 
	// иначе вернется разница между номерами символов
	while (str1[i] != '\0' && str2[i] != '\0'){
		if (str1[i] != str2[i]){
			return str1[i] - str2[i];
		}
		i++;
	}
	return str1[i] - str2[i];
}

int main(void){
	char line1[32]="abcdef", line2[]="1234567890";

	int length_1, length_2;
	
	length_1 = string_length(line1);
	length_2 = string_length(line2);
	
	std::cout<< "Длина первой строки:"<< line1 <<" " << length_1;
	std::cout<<std::endl;

	std::cout<< "Длина второй строки:"<< line2 <<" " << length_2;
	std::cout<<std::endl;

	char line3[] = "g";
	
	//Конкатенация строк
	char* new_line = string_cat(line1, line3);
	
	std::cout<< "Cтрока 1:" << line1;
	std::cout<<std::endl;
	std::cout<< "Строка 2:" << line3;
	std::cout<<std::endl;
	std::cout<< "Объеденненые строки:" << new_line;
	std::cout<<std::endl;
	// копиование строк
	char copied_line[32];
	string_copy(copied_line, line2);

	std::cout<< "Исходная строка:" << line2;
	std::cout<<std::endl;
	std::cout<< "Скопированная строка:" << copied_line;
	std::cout<<std::endl;

	int cmp_line1_line2 = string_compare(line1, line2);
	int cmp_line2_copied = string_compare(line2, copied_line);

	std::cout<< "Сравнение line1 и line2 (strcmp): " << cmp_line1_line2;
	std::cout<<std::endl;
	std::cout<< "Сравнение line2 и copied_line (strcmp): " << cmp_line2_copied;
	std::cout<<std::endl;

	return 0;
}
