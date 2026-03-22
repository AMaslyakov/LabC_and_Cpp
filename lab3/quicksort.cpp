#include <iostream>



int partition(int arr[], int left, int right){
	int index = (left + right) / 2; // индекс разделения массива на партиции, можно задать случайно
	int value = arr[index]; //случайное значение
	int i = left;
	int j = right;
	while(i<=j){
			while (arr[i] < value) { //находим элемент с значением больше value
			i++;
		}
		while(arr[j]>value) {  // находим элемент со значением меньше value
			j--;
		}
		// если i-ый элемент находится левее j-го элемента меняем элементы местами
		if(i<=j){
			int t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
			i++;
			j--;
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

	// Быстрая сортировка
	quickSort(arr, 0, n-1);
	
	//Отсортированный массив
	for (int i = 0; i < n; i++) std::cout << arr[i] << ' ';
	std::cout << std::endl;
	return 0;
}
