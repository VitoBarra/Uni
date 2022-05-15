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
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <sys/types.h>

#define UNIX_PATH_MAX 108

#define DEBUG_COMMAND(s) \
    if (DEBUG)           \
        s;

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

    void *a;
    if ((a = mmap(NULL, size, protection, visibility, -1, 0)) == MAP_FAILED)
    {
        perror("Mmap Error");
        exit(EXIT_FAILURE);
    };
    return a;
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

int StartUpLocalServer(struct sockaddr_un skAddh)
{
    int server_skt;
    MC_SYSCALL_M1(server_skt = socket(AF_UNIX, SOCK_STREAM, 0), "socket Error");
    MC_SYSCALL_M1(bind(server_skt, (struct sockaddr *)&skAddh, sizeof(skAddh)), "bind error");
    MC_SYSCALL_M1(listen(server_skt, SOMAXCONN), "listen error");

    return server_skt;
}

void PrintDeb(const char str[])
{
    printf("--------------------%s---------------------\n", str);
    fflush(NULL);
}

char *FD_bitDebug(fd_set fd_s)
{
    char *str = (char *)calloc(sizeof(char), 15);
    for (size_t i = 0; i < 16; i++)
        sprintf(str + i, "%ld", fd_s.__fds_bits[i]);
    return str;
}

int FD_bitCompare(fd_set fd_s1, fd_set fd_s2)
{
    int uguali = 1;
    for (size_t i = 0; i < 16; i++)
    {
        if (fd_s1.__fds_bits[i] != fd_s2.__fds_bits[i])
        {
            uguali = 0;
            break;
        }
    }
    return uguali;
}