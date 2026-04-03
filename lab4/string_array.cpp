#include <iostream>
#define STRING_FUNCS_ONLY
#include "calloc_string_funcs.cpp"

int main(void){
	char w0[] = "alpha";
	char w1[] = "beta";
	char w2[] = "gamma";
	char w3[] = "delta";

	char* words_init[] = {w0, w1, w2, w3};
	const int arr_size = 4;
	char* words[arr_size];

	for (int i = 0; i < arr_size; i++){
		words[i] = string_copy(words_init[i]);
		if (words[i] == NULL){
			for (int j = 0; j < i; j++){
				free(words[j]);
			}
			return 1;
		}
	}

	std::cout<< "Массив строк:";
	std::cout<<std::endl;
	for (int i = 0; i < arr_size; i++){
		std::cout<< "words[" << i << "] = " << words[i];
		std::cout<<std::endl;
	}

	std::cout<< "Длина строк массива:";
	std::cout<<std::endl;
	for (int i = 0; i < arr_size; i++){
		int len = string_length(words[i]);
		std::cout<< words[i] << " -> " << len;
		std::cout<<std::endl;
	}

	// копирование одной строки из массива
	char* copied_word = string_copy(words[2]);
	if (copied_word == NULL){
		for (int i = 0; i < arr_size; i++){
			free(words[i]);
		}
		return 1;
	}

	std::cout<< "Исходная строка для копии:" << words[2];
	std::cout<<std::endl;
	std::cout<< "Скопированная строка:" << copied_word;
	std::cout<<std::endl;

	// конкатенация двух строк из массива
	char* cat_base = string_copy(words[0]);
	if (cat_base == NULL){
		free(copied_word);
		for (int i = 0; i < arr_size; i++){
			free(words[i]);
		}
		return 1;
	}

	char* merged = string_cat(cat_base, words[1]);
	if (merged == NULL){
		free(cat_base);
		free(copied_word);
		for (int i = 0; i < arr_size; i++){
			free(words[i]);
		}
		return 1;
	}

	std::cout<< "Объеденненые строки (words[0] + words[1]):" << merged;
	std::cout<<std::endl;

	int cmp_1 = string_compare(words[1], words[3]);
	int cmp_2 = string_compare(words[2], copied_word);

	std::cout<< "Сравнение words[1] и words[3] (strcmp): " << cmp_1;
	std::cout<<std::endl;
	std::cout<< "Сравнение words[2] и copied_word (strcmp): " << cmp_2;
	std::cout<<std::endl;

	free(copied_word);
	free(merged);
	for (int i = 0; i < arr_size; i++){
		free(words[i]);
	}

	return 0;
}
