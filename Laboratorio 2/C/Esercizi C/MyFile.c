#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

int copyFileOnlyText(const char* source, const char* dest)
{
	FILE* fs = fopen(source, "rb");
	FILE* fd = fopen(dest, "wb");

	if (fs == NULL) return 1;

	char buffer[BUFFER_SIZE];

	int BufferFill = 0;
	while (!feof(fs) && BufferFill < BUFFER_SIZE - 1 && fgets(&buffer[BufferFill], BUFFER_SIZE - BufferFill, fs))
		BufferFill = strlen(buffer);
	if (ferror(fs)) return 1;

	int eof = feof(fs);


	if (eof)
		fputs(buffer, fd);

	fclose(fs);
	fclose(fd);

	return !eof;
}

int copyFile(const char* source, const char* dest)
{
	FILE* fs = fopen(source, "rb");
	FILE* fd = fopen(dest, "wb");

	if (fs == NULL) return 1;

	char buffer[BUFFER_SIZE];

	int byteW = fread(buffer, sizeof(char), sizeof(char) * BUFFER_SIZE, fs);
	if (ferror(fs)) return 1;

	int eof = feof(fs);

	if (eof)
		fwrite(buffer, sizeof(char), sizeof(char) * byteW, fd);

	fclose(fs);
	fclose(fd);

	return !eof;
}

typedef struct Row
{
	int nrow;
	char* str;
} Row;

typedef struct RowList
{
	int count;
	Row* List;
} RowList;






RowList* RowListConstructor(int MaxRow)
{
	RowList* rowl = malloc(sizeof(RowList));
	rowl->count = 0;
	rowl->List = malloc(sizeof(char*) * MaxRow);
	return rowl;
}

RowList* RowListDiff(RowList rl1, RowList rl2)
{
	RowList* RowListRes = RowListConstructor(rl1.count + rl2.count);
	for (int i = 0; i < rl1.count; i++)
	{
		int present = 0;
		for (int j = 0; j < rl2.count; j++)
		{
			if (strcmp(rl1.List[i].str, rl2.List[j].str) == 0)
			{
				present = 1;
				break;
			}
		}
		if (!present)
			RowListRes->List[RowListRes->count++] = rl1.List[i];
	}
	return RowListRes;
}


void StampaRowList(RowList rl)
{
	for (int i = 0; i < rl.count; i++)
	{
		Row e = rl.List[i];
		printf("%d: %s", e.nrow, e.str);
	}
}

RowList* InizializeRowList(FILE* f, int n)
{
	char* buffer = malloc(sizeof(char) * n);
	int bufferFill = 0;

	RowList* rowl = RowListConstructor(100);
	char* ReadedRowPtr;

	do
	{
		Row* e = &rowl->List[rowl->count];

		ReadedRowPtr = fgets(&buffer[bufferFill], n - bufferFill, f);
		int oldbufferFill = bufferFill;
		bufferFill = strlen(buffer);
		e->nrow = 1 + rowl->count++;
		e->str = malloc(sizeof(char) * (bufferFill - oldbufferFill));
		strcpy(e->str, ReadedRowPtr);

	} while (!feof(f) && bufferFill < n - 1 && ReadedRowPtr);
	free(buffer);

	if (ferror(f) || !feof(f)) return NULL;

	return rowl;
}

int diff(const char* f1, const char* f2)
{
	FILE* fs1 = fopen(f1, "r");
	FILE* fs2 = fopen(f2, "r");

	if (fs1 == NULL || fs2 == NULL) return -1;

	RowList* RowList1 = (InizializeRowList(fs1, BUFFER_SIZE));
	RowList* RowList2 = (InizializeRowList(fs2, BUFFER_SIZE));

	if (RowList1 == NULL || RowList2 == NULL) return -1;



	RowList* RowListRes1 = RowListDiff(*RowList1, *RowList2);
	RowList* RowListRes2 = RowListDiff(*RowList2, *RowList1);

	if (RowListRes1->count == 0 && RowListRes2->count == 0)
		return 0;


	StampaRowList(*RowListRes1);
	StampaRowList(*RowListRes2);
	return 1;

}




