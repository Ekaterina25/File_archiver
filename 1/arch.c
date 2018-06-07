#include <stdio.h>
#include <locale.h>
FILE *input;
FILE *output;

///archive
struct Registr
{
	char symbol;
	int quantity;
	float frequency;
	unsigned long long code;//8 byte
	unsigned char length_code;
};
int quant_reg = 0;
void Archive(const char* FileNameIn, const char* FileNameOut);
void DataRead(const char* FileNameIn);
void Create_Registr(struct Registr *datasymbol);

///archive
long quantity_byte[256] = { 0 };
int length_registr = 0;
unsigned char ByteToFile = 0;
char IndexBTF = 7;
float length_input_file = 1;
float length_output_file = 1;

int main(void)
{
    setlocale(LC_ALL, "Rus");
	const char* ArchFileNameIn = "C:\\1234\\2.pdf";
	const char* ArchFileNameOut = "C:\\1234\\1234.123";
	const char* DeArchFileNameIn = ArchFileNameOut;
	const char* DeArchFileNameOut = "C:\\1234\\1234.pdf";

	Archive(ArchFileNameIn, ArchFileNameOut);
	DeArchive(DeArchFileNameIn, DeArchFileNameOut);
	Compare_File(ArchFileNameIn, DeArchFileNameOut);

	system("pause");
	return 0;
}
void Archive(const char* FileNameIn, const char* FileNameOut)
{
	printf("Архивация...\n\n");
	output = fopen(FileNameOut, "wb");
	if (output == NULL) printf("error");
	DataRead(FileNameIn);
	if (length_registr == 0)
	{
		printf("Файл пустой или не существует!\n");
		return;
	}
struct Registr *DataSymbol;
	DataSymbol = (int*)malloc(length_registr * sizeof(struct Registr));
	Create_Registr(DataSymbol);
}

void DataRead(const char* FileNameIn)
{
	printf("Чтение данных...\n");
	input = fopen(FileNameIn, "rb");
	printf("%s\n", FileNameIn);
	if (input == NULL) return;
	unsigned char byte_input = 0;
	fscanf_s(input, "%c", &byte_input);
	while (!feof(input))
	{

		if (quantity_byte[byte_input] == 0) length_registr++;
		quantity_byte[byte_input]++;
		fscanf_s(input, "%c", &byte_input);
	}
	length_input_file = ftell(input);
	fclose(input);
	printf("OK\n\n");
}
