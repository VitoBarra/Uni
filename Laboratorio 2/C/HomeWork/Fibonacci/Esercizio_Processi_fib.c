#include "../MyLib.c"

int main(int argc, char const *argv[])
{
    int cal = atoi(argv[1]);
    int *shm = (int *)create_anony_shared_memory(sizeof(int));
    *shm = 1;
    int depth = 0;

    if (cal == 1 || cal == 0)
    {
        printf("fibo alla posizione %d alla profondita %d con %d processi attivi: %d\n", cal, depth, *((int *)shm), cal);
        return cal;
    }

    while (cal > 0)
    {
        pid_t pid[2];

        switch (pid[0] = fork())
        {
        MC_FORK_ERROR_SW();

        case 0:
            depth++;
            cal -= 1;
            (*shm)++;
            break;

        default:
            switch (pid[1] = fork())
            {
                MC_FORK_ERROR_SW();

            case 0:
                cal -= 2;
                depth++;
                (*shm)++;
                break;
            }
            break;
        }

        if (cal == 1 || cal == 0)
            return cal;

        int stat[2];
        waitpid(pid[0], &(stat[0]), 0);
        waitpid(pid[1], &(stat[1]), 0);

        if (WIFEXITED(stat[0]) && WIFEXITED(stat[1]))
        {
            printf("fibo alla posizione %d alla profondita %d con %d processi attivi: %d\n", cal, depth, *((int *)shm), WEXITSTATUS(stat[0]) + WEXITSTATUS(stat[1]));
            (*shm)--;
            return WEXITSTATUS(stat[0]) + WEXITSTATUS(stat[1]);
        }
    }

    return 0;
}
