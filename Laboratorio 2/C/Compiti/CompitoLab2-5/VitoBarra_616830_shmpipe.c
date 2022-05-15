#include "VitoBarra_616830_MyLib.c"
#include <util.h>
#include <stdlib.h>
#define MAX_FILE_SIZE 3 * 1024 * 1024
#define SHM_NAME "SHM_VITO"

int Worker(int rToWork[], int WorkerToWriter[]);
int Write(int WorkerToWriter[]);

int main(int argc, char *const argv[])
{
    int pid[2];
    void *shm;

    MC_CREATE_PIPE(readerToWorker);
    MC_CREATE_PIPE(workerToWriter);
    MC_SYSCALL_M1((int)(shm = create_shared_memory(MAX_FILE_SIZE, SHM_NAME)), "SHM");
    MC_CREATE_NAMED_SEM(semfd, "/RTOW", 0);

    switch (pid[0] = fork())
    {
        MC_FORK_ERROR_SW();

    case 0:
        exit(Worker(readerToWorker, workerToWriter));
        break;
    }

    switch (pid[1] = fork())
    {
        MC_FORK_ERROR_SW();
    case 0:
        exit(Write(workerToWriter));
        break;
    }

    for (int i = 1; i < argc; i++)
    {
        size_t *s;
        int regular = isRegular(argv[i], s) == 1;
        if (s > MAX_FILE_SIZE)
            MC_WRITEONSTD("File troppo grande");
        MC_SYSCALL_M1(regular, "Isregular Error");

        if (regular == 0)
            continue;
        int fd;
        MC_SYSCALL_M1(fd = open(argv[i], O_RDWR, 0666), "Open Error");
        sem_wait(semfd);
        MC_SYSCALL_M1(readerToWorker[1] = read(fd, shm, MAX_FILE_SIZE), "read");
        sem_post(semfd);
    }

    readerToWorker[1] = -1;
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);

    MC_SYSCALL_M1(close(readerToWorker[0]), "close");
    MC_SYSCALL_M1(close(readerToWorker[1]), "close");
    MC_SYSCALL_M1(close(workerToWriter[0]), "close");
    MC_SYSCALL_M1(close(workerToWriter[1]), "close");
    return 0;
}

int Worker(int rToWork[], int WorkerToWriter[])
{
    MC_SYSCALL_M1(close(rToWork[1]), "WORKER close PIPE");
    MC_SYSCALL_M1(close(WorkerToWriter[0]), "WORKER close PIPE");
    while (1)
    {
        int dimBuffer;
        long numberBuffer[1024];
        read(rToWork[0], dimBuffer, MAX_FILE_SIZE);
        void *shm;
        MC_SYSCALL_M1(shm = create_shared_memory(MAX_FILE_SIZE, SHM_NAME), "SHM");
        if (dimBuffer > 0)
        {

            int Nfloat = read(shm, numberBuffer, dimBuffer) / sizeof(long);
            int result = 0;
            for (int i = 0; i < Nfloat - 1; i++)
                result = i * numberBuffer[i];

            WorkerToWriter[1] = result;
        }
        else if (dimBuffer == -1)
        {
            WorkerToWriter[1] = -1;
            MC_SYSCALL_M1(close(rToWork[0]), "WORKER close PIPE");
            MC_SYSCALL_M1(close(WorkerToWriter[1]), "close");
            MC_SYSCALL_M1(shm_unlink(shm), "SHM_UNLINK error");
            return 0;
        }
    }
}

int Write(int WorkerToWriter[])
{
    MC_SYSCALL_M1(close(WorkerToWriter[1]), "WORKER close PIPE");
    MC_CREATE_NAMED_SEM(semfd, "/RTOW", 0);
    while (1)
    {
        char tmp[255];
        long result;
        sem_wait(semfd);
        read(WorkerToWriter[0], result, MAX_FILE_SIZE);

        if (result == -1)
        {
            MC_SYSCALL_M1(sem_unlink(semfd), "SEM_UNLINK error");
            MC_SYSCALL_M1(close(WorkerToWriter[0]), "close");
            return 0;
        }

        sprintf(tmp, "%d", result);
        MC_WRITEONSTD(tmp);

        sem_post(semfd);
    }
}