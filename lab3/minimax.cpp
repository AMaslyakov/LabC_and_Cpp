#include <iostream>
#include <ostream>

int main(void) {
	int arr[] = {2,5,-8,1,4,6,3,-5,-9,13,0,4,9};
	int imin, imax;
	int n = sizeof(arr) / sizeof(int);

	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;

	for (int i = 0; i < n / 2; i++) {
		imin = i;
		imax = i;

		for (int j = i + 1; j < n - i; j++) {
			if (arr[j] < arr[imin]) imin = j;
			if (arr[j] > arr[imax]) imax = j;
		}

		int t = arr[i];
		arr[i] = arr[imin];
		arr[imin] = t;

		// Если максимум был на месте i, после первой перестановки он сместился в imin.
		if (imax == i) imax = imin;

		t = arr[n - 1 - i];
		arr[n - 1 - i] = arr[imax];
		arr[imax] = t;
	}

	for (int i = 0; i < n; i++) std::cout << arr[i] << ' ';
	std::cout << std::endl;
	return 0;
}
