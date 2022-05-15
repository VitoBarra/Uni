#include "merge.h"          //optional
#include "unboundedqueue.h" //optional
#include "util.h"
// #include "VitoBarra_616830_MyLib.c"
#include <dirent.h>

void *WorkerReadArray(void *arg);
int compare(const void *a, const void *b);
int N;
Queue_t *MainToWorkerDirectory;
Queue_t *Result;

pthread_barrier_t barrier;

void printArra(long *a, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%ld,", a[i]);
    }

    printf("\n");
}

int main(int argc, const char *argv[])
{

    if (argc != 4)
        return -1;

    MainToWorkerDirectory = initQueue();
    Result = initQueue();

    int Nwork = atoi(argv[1]);
    N = atoi(argv[2]);
    pthread_t Worker[Nwork];

    for (int i = 0; i < Nwork; i++)
        pthread_create(&Worker[i], NULL, WorkerReadArray, NULL);

    int ArrayN = 0;
    DIR *dir;

    if ((dir = opendir(argv[3])) == NULL)
        perror("opendir() error");
    else
    {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                char s1[64];
                strcpy(s1, argv[3]);
                char *s3 = calloc(sizeof(char), 126);
                strcpy(s3, strcat(strcat(s1, "/"), entry->d_name));

                push(MainToWorkerDirectory, s3);
                ArrayN++;
            }
        closedir(dir);
    }

    push(MainToWorkerDirectory, "NULL");

    for (int i = 0; i < Nwork; i++)
        pthread_join(Worker[i], NULL);

    long *FinalArr = pop(Result);
    printf("--F--\n");
    printArra(FinalArr, N);

    for (int i = 1; i < ArrayN; i++)
    {
        long *e = pop(Result);
        printf("--e--\n");
        printArra(e, N);

        FinalArr = mergeAndFree(FinalArr, i * N, e, N);
        printf("--F%d--\n", i);
        printArra(FinalArr, (i + 1) * N);
    }

    long sum = 0;
    for (int i = 0; i < ArrayN * N; i++)
    {
        sum += i * FinalArr[i];
    }

    printf("%ld\n", sum);
}
int compare(const void *a, const void *b)
{
    long int_a = *((long *)a);
    long int_b = *((long *)b);

    if (int_a == int_b)
        return 0;
    else if (int_a < int_b)
        return -1;
    else
        return 1;
}

void *WorkerReadArray(void *arg)
{
    printf("--------%ld--------\n", (long)pthread_self());
    while (1)
    {

        char *fileName = (char *)pop(MainToWorkerDirectory);

        printf("--------%s--------\n", fileName);

        if (strcmp(fileName, "NULL") == 0)
        {

            push(MainToWorkerDirectory, "NULL");
            printf("------------FINE----------\n");
            return 0;
        }

        FILE *fp;

        fp = fopen(fileName, "r");

        if (fp == NULL)
        {
            printf("------------ERRORE----------\n");
            pthread_exit((void *)2);
        }

        long *array = calloc(sizeof(long), N);

        fread(array, sizeof(long), N, fp);

        qsort(array, N, sizeof(long), compare);

        push(Result, array);

        fclose(fp);
    }
}
