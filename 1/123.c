#include <stdio.h>
#include <locale.h>


void Archive(const char* FileNameIn, const char* FileNameOut);
void Create_Registr(struct Registr *datasymbol);


//dearchive
void DeArchive(const char* FileNameIn, const char* FileNameOut);



void Compare_File(const char* FileNameIn, const char* FileNameOut);

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
	printf("���������..\n\n");
	output = fopen(FileNameOut, "wb");
	if (output == NULL) printf("error");
	DataRead(FileNameIn);
	if (length_registr == 0)
	{
		printf("���� ���� ��� �� ����������!\n");
		return;
	}
struct Registr *DataSymbol;
	DataSymbol = (int*)malloc(length_registr * sizeof(struct Registr));
	Create_Registr(DataSymbol);
}
