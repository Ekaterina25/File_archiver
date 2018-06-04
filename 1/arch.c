#include <stdio.h>
#include <locale.h>

FILE *input;
FILE *input2;
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
int quant_reg = 0;git


///dearchive
struct Registr_dea
{
	char symbol;
	unsigned char length_code;
	unsigned long long code;//8 byte
};
char quant_reg_dea = 0;