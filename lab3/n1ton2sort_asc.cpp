#include <iostream>
#include <limits>



int partition(int arr[], int left, int right){
	int index = (left + right) / 2; // индекс разделения массива на партиции, можно задать случайно
	int value = arr[index]; //случайное значение
	int i = left;
	int j = right;
	while(i<=j){
			while (arr[i] > value) { //находим элемент с значением больше value
			i++;
		}
		while(arr[j]<value) {  // находим элемент со значением меньше value
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
	
	std::cout<< "Введите N1(от 0 до " << n-1 << "):"; 
	int N1;
	int N2;
	while (true) {
		// Проверка ввода, если число будет не в диапазоне массива,
		// то можно будет ввести повторно 
		std::cout << std::endl;
		if (std::cin >> N1 && N1 >= 0 && N1 < n) {
			break;
		}
		std::cout << "Ошибка: N1 должен быть целым числом в диапазоне [0, " << n - 1 << "]." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Введите N1:";
	}
	// N2 должно быть больше N1, но меньше n 
	std::cout << "Введите N2(от"<< N1+1 <<" до " << n-1 << "):";
	while (true) {
		// Проверка ввода 
		std::cout << std::endl;
		if (std::cin >> N2 && N2 >= 0 && N2 < n && N1 < N2) {
			break;
		}
		std::cout << "Ошибка: N2 должен быть целым числом в диапазоне [0, " << n - 1 << "] и больше N1." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Введите N2:";
	}

	// Сортировка диапазона N1..N2
	quickSort(arr, N1, N2);
	
	//Отсортированный массив
	for (int i = 0; i < n; i++) std::cout << arr[i] << ' ';
	std::cout << std::endl;
	return 0;
}
