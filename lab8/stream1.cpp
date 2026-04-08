#include <iostream>
#include <fstream>
#include <cctype>

int main(void){
	char in_fname[256];
	char out_fname[256];
	char c;

	std::cout<< "Введите имя входного файла: ";
	std::cin >> in_fname;

	// открываем входной файл
	std::ifstream ifs(in_fname);
	if (!ifs){
		std::cout<< "Не открыт входной файл " << in_fname;
		std::cout<<std::endl;
		return 1;
	}

	std::cout<< "Введите имя выходного файла: ";
	std::cin >> out_fname;

	// открываем выходной файл
	std::ofstream ofs(out_fname);
	if (!ofs){
		std::cout<< "Не открыт выходной файл " << out_fname;
		std::cout<<std::endl;
		return 1;
	}

	// читаем символы из файла, переводим в верхний регистр и записываем в новый файл
	while (ifs.get(c)){
		c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
		ofs.put(c);
	}

	std::cout<< "Файл " << out_fname << " создан.";
	std::cout<<std::endl;

	return 0;
}
