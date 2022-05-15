#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <signal.h>
#include <pthread.h>

#define MC_SYSCALL_NULL(s, m) \
    if ((s) == NULL)          \
    {                         \
        perror(m);            \
        exit(EXIT_FAILURE);   \
    }

#define MC_SYSCALL_M1(s, m) \
    if ((s) == -1)          \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    }

#define MC_MAKEFIFO_COMAND(name, c)        \
    if (mkfifo(name, 0666) == -1)          \
    {                                      \
        if (errno != EEXIST)               \
        {                                  \
            perror("FIFO Creation Error"); \
            c                              \
        }                                  \
    }

#define WRITE_ON_STDOUT(s) \
    MC_SYSCALL_M1(write(STDOUT_FILENO, s, strlen(s)), "Write Error");

#define READ_FROM_STDOUT(bname, bsize) \
    char bname[bsize];                 \
    MC_SYSCALL_M1(read(STDIN_FILENO, bname, bsize * sizeof(char)), "Write Error");

#define MC_WAITALLFORK()                       \
    while (wait(NULL) != 1 || errno != ECHILD) \
        ;

#define MC_FORK_ERROR_SW()     \
    case -1:                   \
        perror("errore fork"); \
        exit(EXIT_FAILURE);    \
        break;
#define MC_CREATE_PIPE(name) \
    int name[2];             \
    MC_SYSCALL_M1(pipe(name), "anony pipe  Creation error");

void *create_anony_shared_memory(size_t size)
{
    // Our memory buffer will be readable and writable:
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | /*MAP_ANONYMOUS*/ 0x20;

    return mmap(NULL, size, protection, visibility, -1, 0);
}

void *create_shared_memory(size_t size, char *VirtualFilePath)
{
    int fd = shm_open(VirtualFilePath, O_CREAT | O_TRUNC | O_RDWR, 0600);
    int protection = PROT_READ | PROT_WRITE;

    int visibility = MAP_SHARED;

    return mmap(NULL, size, protection, visibility, fd, 0);
}

int create_named_pipe_write(char *VirtualFilePath)
{
    MC_MAKEFIFO_COMAND(VirtualFilePath, return 1;)

    return open(VirtualFilePath, O_RDWR);
}

sem_t *create_named_semaphore(char *VirtualFilePath)
{
    return sem_open(VirtualFilePath, O_CREAT | O_RDWR, 0600);
}

#define MC_CREATE_SEM(sem_name, init, isProcessShered)         \
    sem_t *sem_name = mmap(NULL, sizeof(sem_t),                \
                           PROT_READ | PROT_WRITE,             \
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0); \
    if (sem_name == MAP_FAILED)                                \
    {                                                          \
        perror("map Error in sem creatiion");                  \
        exit(1);                                               \
    }                                                          \
    MC_SYSCALL_M1(sem_init(sem_name, isProcessShered, init), "init fail");

#define ftos(s, num) \
    char s[20];      \
    sprintf(ss, "%f", num);

#define itos(s, num) \
    char s[20];      \
    sprintf(s, "%d", num);

#define SET_SIGNAL_HANDLER(s, sig, SigAction) \
    struct sigaction s;                       \
    memset(&s, 0, sizeof(s));                 \
    s.sa_handler = SigAction;                 \
                                              \
    MC_SYSCALL_M1(sigaction(sig, &s, NULL), "sigaction error");
