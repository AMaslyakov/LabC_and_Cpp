#include <iostream>

class StringType{
private:
	char* str;

	// вычисляем длину строки без std::strlen
	int calc_length(const char* line) const{
		int i = 0;
		while (line[i] != '\0'){
			i++;
		}
		return i;
	}

	// копируем символы в новую область памяти
	char* make_copy(const char* line) const{
		int len = calc_length(line);
		char* new_str = new char[len + 1];

		for (int i = 0; i < len; i++){
			new_str[i] = line[i];
		}
		new_str[len] = '\0';

		return new_str;
	}

public:
	// конструктор пустой строки
	StringType(){
		str = make_copy("");
	}

	// конструктор из c-строки
	StringType(const char* line){
		str = make_copy(line);
	}

	// конструктор копирования
	StringType(const StringType& other){
		str = make_copy(other.str);
	}

	// освобождаем выделенную память
	~StringType(){
		delete[] str;
	}

	// перегрузка присваивания с защитой от self assignment
	StringType& operator=(const StringType& other){
		if (this != &other){
			delete[] str;
			str = make_copy(other.str);
		}
		return *this;
	}

	// создаем новую строку как сумму двух строк
	StringType operator+(const StringType& other) const{
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

	// сравниваем строки посимвольно
	bool operator==(const StringType& other) const{
		int i = 0;
		while (str[i] != '\0' && other.str[i] != '\0'){
			if (str[i] != other.str[i]){
				return false;
			}
			i++;
		}
		return str[i] == other.str[i];
	}

	// возвращаем количество символов
	int length(void) const{
		return calc_length(str);
	}

	// читаем строку целиком до перевода строки
	void input(void){
		char line[256];
		std::cin.getline(line, 256);

		delete[] str;
		str = make_copy(line);
	}

	// выводим строку в поток
	void output(void) const{
		std::cout<< str;
	}

	// даем доступ оператору вывода к внутренней строке
	friend std::ostream& operator<<(std::ostream& os, const StringType& line);

	// даем доступ оператору ввода для замены строки
	friend std::istream& operator>>(std::istream& is, StringType& line);
};

std::ostream& operator<<(std::ostream& os, const StringType& line){
	os << line.str;
	return os;
}

std::istream& operator>>(std::istream& is, StringType& line){
	char buffer[256];
	is.getline(buffer, 256);

	delete[] line.str;
	line.str = line.make_copy(buffer);

	return is;
}

int main(void){
	StringType line1("abcdef");
	StringType line2("1234567890");
	StringType line3;
	StringType copied_line;

	// присваиваем значение через оператор =
	copied_line = line1;

	std::cout<< "Строка 1:" << line1;
	std::cout<<std::endl;
	std::cout<< "Строка 2:" << line2;
	std::cout<<std::endl;
	std::cout<< "Скопированная строка:" << copied_line;
	std::cout<<std::endl;

	std::cout<< "Длина строки 1: " << line1.length();
	std::cout<<std::endl;
	std::cout<< "Длина строки 2: " << line2.length();
	std::cout<<std::endl;

	// сцепляем две строки
	line3 = line1 + line2;
	std::cout<< "Объеденненые строки:" << line3;
	std::cout<<std::endl;

	// сравниваем одинаковые и разные строки
	std::cout<< "line1 == copied_line: " << (line1 == copied_line);
	std::cout<<std::endl;
	std::cout<< "line1 == line2: " << (line1 == line2);
	std::cout<<std::endl;

	StringType input_line;
	std::cout<< "Введите строку: ";
	input_line.input();

	std::cout<< "Введенная строка методом output: ";
	input_line.output();
	std::cout<<std::endl;

	std::cout<< "Введите еще одну строку: ";
	StringType input_line2;
	std::cin >> input_line2;

	std::cout<< "Введенная строка оператором >> : " << input_line2;
	std::cout<<std::endl;

	return 0;
}
