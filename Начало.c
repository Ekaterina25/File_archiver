#include <stdio.h>

void Archive(const char* FileNameIn, const char* FileNameOut);
void DeArchive(const char* FileNameIn, const char* FileNameOut);
void Compare_File(const char* FileNameIn, const char* FileNameOut);

int main()
{

	const char* ArchFileNameIn = "C:\\12452346\\1234.pdf";
	const char* ArchFileNameOut = "C:\\12452346\\1234.re";
	const char* DeArchFileNameIn = ArchFileNameOut;
	const char* DeArchFileNameOut = "C:\\12452346\\1234.re1";
	
	Archive(ArchFileNameIn, ArchFileNameOut);
	DeArchive(DeArchFileNameIn, DeArchFileNameOut);
	Compare_File(ArchFileNameIn, DeArchFileNameOut);

	return 0;
}
