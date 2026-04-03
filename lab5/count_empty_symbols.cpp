#include "stdio.h"
#include "ctype.h"

long count_empty_symbols(FILE *in){
	int ch;
	long count = 0;

	while((ch = getc(in)) != EOF){
		if(ch == ' ' || iscntrl((unsigned char)ch))
			count++;
	}
	return count;
}

int main(void){
	int ch;
	char name[50];
	FILE *in;

	printf("Введите имя файла для просмотра: ");
	scanf("%49s", name);

	if((in=fopen(name, "r"))==NULL)
		printf("Файл %s не открыт", name);
	else{
		while((ch=getc(in)) != EOF){
			putchar(ch);
		}
		rewind(in);
		printf("\n\nКоличество пустых символов (включая управляющие): %ld\n", count_empty_symbols(in));
		fclose(in);
	}
	return 0;
}

