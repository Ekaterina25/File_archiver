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
void DataSort(struct Registr *datasymbol);
void CreateCode(struct Registr *datasymbol, int range_start, int range_stop);

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
	Archive(ArchFileNameIn, ArchFileNameOut);

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
	DataSort(DataSymbol);
	CreateCode(DataSymbol, 0, quant_reg);
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
void Create_Registr(struct Registr *datasymbol)
{
	printf("Создание регистра данных\n");
	quant_reg = 0;
	int pos_in_DS = 0;
	for (int i = 0; i < 256; i++)
		if (quantity_byte[i] != 0)
		{
			(datasymbol + pos_in_DS)->symbol = i;
			(datasymbol + pos_in_DS)->quantity = quantity_byte[i];
			(datasymbol + pos_in_DS)->code = 0;
			(datasymbol + pos_in_DS)->length_code = 0;
			pos_in_DS++;
			quant_reg++;
		}
	float summary_symbol = 0;
	for (int i = 0; i < quant_reg; i++)
		summary_symbol += (datasymbol + i)->quantity;
	for (int i = 0; i < quant_reg; i++)
		(datasymbol + i)->frequency = (datasymbol + i)->quantity / summary_symbol;
}

void DataSort(struct Registr *datasymbol)
{
	char transp = 0;
	struct Registr dop;
	for (int j = 0; j < quant_reg - 1; j++)
	{
		for (int i = 0; i < quant_reg - 1 - j; i++)
		{
			if ((datasymbol + i)->quantity < (datasymbol + i + 1)->quantity)
			{
				dop = *(datasymbol + i);
				*(datasymbol + i) = *(datasymbol + i + 1);
				*(datasymbol + i + 1) = dop;
				transp = 1;
			}
		}
		if (!transp) break;
		transp = 0;
	}
	printf("OK\n\n");
}
