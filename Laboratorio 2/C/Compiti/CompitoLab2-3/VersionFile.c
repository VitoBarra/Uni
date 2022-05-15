///*
//Implementare una libreria per lavorare con liste bidimensionali utilizzate per tenere traccia di versioni di file. Ogni file è definito dal suo path assoluto, più una lista di versioni. Per ogni versione abbiamo un ID numerico e una timestamp con la data della versione.
//
//Scrivere una struttura di dati FileList che utilizza liste concatenate per mantenere le versioni, e per mantenere la lista stessa di file.
//
//Implementare le seguenti funzioni:
//
//int addFile(FileList* fl ,const char* filename) - aggiunge un file nuovo alla lista (in testa) e restituisce 0 in caso di successo, 1 in caso di errore. La lista di versioni del nuovo file è vuota. Se il file esiste già non aggiunge niente e restituisce 1.
//
//int addVersion(FileList* fl, const char* filename, int versionID, time_t timestamp) - aggiunge una nuova versione alla lista di versione del file con il nome filename. Se il file non esiste nella lista, lo aggiunge. La funzione restituisce 0 in caso di successo, 1 in caso di errore.
//
//int removeFile(FileList* fl ,const char* filename) - rimuove un file con tutte le sue versioni dalla lista. Se il file non esiste restituisce 1, altrimenti 0.
//
//int removeVersion (FileList* fl, const char* filename, int versionID)  - rimuove una versione da un file nella lista. Se il file non esiste, restituisce 1, se la versione non esiste, restituisce 2, altrimenti 0.
//
//VersionList getHist(FileList fl, const char* filename) - restituisce la lista di versioni del file passato come parametro. Il tipo di return VersionList è lo stesso della struttura di dati utilizzata per mantenere la lista di versioni.
//
//void freeFileList(FileList* fl) - libera la memoria per la lista FileList. Dopo la chiamata il puntatore fl deve essere NULL.
//
//FileList loadFileList(const char* file) - legge una lista da un file testuale. Ogni file e le sue versioni sono rappresentate su una riga nel formato “nome file: versione, timestamp; versione, timestamp; … versione, timestamp” Restituisce  la lista di file, NULL in caso di errore.
//
//int saveFileList(FileList f, const char* file) - salva una lista di file in un file testuale, nel formatto descritto sopra. La funzione restituisce 0 in caso di successo, 1 in caso di errore.
//
//Non editare la funzione main e i file di input e output che trovate su REPL.
//
//*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>


typedef struct Version
{
	int ID;
	time_t  Timestamp;
	struct Version* NextVersion;
}Version;
typedef Version* VersionList;

typedef struct File
{
	char* FileName;
	VersionList VersionListHead;
	struct File* NextFile;
} File;
typedef File* FileList;

typedef struct
{
	int Find;
	File* Predptr;
	File* ptr;
	File* Nextptr;
} FindFileTupla;

typedef struct
{
	int Find;
	Version* Predptr;
	Version* ptr;
	Version* Nextptr;
} FindVersionTupla;




int addFile(FileList* fl, const char* filename);
int addVersion(FileList* fl, const char* filename, int versionID, time_t timestamp);
int removeFile(FileList* fl, const char* filename);
int removeVersion(FileList* fl, const char* filename, int versionID);
VersionList getHist(FileList fl, const char* filename);
void freeFileList(FileList* fl);
FileList loadFileList(const char* file);
int saveFileList(FileList f, const char* file);

int main(void) {
	char fname[100], command[200];
	scanf("%s", fname);

	FileList f = loadFileList(fname);
	VersionList h = NULL;
	if (f) {
		int option;
		scanf("%d", &option);
		switch (option) {
		case 1:
			saveFileList(f, "realout1.txt");
			sprintf(command, "diff %s %s", "out1.txt", "realout1.txt");
			system(command);
			break;

		case 2:
			addFile(&f, "/home/user/f9.txt");
			saveFileList(f, "realout2.txt");
			sprintf(command, "diff %s %s", "out2.txt", "realout2.txt");
			system(command);
			break;

		case 3:
			addVersion(&f, "/home/user/f9.txt", 1, 1637507877);
			saveFileList(f, "realout3.txt");
			sprintf(command, "diff %s %s", "out3.txt", "realout3.txt");
			system(command);
			break;

		case 4:
			addVersion(&f, "/home/user/f2.txt", 2, 1637507890);
			saveFileList(f, "realout4.txt");
			sprintf(command, "diff %s %s", "out4.txt", "realout4.txt");
			system(command);
			break;

		case 5:
			removeFile(&f, "/home/user/f2.txt");
			saveFileList(f, "realout5.txt");
			sprintf(command, "diff %s %s", "out5.txt", "realout5.txt");
			system(command);
			break;

		case 6:
			removeVersion(&f, "/home/user/t3.txt", 2);
			saveFileList(f, "realout6.txt");
			sprintf(command, "diff %s %s", "out6.txt", "realout6.txt");
			system(command);
			break;

		case 7:
			h = getHist(f, "/home/user/t3.txt");
			assert(h != NULL);
			freeFileList(&f);
			assert(f == NULL);
		}
		printf("Done.\n");
	}
	else {
		printf("Errore.\n");
	}
}


//utility
File* ConstructorFile(File* nextFile, const char* filename)
{
	File* newFile = malloc(sizeof(File));
	if (newFile != NULL)
	{
		newFile->NextFile = nextFile;
		newFile->FileName = malloc(sizeof(char) * strlen(filename));
		if (newFile->FileName != NULL)
			strcpy(newFile->FileName, filename);
		newFile->VersionListHead = NULL;
	}
	return newFile;
}

Version* ConstructorVersion(Version* nextVersion, int id, time_t Timestamp)
{
	Version* newVersion = malloc(sizeof(Version));
	if (newVersion != NULL)
	{
		newVersion->ID = id;
		newVersion->Timestamp = Timestamp;
		newVersion->NextVersion = nextVersion;
	}
	return newVersion;
}



//-Find
FindFileTupla* ConstructorFindFile()
{
	FindFileTupla* ff = malloc(sizeof(FindFileTupla));
	if (ff != NULL)
	{
		ff->ptr = NULL;
		ff->Nextptr = NULL;
		ff->Predptr = NULL;
		ff->Find = 0;
	}
	return ff;
}
FindVersionTupla* ConstructorFindVersion()
{
	FindVersionTupla* fv = malloc(sizeof(FindVersionTupla));
	if (fv != NULL)
	{
		fv->ptr = NULL;
		fv->Find = 0;
	}
	return fv;
}

FindFileTupla* FindFile(FileList fl, const char* filename)
{
	if (fl == NULL) return NULL;
	FindFileTupla* ff = ConstructorFindFile();
	for (File* f = fl, *pred = NULL; f != NULL; pred = f, f = f->NextFile)
		if (strcmp(f->FileName, filename) == 0)
		{
			ff->Find = 1;
			ff->Predptr = pred;
			ff->ptr = f;
			ff->Nextptr = f->NextFile;
			return ff;
		}
	return ff;
}
FindVersionTupla* FindVersion(File* File, int ID)
{
	FindVersionTupla* fv = ConstructorFindVersion();
	for (Version* v = File->VersionListHead, *pred = NULL; v != NULL; pred = v, v = v->NextVersion)
		if (v->ID == ID)
		{
			fv->Find = 1;
			fv->Predptr = pred;
			fv->ptr = v;
			fv->Nextptr = v->NextVersion;
			return fv;
		}
	return fv;
}
//-Find


Version* GetTailVersion(File* ptr)
{
	Version* vl = NULL;
	for (vl = ptr->VersionListHead; vl->NextVersion != NULL; vl = vl->NextVersion);
	return vl;
}
File* GetTailFile(File* ptr)
{
	File* fp = NULL;
	for (fp = ptr; fp->NextFile != NULL; fp = fp->NextFile);
	return fp;
}

//------------------

int addFileNoCheckTail(FileList* fl, const char* filename, int find)
{
	if (!find)
	{
		File* f = ConstructorFile(NULL, filename);
		if (*fl != NULL)
		{
			File* tail = GetTailFile(*fl);
			tail->NextFile = f;
		}
		else *fl = f;
	}
	return find;
}

int addFileTail(FileList* fl, const char* filename)
{
	FindFileTupla* ff = FindFile(*fl, filename);
	int find = 0;
	if (ff != NULL)
	{
		find = ff->Find;
		free(ff);
	}
	return addFileNoCheckTail(fl, filename, find);
}
int addFileNoCheckHead(FileList* fl, const char* filename, int find)
{
	if (!find)	(*fl) = ConstructorFile(*fl, filename);
	return find;
}
int addFile(FileList* fl, const char* filename)
{
	FindFileTupla* ff = FindFile(*fl, filename);
	int find = 0;
	if (ff != NULL)
	{
		find = ff->Find;
		free(ff);
	}
	return addFileNoCheckHead(fl, filename, find);
}




int addVersion(FileList* fl, const char* filename, int versionID, time_t timestamp)
{
	FindFileTupla* ff = FindFile(*fl, filename);

	if (!ff->Find)
	{
		int a = addFileNoCheckHead(fl, filename, 0);
		(*fl)->VersionListHead = ConstructorVersion(NULL, versionID, timestamp);
		return a;
	}


	if (ff->ptr->VersionListHead != NULL)
	{
		VersionList vl = GetTailVersion(ff->ptr);
		vl->NextVersion = ConstructorVersion(NULL, versionID, timestamp);
	}
	else
		ff->ptr->VersionListHead = ConstructorVersion(NULL, versionID, timestamp);

	free(ff);

	return 0;
}

int removeFile(FileList* fl, const char* filename)
{
	FindFileTupla* ff = FindFile(*fl, filename);
	if (ff->Find)
	{
		Version* vtemp = NULL;
		for (Version* v = ff->ptr->VersionListHead; v != NULL; v = vtemp)
		{
			vtemp = v->NextVersion;
			free(v);

		}
		free(ff->ptr);
		ff->Predptr->NextFile = ff->Nextptr;
	}
	int code = !ff->Find;
	free(ff);
	return code;
}

int removeVersion(FileList* fl, const char* filename, int versionID)
{
	int code = 0;
	FindFileTupla* ff = FindFile(*fl, filename);
	if (ff->Find)
	{
		FindVersionTupla* fv = FindVersion(ff->ptr, versionID);
		if (fv->Find)
		{
			free(fv->ptr);
			fv->Predptr->NextVersion = fv->Nextptr;
		}
		else
			code = 2;

		free(fv);
	}
	else
		code = 1;

	free(ff);
	return code;
}

VersionList getHist(FileList fl, const char* filename)
{
	FindFileTupla* ff = FindFile(fl, filename);
	return ff->ptr->VersionListHead;
}

void freeFileList(FileList* fl)
{
	Version* vtemp = NULL;
	File* ftemp = NULL;
	for (File* f = (*fl); f != NULL; f = ftemp)
	{
		for (Version* v = f->VersionListHead; v != NULL; v = vtemp)
		{
			vtemp = v->NextVersion;
			free(v);
		}
		ftemp = f->NextFile;
		free(f);
	}
	*fl = NULL;
}

FileList loadFileList(const char* file)
{

	FILE* f = fopen(file, "r");
	if (f == NULL) return NULL;

	char* s = malloc(sizeof(char) * 128);
	FileList fl = NULL;
	for (; fscanf(f, "%[^:]s", &s[0]) != EOF;)
	{
		addFileTail(&fl, s);
		int idver, time;
		fscanf(f, ":");
		while (fscanf(f, "%d,%dl", &idver, &time) != EOF)
		{
			time_t timestamp = time;
			addVersion(&fl, s, idver, time);
			if (fgetc(f) == '\n') break;
		}
	}
	fclose(f);
	return fl;
}

int saveFileList(FileList f, const char* file)
{
	if (f == NULL) return 1;
	FILE* FTW = fopen(file, "w");

	for (File* fi = f; fi != NULL; fi = fi->NextFile)
	{
		fprintf(FTW, "%s:", fi->FileName);
		for (Version* v = fi->VersionListHead; v != NULL; v = v->NextVersion)
		{
			fprintf(FTW, "%d,%ld", v->ID, (long)v->Timestamp);
			if (v->NextVersion != NULL)
				fprintf(FTW, ";");
		}
		if (fi->NextFile != NULL)
			fprintf(FTW, "\n");
	}
	fclose(FTW);
	return 0;
}

