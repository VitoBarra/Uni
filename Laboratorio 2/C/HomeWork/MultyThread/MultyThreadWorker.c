#include "../MyLib.c"
#include "../util.c"
#include "../DataStructure/boundedqueue.c"

typedef struct ColonSum
{
    int col1;
    int col2;
} ColonSum_t;

void *WorkerFunction(void *arg);
ColonSum_t *InitColonSum();
BQueue_t *MainToWorker;
BQueue_t *Result;

int main(int argc, const char *argv[])
{
    if (argc < 3)
        return -1;

    MainToWorker = initBQueue(25);
    Result = initBQueue(25);

    int Nwork = atoi(argv[1]);

    pthread_t Worker[Nwork];

    for (int i = 0; i < Nwork; i++)
    {
        pthread_create(&Worker[i], NULL, WorkerFunction, NULL);
    }

    for (int i = 2; i < argc; i++)
    {
        isRegular(argv[i], NULL);
        push(MainToWorker, (void *)argv[i]);
    }
    push(MainToWorker, "NULL");

    for (int i = 0; i < Nwork; i++)
    {
        printf("join\n");
        pthread_join(Worker[i], NULL);
    }

    ColonSum_t *cs = InitColonSum();

    for (int i = 2; i < argc; i++)
    {
        ColonSum_t *temp = (ColonSum_t *)pop(Result);

        cs->col1 += temp->col1;
        cs->col2 += temp->col2;
    }

    printf("valori:%d,%d\n", cs->col1, cs->col2);

    return 0;
}

ColonSum_t *InitColonSum()
{
    ColonSum_t *cs = calloc(sizeof(ColonSum_t), 1);
    cs->col1 = 0;
    cs->col2 = 0;
    return cs;
}

void *WorkerFunction(void *arg)
{

    int c = 0;

    printf("--------%ld--------\n", (long)pthread_self());
    while (1)
    {

        char *fileName = (char *)pop(MainToWorker);

        printf("--------%s--------\n", fileName);

        if (strcmp(fileName, "NULL") == 0)
        {

            push(MainToWorker, "NULL");
            // pthread_exit((void *)0);
            printf("------------FINE----------\n");
            return 0;
        }

        FILE *fp;
        char line[128];

        fp = fopen(fileName, "r");

        if (fp == NULL)
            pthread_exit((void *)2);

        ColonSum_t *cs = InitColonSum();
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            c++;
            int a1 = atoi(strtok(line, ","));
            int a2 = atoi(strtok(NULL, ","));

            cs->col1 += a1;
            cs->col2 += a2;
            printf("%s(%d):%d,%d | %d,%d\n", fileName, c, a1, a2, cs->col1, cs->col2);
        }

        push(Result, cs);

        fclose(fp);
    }
}