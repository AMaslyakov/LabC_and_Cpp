#include <iostream>
#include <fstream>
#include <filesystem>

const char fname[] = "new_file.txt";

int main(void){
	// создаем новый файл, если он еще не существует
	if (std::filesystem::exists(fname)){
		std::cout<< "Ошибочная ситуация! Файл " << fname << " уже существует.";
		std::cout<<std::endl;
		return 0;
	}

	std::ofstream ofs(fname, std::ios::out);
	if (!ofs){
		std::cout<< "Ошибочная ситуация! Файл " << fname << " уже существует.";
		std::cout<<std::endl;
		return 0;
	}

	ofs << "Эта строка записывается в новый файл";
	ofs.close();

	// открываем файл для добавления текста в конец
	std::fstream fs;
	fs.open(fname, std::ios::out | std::ios::app);
	if (!fs){
		std::cout<< "Ошибочная ситуация при повторном открытии " << fname;
		std::cout<<std::endl;
		return 1;
	}

	fs << " Сейчас к ней сделано добавление";
	fs.close();

	// открываем файл как входной поток
	std::fstream ifs(fname, std::ios::in);
	if (ifs){
		std::cout<< "В старом файле содержится...";
		std::cout<<std::endl;

		char line[256];
		ifs.getline(line, sizeof(line));
		std::cout<< line;
		std::cout<<std::endl;
	}
	else{
		std::cout<< "Ошибочная ситуация при повторном открытии " << fname;
		std::cout<<std::endl;
		return 1;
	}

	return 0;
}
