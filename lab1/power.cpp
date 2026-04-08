/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Пример сборки: make build FILE=power.cpp
Пример запуска: make run FILE=power.cpp
*/

#include <iostream>

int power(int x, int n);

int main(void){
      int x;
      std::cout << "Введите основание для возвдения в степень:\n";
      if (std::cin >> x) {
          std::cout << "Введено основание:" << x << "\n";
      } else {
          std::cout << "Число должно быть целым\n";
      }
	for(int i=0; i<10; i++){
		int k;
		k = power(x, i);
		std::cout<<"i = "<<i<<", k "<<k<<std::endl;
	}
	return 0;
}

int power(int x, int n){
	int p = 1;
	for(int i=0; i<n; i++) p *= x;
	return p;
}
