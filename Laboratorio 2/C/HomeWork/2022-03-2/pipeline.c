#include "../MyLib.c"

int main(int argc, char *const argv[])
{
    int pid[3];

    MC_CREATE_PIPE(p1);
    MC_CREATE_PIPE(p2);

    switch (pid[0] = fork())
    {
        MC_FORK_ERROR_SW();

    case 0:
        MC_SYSCALL_M1(close(p1[0]),"close error");
        MC_SYSCALL_M1(close(p2[0]),"close error");
        MC_SYSCALL_M1(close(p2[1]),"close error");

        MC_SYSCALL_M1(dup2(p1[1], STDOUT_FILENO),"Dup2 Error");
        MC_SYSCALL_M1(close(p1[1]),"close error");
        MC_SYSCALL_M1(execlp("cat", "cat", "/etc/passwd", NULL), "error in execlp");
        exit(0);
        break;
    }

    switch (pid[1] = fork())
    {
        MC_FORK_ERROR_SW();

    case 0:
        close(p1[1]);
        close(p2[0]);

        dup2(p1[0], STDIN_FILENO);
        dup2(p2[1], STDOUT_FILENO);
        close(p1[0]);
        close(p2[1]);

        MC_SYSCALL_M1(execlp("cut", "cut", "-d", ":", "-f", "1", NULL), "error in execlp");

        exit(0);
    }
    switch (pid[2] = fork())
    {
        MC_FORK_ERROR_SW();

    case 0:
        MC_SYSCALL_M1(close(p1[0]),"close error");
        MC_SYSCALL_M1(close(p1[1]),"close error");
        MC_SYSCALL_M1(close(p2[1]),"close error");
        MC_SYSCALL_M1(dup2(p2[0], STDIN_FILENO),"dup2 Error");
        MC_SYSCALL_M1(close(p2[0]),"close error");

        MC_SYSCALL_M1(execlp("sort", "sort", NULL), "error in execlp");
        exit(0);
        break;
    }
        MC_SYSCALL_M1(close(p1[0]),"close error");
        MC_SYSCALL_M1(close(p2[0]),"close error");
        MC_SYSCALL_M1(close(p2[1]),"close error");
        MC_SYSCALL_M1(close(p1[1]),"close error");

    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);
    waitpid(pid[2], NULL, 0);
    return 0;
}