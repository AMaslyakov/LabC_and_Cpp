/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Пример сборки: make build bublesort.cpp
Пример запуска: make run bublesort.cpp
*/

#include <iostream>
#include <ostream>

int main(void) {
	int arr[] = {23,2,5,-8,1,4,6,3,-5,-9,13,0,4,9,44,};
	int n = sizeof(arr) / sizeof(int);

	// Вывод массива до сортировки
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;

	// Сортировка пузырьком
	
	bool swapped = true; // для того чтобы войти в цикл
	int end = n-1; // граница перебора пузырьком
	while(swapped){
		swapped = false; // сброс перед каждым перербором цикла
		for(int i=0; i<end; i++){
			if(arr[i]>arr[i+1]){
				int t = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = t;
				swapped = true;
			}
		}
		end--; // для того чтобы не проверять уже отсортированные элементы
	}
	//Отсортированный массив
	for (int i = 0; i < n; i++) std::cout << arr[i] << ' ';
	std::cout << std::endl;
	return 0;
}
