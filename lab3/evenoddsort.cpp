/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Пример сборки: make build evenoddsort.cpp
Пример запуска: make run evenoddsort.cpp
*/

#include <iostream>

bool evenOrOdd(int a, int b)
{
    bool aEven = (a % 2 == 0);
    bool bEven = (b % 2 == 0);

    if (aEven && !bEven) return true;
    if (!aEven && bEven) return false;
    if (aEven && bEven) return a < b;   // возрастание
    return a > b;                       // убывание для нечётных
}

int partition(int arr[], int left, int right){
	int index = (left + right) / 2; // индекс разделения массива на партиции, можно задать случайно
	int value = arr[index];
	int i = left;
	int j = right;
	while(i<=j){
		while (evenOrOdd(arr[i], value)) { 
			++i;
		}
		while(evenOrOdd(value, arr[j])) {
			--j;
		}
		// если i-ый элемент находится не левее j-го элемента меняем элементы местами
		if(i<=j){
			int t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
			++i;
			--j;
		}
	}
	return i;

}


void quickSort(int arr[], int left, int right){
	if(left < right){

		int split_index = partition(arr, left, right);
		quickSort(arr,  left,  split_index - 1);
		quickSort(arr,  split_index, right);
	}
}


int main(void) {
	int arr[] = {0, 23, 2, 12 , -1, -91, 12, 44, 65, 10, -100, 123, 3, 4, 17, -2};
	int n = sizeof(arr) / sizeof(int);

	// Вывод массива до сортировки
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;

	quickSort(arr, 0, n-1);
	
	//Отсортированный массив
	for (int i = 0; i < n; i++) std::cout << arr[i] << ' ';
	std::cout << std::endl;
	return 0;
}
