#include <iostream>
#include <fstream>

int main(void){
	char name[256];
	std::fstream fin;

	std::cout<< "Введите имя файла: ";
	std::cin >> name;

	// открываем файл для чтения
	fin.open(name, std::ios::in);

	// проверяем состояние потока
	if (fin){
		std::cout<< "Файл открыт " << name;
		std::cout<<std::endl;
		fin.close();
	}
	else{
		std::cout<< "Не открыт выходной файл " << name;
		std::cout<<std::endl;
		return 1;
	}

	return 0;
}
