#include <iostream>
#include <fstream>
#include <cstring>

int encrypt_file(std::ifstream& in, std::ofstream& out, const unsigned char* key, size_t key_len){
	char ch;
	size_t key_index = 0;

	while (in.get(ch)){
		unsigned char encrypted;

		encrypted = static_cast<unsigned char>(ch) ^ key[key_index];
		out.put(static_cast<char>(encrypted));
		if (!out){
			return 0;
		}

		key_index++;
		if (key_index == key_len){
			key_index = 0;
		}
	}

	return in.eof() != 0;
}

void build_output_file_name(const char* input_file_name, char* output_file_name, size_t size){
	const char* dot;
	const char* slash;
	size_t base_len;

	slash = std::strrchr(input_file_name, '/');
	dot = std::strrchr(input_file_name, '.');
	if (dot != NULL && (slash == NULL || dot > slash)){
		base_len = static_cast<size_t>(dot - input_file_name);
	}
	else{
		base_len = std::strlen(input_file_name);
	}

	if (base_len + std::strlen("_enc.txt") + 1 > size){
		output_file_name[0] = '\0';
		return;
	}

	std::memcpy(output_file_name, input_file_name, base_len);
	output_file_name[base_len] = '\0';
	std::strcat(output_file_name, "_enc.txt");
}

int main(void){
	std::ifstream in;
	std::ofstream out;
	const unsigned char* key;
	size_t key_len;
	char input_file_name[256];
	char output_file_name[300];
	char key_buffer[256];

	std::cout<< "Введите имя файла для шифрования: ";
	if (!(std::cin >> input_file_name)){
		std::cout<< "Ошибка ввода имени файла";
		std::cout<<std::endl;
		return 1;
	}

	std::cout<< "Введите ключ шифрования: ";
	if (!(std::cin >> key_buffer)){
		std::cout<< "Ошибка ввода ключа";
		std::cout<<std::endl;
		return 1;
	}

	build_output_file_name(input_file_name, output_file_name, sizeof(output_file_name));
	if (output_file_name[0] == '\0'){
		std::cout<< "Слишком длинное имя выходного файла";
		std::cout<<std::endl;
		return 1;
	}

	key = reinterpret_cast<const unsigned char*>(key_buffer);
	key_len = std::strlen(reinterpret_cast<const char*>(key));
	if (key_len == 0){
		std::cout<< "Ключ не должен быть пустым";
		std::cout<<std::endl;
		return 1;
	}

	// открываем входной файл в двоичном режиме
	in.open(input_file_name, std::ios::in | std::ios::binary);
	if (!in){
		std::cout<< "Не удалось открыть входной файл: " << input_file_name;
		std::cout<<std::endl;
		return 1;
	}

	// открываем выходной файл в двоичном режиме
	out.open(output_file_name, std::ios::out | std::ios::binary);
	if (!out){
		std::cout<< "Не удалось открыть выходной файл: " << output_file_name;
		std::cout<<std::endl;
		in.close();
		return 1;
	}

	if (!encrypt_file(in, out, key, key_len)){
		std::cout<< "Ошибка при обработке файла";
		std::cout<<std::endl;
		out.close();
		in.close();
		return 1;
	}

	out.close();
	in.close();
	std::cout<< "Готово. Результат записан в " << output_file_name;
	std::cout<<std::endl;

	return 0;
}
