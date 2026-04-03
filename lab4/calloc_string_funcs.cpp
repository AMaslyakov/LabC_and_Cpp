#include <iostream>
#include <cstdlib>

int string_length(char* str){
	int i = 0;
	// перебераем все символы пока не достигнем конца строки \0
	while (str[i] != '\0'){
		i++;
	}
	return i;
}

char* string_copy(char* src){
	int len = string_length(src);
	// выделяем память под копию строки
	char* dest = (char*)calloc(len + 1, sizeof(char));
	if (dest == NULL){
		return NULL;
	}

	int i = 0;
	while (src[i] != '\0'){
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

char* string_cat(char* str1, char* str2){
	int len1 = string_length(str1);
	int len2 = string_length(str2);

	// выделяем память под объединенную строку
	char* new_str = (char*)calloc(len1 + len2 + 1, sizeof(char));
	if (new_str == NULL){
		return NULL;
	}

	int i = 0;
	while (str1[i] != '\0'){
		new_str[i] = str1[i];
		i++;
	}

	int j = 0;
	while (str2[j] != '\0'){
		new_str[i + j] = str2[j];
		j++;
	}
	new_str[i + j] = '\0';

	free(str1);
	return new_str;
}

int string_compare(char* str1, char* str2){
	int i = 0;
	// если все символы равны вернется 0
	while (str1[i] != '\0' && str2[i] != '\0'){
		if (str1[i] != str2[i]){
			return str1[i] - str2[i];
		}
		i++;
	}
	return str1[i] - str2[i];
}

#ifndef STRING_FUNCS_ONLY
int main(void){
	char line1_init[] = "abcdef";
	char line2_init[] = "1234567890";
	char line3_init[] = "g";

	char* line1 = string_copy(line1_init);
	char* line2 = string_copy(line2_init);
	char* line3 = string_copy(line3_init);

	if (line1 == NULL || line2 == NULL || line3 == NULL){
		free(line1);
		free(line2);
		free(line3);
		return 1;
	}

	int length_1, length_2;

	length_1 = string_length(line1);
	length_2 = string_length(line2);

	std::cout<< "Длина первой строки:"<< line1 <<" " << length_1;
	std::cout<<std::endl;

	std::cout<< "Длина второй строки:"<< line2 <<" " << length_2;
	std::cout<<std::endl;

	//Конкатенация строк
	char* new_line = string_cat(line1, line3);
	if (new_line == NULL){
		free(line1);
		free(line2);
		free(line3);
		return 1;
	}
	line1 = new_line;

	std::cout<< "Cтрока 1:" << line1;
	std::cout<<std::endl;
	std::cout<< "Строка 2:" << line3;
	std::cout<<std::endl;
	std::cout<< "Объеденненые строки:" << new_line;
	std::cout<<std::endl;

	char* copied_line = string_copy(line2);
	if (copied_line == NULL){
		free(line1);
		free(line2);
		free(line3);
		return 1;
	}

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

	free(line1);
	free(line2);
	free(line3);
	free(copied_line);

	return 0;
}
#endif
