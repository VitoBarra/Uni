#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <limits.h>

#include <stdio.h>
#include <stdlib.h>

#define EXIT_FAILURE 1

#define ec_meno1(s, m)      \
    if ((s) == -1)          \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    }

#define ec_null(s, m)       \
    if ((s) == NULL)        \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    }

#define ec_meno1_c(s, m, c) \
    if ((s) == -1)          \
    {                       \
        perror(m);          \
        c;                  \
    }

#define writeOnStdOut(s) \
    ec_meno1(write(1, s, strlen(s)), "Write Error");

int CompereTimespec(struct timespec a, struct timespec b)
{

    if (a.tv_sec == b.tv_sec)
    {
        if (a.tv_nsec == b.tv_nsec)
            return 0;
        else if (a.tv_nsec > b.tv_nsec)
            return 1;
        else
            return -1;
    }
    else if (a.tv_sec > b.tv_sec)
        return 1;
    else
        return -1;
}

int GetCurrentFreeSpace(char* dir, int size, char** OlderFile)
{
    DIR* Directory;
    ec_null(Directory = opendir(dir), "OpenDir error");

    ec_meno1(chdir(dir), "chdir error");

    int CurrentSize = 0;
    struct timespec OlderTime;
    OlderTime.tv_sec = LONG_MAX;
    OlderTime.tv_nsec = LONG_MAX;

    struct dirent* file;
    while ((errno = 0, file = readdir(Directory)) != NULL)
    {
        struct stat st;
        ec_meno1(stat(file->d_name, &st), "fallimento stat");

        if (S_ISDIR(st.st_mode))
            continue;

        if (CompereTimespec(OlderTime, st.st_atim) == 1)
        {
            *OlderFile = file->d_name;
            OlderTime = st.st_atim;
        }
        CurrentSize += st.st_size;

        printf("dimension %s: %ld   OLDERTIME:%ld.%.9ld,OLDERFILE:%s    Cur:%d \n",
            file->d_name, st.st_size, OlderTime.tv_sec, OlderTime.tv_nsec, *OlderFile, CurrentSize);
    }

    if (errno != 0)
        exit(EXIT_FAILURE);

    ec_meno1(chdir(".."), "Error chdir");
    ec_meno1(closedir(Directory), "closedir error");

    return size - CurrentSize;
}

int main(int argc, char* argv[])
{

    if (argc != 9)
    {
        writeOnStdOut("To few argument, shuld be -d [directory] -s [number] -f [number] - n [number]\n");
        return EXIT_FAILURE;
    }

    char* dir;
    long size;
    int maxnum;
    float warning_factor;
    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "-d") == 0)
            dir = argv[i + 1];
        else if (strcmp(argv[i], "-s") == 0)
            size = atoi(argv[i + 1]) * 1024 * 1024;
        else if (strcmp(argv[i], "-f") == 0)
            warning_factor = atof(argv[i + 1]);
        else if (strcmp(argv[i], "-n") == 0)
            maxnum = atoi(argv[i + 1]);
        else
        {
            writeOnStdOut("Paramether number right but wrong usage of flag\n");
            return EXIT_FAILURE;
        }
    }

    float Warning = size * warning_factor;

    char* OlderFile = "";

    for (int i = 0, FreeSpace = GetCurrentFreeSpace(dir, size, &OlderFile);
        FreeSpace < Warning && (maxnum == 0 || i < maxnum);
        i++, FreeSpace = GetCurrentFreeSpace(dir, size, &OlderFile))
    {
        ec_meno1(chdir(dir), "chdir error");
        //  printf("---------(%d < %f && (%d == 0 || %d < %d))-------\n", FreeSpace, Warning, maxnum, i, maxnum);
        //  printf("%d,%s\n", FreeSpace, OlderFile);
        remove(OlderFile);
        ec_meno1(chdir(".."), "Error chdir");
    }
}
