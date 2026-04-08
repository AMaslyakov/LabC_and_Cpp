/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Пример сборки: make build prog_stream_state.cpp
Пример запуска: make run prog_stream_state.cpp
*/

#include <iostream>
#include <sstream>

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
	std::istringstream input_stream("10 20 abc 30");
	int value;
	char bad_token[32];

	print_stream_state("входной поток в начале", input_stream);

	// читаем первые два числа без ошибок
	input_stream >> value;
	std::cout<< "Первое число: " << value;
	std::cout<<std::endl;

	input_stream >> value;
	std::cout<< "Второе число: " << value;
	std::cout<<std::endl;

	print_stream_state("входной поток после чтения двух чисел", input_stream);

	// пытаемся прочитать число из текста abc и получаем failbit
	input_stream >> value;
	if (input_stream.fail()){
		std::cout<< "При чтении следующего числа произошла ошибка.";
		std::cout<<std::endl;
	}
	print_stream_state("входной поток после ошибочного чтения числа", input_stream);

	// сбрасываем флаг ошибки и пропускаем ошибочный фрагмент
	input_stream.clear();
	print_stream_state("входной поток после clear()", input_stream);

	input_stream >> bad_token;
	std::cout<< "Пропущен ошибочный фрагмент: " << bad_token;
	std::cout<<std::endl;
	print_stream_state("входной поток после чтения ошибочного фрагмента как строки", input_stream);

	// после восстановления снова читаем число
	input_stream >> value;
	std::cout<< "Следующее число после восстановления: " << value;
	std::cout<<std::endl;
	print_stream_state("входной поток после чтения последнего числа", input_stream);

	// пробуем читать дальше и получаем eofbit и failbit
	input_stream >> value;
	print_stream_state("входной поток после чтения за концом данных", input_stream);

	// вручную меняем состояние потока
	input_stream.clear();
	print_stream_state("входной поток после повторного clear()", input_stream);

	input_stream.setstate(std::ios::failbit);
	print_stream_state("входной поток после setstate(failbit)", input_stream);

	input_stream.clear();
	input_stream.setstate(std::ios::eofbit);
	print_stream_state("входной поток после setstate(eofbit)", input_stream);

	input_stream.clear();
	print_stream_state("входной поток в конце программы", input_stream);

	return 0;
}
