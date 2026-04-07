#ifndef STRINGTYPE_H
#define STRINGTYPE_H

#include <iostream>

class StringType{
private:
	char* str;
	int str_size;

	// вычисляем длину строки без std::strlen
	int calc_length(const char* line) const;

	// копируем символы в новую область памяти
	char* make_copy(const char* line) const;

public:
	// конструктор пустой строки
	StringType();

	// конструктор с заданным размером памяти
	StringType(int size);

	// конструктор из c-строки
	StringType(const char* line);

	// конструктор копирования
	StringType(const StringType& other);

	// деструктор нужен, потому что строка хранится в динамической памяти
	~StringType();

	// перегрузка присваивания с защитой от self assignment
	StringType& operator=(const StringType& other);

	// создаем новую строку как сумму двух строк
	StringType operator+(const StringType& other) const;

	// сравниваем строки посимвольно
	bool operator==(const StringType& other) const;

	// возвращаем количество символов
	int length(void) const;

	// читаем строку целиком до перевода строки
	void input(void);

	// выводим строку в поток
	void output(void) const;

	// даем доступ оператору вывода к внутренней строке
	friend std::ostream& operator<<(std::ostream& os, const StringType& line);

	// даем доступ оператору ввода для замены строки
	friend std::istream& operator>>(std::istream& is, StringType& line);
};

std::ostream& operator<<(std::ostream& os, const StringType& line);
std::istream& operator>>(std::istream& is, StringType& line);

#endif
