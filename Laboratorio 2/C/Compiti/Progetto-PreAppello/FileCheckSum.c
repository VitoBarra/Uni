#include <stdlib.h>
typedef struct fileCheckSum
{
    char FileName[255];
    long CheckSum;
} FileCheckSum;

FileCheckSum *InitFileCheckSum();
void FreeFileCheckSum(FileCheckSum *fcs);

FileCheckSum *InitFileCheckSum()
{
    FileCheckSum *fcs = calloc(1, sizeof(FileCheckSum));
    fcs->CheckSum = 0;
    return fcs;
}
void FreeFileCheckSum(FileCheckSum *fcs)
{
    free(fcs);
}