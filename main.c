#include <stdio.h>
#include <locale.h>
void Archive(const char* FileNameIn, const char* FileNameOut);
void DeArchive(const char* FileNameIn, const char* FileNameOut);
void Compare_File(const char* FileNameIn, const char* FileNameOut);

int main()
{
setlocale(LC_ALL, "Rus");
	const char* ArchFileNameIn = "C:\\12452346\\1234.pdf";
	const char* ArchFileNameOut = "C:\\12452346\\1234.re";
	const char* DeArchFileNameIn = ArchFileNameOut;
	const char* DeArchFileNameOut = "C:\\12452346\\1234.re1";

	Archive(ArchFileNameIn, ArchFileNameOut);
	DeArchive(DeArchFileNameIn, DeArchFileNameOut);
	Compare_File(ArchFileNameIn, DeArchFileNameOut);
       system("pause");
	return 0;
}
void Archive(const char* FileNameIn, const char* FileNameOut)
{
	printf("Архивация..\n\n");
	output = fopen(FileNameOut, "wb");
	if (output == NULL) printf("error");
	DataRead(FileNameIn);
	if (length_registr == 0)
	{
		printf("Файл пуст или не существует!\n");
		return;
	}
}
