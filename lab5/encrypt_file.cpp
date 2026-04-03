#include "stdio.h"
#include "string.h"

int encrypt_file(FILE *in, FILE *out, const unsigned char *key, size_t key_len){
	int ch;
	size_t key_index = 0;

	while((ch = fgetc(in)) != EOF){
		unsigned char encrypted;

		encrypted = (unsigned char)ch ^ key[key_index];
		if(fputc(encrypted, out) == EOF)
			return 0;

		key_index++;
		if(key_index == key_len)
			key_index = 0;
	}

	return ferror(in) == 0;
}

void build_output_file_name(const char *input_file_name, char *output_file_name, size_t size){
	const char *dot;
	const char *slash;
	size_t base_len;

	slash = strrchr(input_file_name, '/');
	dot = strrchr(input_file_name, '.');
	if(dot != NULL && (slash == NULL || dot > slash))
		base_len = (size_t)(dot - input_file_name);
	else
		base_len = strlen(input_file_name);

	if(base_len + strlen("_enc.txt") + 1 > size){
		output_file_name[0] = '\0';
		return;
	}

	memcpy(output_file_name, input_file_name, base_len);
	output_file_name[base_len] = '\0';
	strcat(output_file_name, "_enc.txt");
}

int main(void){
	FILE *in;
	FILE *out;
	const unsigned char *key;
	size_t key_len;
	char input_file_name[256];
	char output_file_name[300];
	char key_buffer[256];

	printf("Введите имя файла для шифрования: ");
	if(scanf("%255s", input_file_name) != 1){
		printf("Ошибка ввода имени файла\n");
		return 1;
	}

	printf("Введите ключ шифрования: ");
	if(scanf("%255s", key_buffer) != 1){
		printf("Ошибка ввода ключа\n");
		return 1;
	}

	build_output_file_name(input_file_name, output_file_name, sizeof(output_file_name));
	if(output_file_name[0] == '\0'){
		printf("Слишком длинное имя выходного файла\n");
		return 1;
	}

	key = (const unsigned char *)key_buffer;
	key_len = strlen((const char *)key);
	if(key_len == 0){
		printf("Ключ не должен быть пустым\n");
		return 1;
	}

	in = fopen(input_file_name, "rb");
	if(in == NULL){
		printf("Не удалось открыть входной файл: %s\n", input_file_name);
		return 1;
	}

	out = fopen(output_file_name, "wb");
	if(out == NULL){
		printf("Не удалось открыть выходной файл: %s\n", output_file_name);
		fclose(in);
		return 1;
	}

	if(!encrypt_file(in, out, key, key_len)){
		printf("Ошибка при обработке файла\n");
		fclose(out);
		fclose(in);
		return 1;
	}

	fclose(out);
	fclose(in);
	printf("Готово. Результат записан в %s\n", output_file_name);
	return 0;
}
