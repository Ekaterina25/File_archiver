#include <stdio.h>
#include <locale.h>

FILE *input;
FILE *input2;
FILE *output;

void Create_Registr(struct Registr *datasymbol);
void DataSort(struct Registr *datasymbol);
void CreateCode(struct Registr *datasymbol, int range_start, int range_stop);
void CreateLibrary(struct Registr *datasymbol);
void Encoding(struct Registr *datasymbol, const char* FileNameIn);
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


///dearchive
struct Registr_dea
{
	char symbol;
	unsigned char length_code;
	unsigned long long code;//8 byte
};
char quant_reg_dea = 0;

void Archive(const char* FileNameIn, const char* FileNameOut)
{
	printf("Архивация..\n\n");
	fopen_s(output, FileNameOut, "wb");
	
	if (output == NULL) printf("error");
	DataRead(FileNameIn);
	if (length_registr == 0)
	{
		printf("Файл пуст или не существует!\n");
		return;
	}
	struct Registr *DataSymbol;
	DataSymbol = (int*)malloc(length_registr * sizeof(struct Registr));
	Create_Registr(DataSymbol);
	DataSort(DataSymbol);
	CreateCode(DataSymbol, 0, quant_reg);
	CreateLibrary(DataSymbol);
	Encoding(DataSymbol, FileNameIn);
	printf("Архивация завершена\nсжато в %f раз(а), процент сжатия: %f\n\n",
		length_input_file / length_output_file, 100 * (1 - length_output_file / length_input_file));
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