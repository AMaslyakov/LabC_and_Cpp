/*
Работа выполнялась на ОС GNU/Linux Manjaro x86_64.
Для компиляции и запуска нужно использовать make.
Пример сборки: make build page_number_last_line.cpp
Пример запуска: make run page_number_last_line.cpp
*/

#include "stdio.h"
#include "ctype.h"
#include "string.h"

int is_form_feed_line(const char *line){
	size_t i;

	if(line[0] != '\f')
		return 0;
	for(i = 1; line[i] != '\0'; i++){
		if(line[i] != '\r' && line[i] != '\n')
			return 0;
	}
	return 1;
}

void detect_line_ending(const char *line, char *line_ending){
	size_t len = strlen(line);

	if(len >= 2 && line[len - 2] == '\r' && line[len - 1] == '\n'){
		line_ending[0] = '\r';
		line_ending[1] = '\n';
		line_ending[2] = '\0';
	}
	else{
		line_ending[0] = '\n';
		line_ending[1] = '\0';
	}
}

int extract_page_number(const char *line, char *page_number, size_t size){
	size_t i = 0;
	size_t pos = 0;

	while(line[i] != '\0' && !isdigit((unsigned char)line[i]))
		i++;
	while(line[i] != '\0' && isdigit((unsigned char)line[i])){
		if(pos + 1 < size)
			page_number[pos++] = line[i];
		i++;
	}

	page_number[pos] = '\0';
	return pos > 0;
}

void write_page_number(FILE *out, const char *page_number, const char *line_ending){
	fputs(page_number, out);
	fputs(line_ending, out);
}

void move_page_numbers_to_last_line(FILE *in, FILE *out){
	char line[2048];
	char page_number[64];
	char last_line_ending[3] = "\n";
	int expect_page_number = 0;
	int has_page_number = 0;

	while(fgets(line, sizeof(line), in) != NULL){
		detect_line_ending(line, last_line_ending);

		if(is_form_feed_line(line)){
			if(has_page_number){
				write_page_number(out, page_number, last_line_ending);
				has_page_number = 0;
			}
			fputs(line, out);
			expect_page_number = 1;
			continue;
		}

		if(expect_page_number){
			if(extract_page_number(line, page_number, sizeof(page_number))){
				has_page_number = 1;
				expect_page_number = 0;
				continue;
			}
			expect_page_number = 0;
		}

		fputs(line, out);
	}

	if(has_page_number)
		write_page_number(out, page_number, last_line_ending);
}

int main(void){
	char input_file_name[50];
	const char output_file_name[] = "test_last_line.txt";
	FILE *in;
	FILE *out;

	printf("Введите имя исходного файла: ");
	scanf("%49s", input_file_name);

	in = fopen(input_file_name, "r");
	if(in == NULL){
		printf("Файл %s не открыт\n", input_file_name);
		return 1;
	}

	out = fopen(output_file_name, "w");
	if(out == NULL){
		printf("Файл %s не открыт\n", output_file_name);
		fclose(in);
		return 1;
	}

	move_page_numbers_to_last_line(in, out);

	fclose(out);
	fclose(in);
	printf("Результат сохранен в %s\n", output_file_name);
	return 0;
}
