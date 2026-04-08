/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Пример сборки: make build search_sub_string.cpp
Пример запуска: make run search_sub_string.cpp
*/

#include "stdio.h"
#include "string.h"

void search_sub_string(FILE *in, const char *sub_string, const char *result_file_name){
	FILE *out;
	char line[1024];
	int line_number = 0;
	int match_lines = 0;

	out = fopen(result_file_name, "w");
	if(out == NULL){
		printf("Файл %s не открыт\n", result_file_name);
		return;
	}

	fprintf(out, "Подстрока для поиска: \"%s\"\n\n", sub_string);
	while(fgets(line, sizeof(line), in) != NULL){
		line_number++;
		if(strstr(line, sub_string) != NULL){
			size_t len;

			match_lines++;
			fprintf(out, "Строка %d: %s", line_number, line);
			len = strlen(line);
			if(len > 0 && line[len - 1] != '\n')
				fputc('\n', out);
		}
	}

	if(match_lines == 0)
		fprintf(out, "Совпадений не найдено.\n");
	else
		fprintf(out, "\nНайдено строк с подстрокой: %d\n", match_lines);

	fclose(out);
}

int main(void){
	int ch;
	char name[50], sub_string[100];
	FILE *in;
	const char result_file_name[] = "search_result.txt";

	printf("Введите имя файла для просмотра: ");
	scanf("%49s", name);

	printf("Введите подстроку для поиска: ");
	scanf("%99s", sub_string);

	if((in=fopen(name, "r"))==NULL)
		printf("Файл %s не открыт\n", name);
	else{
		while((ch=getc(in)) != EOF){
			putchar(ch);
		}
		rewind(in);
		search_sub_string(in, sub_string, result_file_name);
		fclose(in);
		printf("\n\nРезультат поиска сохранен в файл %s\n", result_file_name);
	}
	return 0;
}
