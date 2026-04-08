/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Пример сборки: make build stream1_state_change.cpp
Пример запуска: make run stream1_state_change.cpp
*/

#include <iostream>
#include <fstream>
#include <cctype>

void print_stream_state(const char* stream_name, std::ios& stream){
	std::cout<< "Состояние потока " << stream_name << ": ";
	std::cout<< "good=" << stream.good() << ", ";
	std::cout<< "fail=" << stream.fail() << ", ";
	std::cout<< "eof=" << stream.eof() << ", ";
	std::cout<< "bad=" << stream.bad() << ", ";
	std::cout<< "rdstate=" << static_cast<int>(stream.rdstate());
	std::cout<<std::endl;
}

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
	print_stream_state("ifs после открытия", ifs);

	std::cout<< "Введите имя выходного файла: ";
	std::cin >> out_fname;

	// открываем выходной файл
	std::ofstream ofs(out_fname);
	if (!ofs){
		std::cout<< "Не открыт выходной файл " << out_fname;
		std::cout<<std::endl;
		return 1;
	}
	print_stream_state("ofs после открытия", ofs);

	// читаем символы из файла, переводим в верхний регистр и записываем в новый файл
	while (ifs.get(c)){
		c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
		ofs.put(c);
	}

	std::cout<< "Файл " << out_fname << " создан.";
	std::cout<<std::endl;

	// после чтения до конца файла у входного потока установлен eofbit
	print_stream_state("ifs после чтения до конца файла", ifs);

	// очищаем флаги состояния и снова делаем поток рабочим
	ifs.clear();
	print_stream_state("ifs после clear()", ifs);

	// возвращаемся в начало файла и повторно читаем первый символ
	ifs.seekg(0, std::ios::beg);
	print_stream_state("ifs после seekg(0)", ifs);

	if (ifs.get(c)){
		std::cout<< "Первый символ после восстановления потока: " << c;
		std::cout<<std::endl;
	}
	print_stream_state("ifs после повторного чтения", ifs);

	// вручную устанавливаем failbit и затем снимаем его
	ofs.setstate(std::ios::failbit);
	print_stream_state("ofs после setstate(failbit)", ofs);

	ofs.clear();
	print_stream_state("ofs после clear()", ofs);

	return 0;
}
