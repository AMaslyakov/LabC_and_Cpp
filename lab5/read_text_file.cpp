#include "stdio.h"

int main(void){
	char ch, name[50];
	FILE *in;

	printf("Введите имя файла для просмотра: ");
	scanf("%s", name);

	if((in=fopen(name, "r"))==NULL)
		printf("Файл %s не открыт", name);
	else
		while(!feof(in)){
			ch=getc(in);
			putchar(ch);
		}
	return 0;
}


