#include <stdio.h>
#include <stdlib.h>

FILE *input;
FILE *output;

///archive
struct Register
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
void Create_Register(struct Register *datasymbol);
void DataSort(struct Register *datasymbol);
void CreateCode(struct Register *datasymbol, int range_start, int range_stop);
void WriteCode(struct Register *datasymbol, char code, int range_start, int range_stop);
void CreateLibrary(struct Register *datasymbol);
void WriteToFile(unsigned long long bits, char quantity_bit);
void Encoding(struct Register *datasymbol, const char* FileNameIn);
void CloseOutPutFile();


///archive
long quantity_byte[256] = { 0 };
int length_register = 0;
unsigned char ByteToFile = 0;
char IndexBTF = 7;
float length_input_file = 1;
float length_output_file = 1;


int main()
{
	const char* ArchFileNameIn = "2.txt";
	const char* ArchFileNameOut = "1.txe";
    Archive(ArchFileNameIn, ArchFileNameOut);

	return 0;
}

void Archive(const char* FileNameIn, const char* FileNameOut)
{
	printf("Archivation..\n\n");
	output = fopen(FileNameOut, "wb");
	if (output == NULL) printf("error");
	DataRead(FileNameIn);
	if (length_register == 0)
	{
		printf("The file is empty or does not exist!\n");
		return;
	}
	struct Register *DataSymbol;
	DataSymbol = (int*)malloc(length_register * sizeof(struct Register));
	Create_Register(DataSymbol);
	DataSort(DataSymbol);
	CreateCode(DataSymbol, 0, quant_reg);
	CreateLibrary(DataSymbol);
	Encoding(DataSymbol, FileNameIn);
	printf("Archiving completed\ncompressed %f times, compression percentage: %f\n\n",
		length_input_file / length_output_file, 100 * (1 - length_output_file / length_input_file));
}

void DataRead(const char* FileNameIn)
{
	printf("Reading data ..\n");
	input = fopen(FileNameIn, "rb");
	printf("%s\n", FileNameIn);
	if (input == NULL) return;
	unsigned char byte_input = 0;
	fscanf(input, "%c", &byte_input);
	while (!feof(input))
	{

		if (quantity_byte[byte_input] == 0) length_register++;
		quantity_byte[byte_input]++;
		fscanf(input, "%c", &byte_input);
	}
	length_input_file = ftell(input);
	fclose(input);
	printf("OK\n\n");
}

void Create_Register(struct Register *datasymbol)
{
	printf("Create a data register\n");
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

void DataSort(struct Register *datasymbol)
{
	struct Register dop;
	for (int j = 0; j < quant_reg - 1; j++)
	{
		for (int i = 0; i < quant_reg - 1 - j; i++)
		{
			if ((datasymbol + i)->quantity < (datasymbol + i + 1)->quantity)
			{
				dop = *(datasymbol + i);
				*(datasymbol + i) = *(datasymbol + i + 1);
				*(datasymbol + i + 1) = dop;

			}
		}

	}
	printf("OK\n\n");
}

void CreateCode(struct Register *datasymbol, int range_start, int range_stop)
{
	if (range_stop - range_start == quant_reg) printf("Creating encryption codes ..\n");
	double summary_frequency = 0;
	for (int i = range_start; i < range_stop; i++)
		summary_frequency += (datasymbol + i)->frequency;
	float half = summary_frequency / 2;
	int index = range_start;
	summary_frequency = (datasymbol + index)->frequency;
	while (summary_frequency <= half)
	{
		index++;
		summary_frequency += (datasymbol + index)->frequency;
	}
	if (range_start == index) index++;
	WriteCode(datasymbol, 0, range_start, index);
	if (range_start + 1 != index) CreateCode(datasymbol, range_start, index);
	WriteCode(datasymbol, 1, index, range_stop);
	if ((index + 1 != range_stop) && (index != range_stop)) CreateCode(datasymbol, index, range_stop);
	if (range_stop - range_start == quant_reg) printf("OK\n\n");
}

void WriteCode(struct Register *datasymbol, char code, int range_start, int range_stop)
{
	for (int i = range_start; i < range_stop; i++)
	{
		(datasymbol + i)->code = ((datasymbol + i)->code << 1) + code;
		(datasymbol + i)->length_code++;
	}
}


void CreateLibrary(struct Register *datasymbol)
{
	printf("Creating an encryption library ..\n");
	WriteToFile(quant_reg, 16);
	unsigned long long quantity_bits = 0;
	for (int i = 0; i < quant_reg; i++)
		quantity_bits += (datasymbol + i)->length_code*(datasymbol + i)->quantity;
	WriteToFile(quantity_bits, 64);

	for (int i = 0; i < quant_reg; i++)
	{
		WriteToFile((datasymbol + i)->symbol, 8);
		WriteToFile((datasymbol + i)->length_code, 8);
		WriteToFile((datasymbol + i)->code, (datasymbol + i)->length_code);
	}
	printf("OK\n\n");
}

void WriteToFile(unsigned long long bits, char quantity_bit)
{
	for (int i = quantity_bit - 1; i >= 0; i--)
	{
		ByteToFile |= (((bits >> i) % 2) << IndexBTF);
		IndexBTF--;
		if (IndexBTF == -1)
		{
			fprintf(output, "%c", ByteToFile);//отправить байт в файл
			ByteToFile = 0;
			IndexBTF = 7;
		}
	}

}

void Encoding(struct Register *datasymbol, const char* FileNameIn)
{
	printf("Archiving ..\n");

	input = fopen(FileNameIn, "rb");
	char byte_input = 0;
	int pos_DS;
	fscanf(input, "%c", &byte_input);
	while (!feof(input))//чтение данных
	{
		pos_DS = 0;
		while (byte_input != (datasymbol + pos_DS)->symbol) pos_DS++;//поиск нужной записи регистра
		WriteToFile((datasymbol + pos_DS)->code, (datasymbol + pos_DS)->length_code);
		fscanf(input, "%c", &byte_input);
	}
	fclose(input);
	CloseOutPutFile();
	printf("OK\n\n");
}

void CloseOutPutFile()
{
	if (IndexBTF != 7) WriteToFile(0, IndexBTF + 1);
	length_output_file = ftell(output);
	fclose(output);
}

