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
