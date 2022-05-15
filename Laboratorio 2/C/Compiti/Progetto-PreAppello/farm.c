#define DEBUG 0
#include "MyLib.c"
#include "util.c"
#include "boundedqueue.h"
#include "FileCheckSum.c"
#include "SyncData.c"
#define SOCKETNAME "./farm.sck"

SyncData_t *syncData;

void SetSignals_client();
void SetSignals_server();
void FillTaskQueue(int argc, const char *argv[], int delay);
void AT_exitCallBack_client();
void AT_exitCallBack_server();

void run_server(struct sockaddr_un sa);
void *WorkerFunction(void *arg);
BQueue_t *MainToWorker;

struct sockaddr_un sockAddr;

int main(int argc, const char *argv[])
{

    int Nwork = 4;
    int QueueDimension = 8;
    int delay = 0;
    for (int i = 1; i < argc; i++)
    {
        int par = 0;
        if (strcmp(argv[i], "-n") == 0)
        {
            Nwork = atoi(argv[i + 1]);
            par++;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            par++;
            delay = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            par++;
            QueueDimension = atoi(argv[i + 1]);
        }

        if (par == 1)
        {
            i++;
            continue;
        }
    }

    SetSignals_client();

    syncData = InitSincData();

    strcpy(sockAddr.sun_path, SOCKETNAME);
    sockAddr.sun_family = AF_UNIX;

    pid_t pid;
    switch (pid = fork())
    {
        MC_FORK_ERROR_SW();

    case 0:
        MC_SYSCALL_M1(atexit(AT_exitCallBack_server), "atexit error");
        DEBUG_COMMAND(PrintDeb("Start-Server"));
        // Conllecor
        SetSignals_server();
        run_server(sockAddr);

        break;
    default:
        // MainWorker
        MC_SYSCALL_M1(atexit(AT_exitCallBack_client), "atexit error");
        MainToWorker = initBQueue(QueueDimension);

        pthread_t Worker[Nwork];

        for (int i = 0; i < Nwork; i++)
            pthread_create(&Worker[i], NULL, WorkerFunction, (void *)&sockAddr);

        DEBUG_COMMAND(PrintDeb("Pre-TaskQueue"));
        FillTaskQueue(argc, argv, delay);
        DEBUG_COMMAND(PrintDeb("Post-TaskQueue"));
        for (int i = 0; i < Nwork; i++)
            pthread_join(Worker[i], NULL);
        deleteBQueue(MainToWorker, NULL);
        DEBUG_COMMAND(PrintDeb("JOIN"));
        waitpid(pid, NULL, 0);
        DEBUG_COMMAND(PrintDeb("WAIT"));
    }

    return 0;
}

void *WorkerFunction(void *arg)
{

    // GESTIONE SOKET
    struct sockaddr_un sa = *(struct sockaddr_un *)arg;

    int fd_skt;

    MC_SYSCALL_M1(fd_skt = socket(AF_UNIX, SOCK_STREAM, 0), "Soket Client Error");

    WaitOnServerOpened(syncData);

    while (connect(fd_skt, (struct sockaddr *)&sa, sizeof(sa)) == -1)
    {
        switch (errno)
        {
        case 111: /* connection refused*/
            sleep(1);
            DEBUG_COMMAND(PrintDeb("WAITING FOR SOKET"));
            break;
        case 2: /* socket not found */
            return 0;
            break;

        default:
            perror("Exit connecte");
            exit(EXIT_FAILURE);
            break;
        }
    }

    while (1)
    {
        // FILE DA LEGGERE DA MAIN
        char *fileName = (char *)pop(MainToWorker);

        DEBUG_COMMAND(printf("--------%s--------\n", fileName));

        if (strcmp(fileName, "NULL") == 0)
        {
            push(MainToWorker, "NULL");
            DEBUG_COMMAND(PrintDeb("CLIENT-CLOSE"));
            close(fd_skt);
            return 0;
        }

        // LETTURA FILE
        FILE *fp;

        fp = fopen(fileName, "r");

        if (fp == NULL)
        {
            PrintDeb("ERRORE OPEN FILE");
            close(fd_skt);
            pthread_exit((void *)2);
        }

        int ArraDimension = 2500, ReadStep = ArraDimension / 2;
        long *array = calloc(ArraDimension, sizeof(long));

        int NLongRead = 0;
        size_t longRead = 0;
        while ((longRead = fread(&array[NLongRead], sizeof(long), ReadStep, fp)) != 0)
        {
            NLongRead += longRead;
            if (NLongRead + ReadStep > ArraDimension)
            {
                ArraDimension = ArraDimension + ReadStep * 3;
                array = realloc(array, ArraDimension * sizeof(long));
            }
        };
        fclose(fp);

        array = realloc(array, NLongRead * sizeof(long));

        // ELABORAZIONE FILE

        long sum = 0;
        for (int i = 0; i < NLongRead; i++)
            sum += i * array[i];
        free(array);

        // SCRIVERE SU SOKET

        FileCheckSum *fcs = InitFileCheckSum();

        fcs->CheckSum = sum;
        strcpy(fcs->FileName, fileName);
        MC_SYSCALL_M1(write(fd_skt, fcs, sizeof(FileCheckSum)), "Write error");

        free(fcs);
    }
}

void run_server(struct sockaddr_un sa)
{
    int server_skt = StartUpLocalServer(sa), fd_num = 0;

    OpenServer(syncData);

    DEBUG_COMMAND(PrintDeb("SERVER-StartUP"));

    if (server_skt > fd_num)
        fd_num = server_skt;

    fd_set current_socket, check_socket, Server_socket;

    FD_ZERO(&current_socket);
    FD_ZERO(&Server_socket);
    FD_SET(server_skt, &current_socket);
    FD_SET(server_skt, &Server_socket);
    DEBUG_COMMAND(PrintDeb("SERVER-FD_SET"));
    while (1)
    {
        check_socket = current_socket;

        MC_SYSCALL_M1(select(fd_num + 1, &check_socket, NULL, NULL, NULL), "Select error")
        DEBUG_COMMAND(PrintDeb("SERVER-SELECT"));
        for (int i = 0; i <= fd_num; i++)
        {
            if (FD_ISSET(i, &check_socket))
            {
                if (i == server_skt)
                {
                    int client_socket;
                    MC_SYSCALL_M1(client_socket = accept(server_skt, NULL, 0), "Accept error");
                    FD_SET(client_socket, &current_socket);
                    if (client_socket > fd_num)
                        fd_num = client_socket;
                }
                else
                {

                    FileCheckSum *buff = malloc(sizeof(FileCheckSum) * 10);
                    int FCSread;

                    MC_SYSCALL_M1(FCSread = read(i, buff, sizeof(FileCheckSum) * 10), "read Error");
                    FCSread = FCSread / sizeof(FileCheckSum);
                    if (FCSread != 0)
                    {
                        for (int j = 0; j < FCSread; j++)
                        {
                            printf("%ld %s \n", buff[j].CheckSum, buff[j].FileName);
                            fflush(NULL);
                            DEBUG_COMMAND(PrintDeb("SERVER: Want to decrese"));
                            DecreseSyncCounter((SyncCounter_t *)syncData->shm_SyncCounter);
                        }
                    }
                    else
                    {
                        close(i);
                        FD_CLR(i, &current_socket);

                        DEBUG_COMMAND(printf("Server bit: %s | %s :Current bit\n", FD_bitDebug(Server_socket), FD_bitDebug(current_socket)));

                        if (FD_bitCompare(Server_socket, current_socket))
                        {
                            DEBUG_COMMAND(PrintDeb("COLLECTOR END"));
                            close(server_skt);
                            free(buff);
                            exit(1);
                        }
                    }

                    free(buff);
                }
            }
        }
    }
}

void FillTaskQueue(int argc, const char *argv[], int delay)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-q") == 0)
        {
            i++;
            continue;
        }
        if (isRegular(argv[i], NULL) == 1)
        {
            push(MainToWorker, (void *)argv[i]);
            DEBUG_COMMAND(PrintDeb("MAIN:Want to Increse"));
            IncreseSyncCounter((SyncCounter_t *)syncData->shm_SyncCounter);
        }
        DEBUG_COMMAND(printf("Sleaping %dms... \n", delay));
        DEBUG_COMMAND(fflush(NULL));
        MC_SYSCALL_M1(usleep(delay * 1000), "USLEEP ");
    }
    push(MainToWorker, "NULL");
}

// SIGNAL HANDLER
void SafeExit()
{
    push(MainToWorker, "NULL");

    DEBUG_COMMAND(PrintDeb("free syncData"));
    WaitUntilAzeration((SyncCounter_t *)syncData->shm_SyncCounter);
    DEBUG_COMMAND(PrintDeb("Exit By Sinals"));
    exit(EXIT_SUCCESS);
}

void AT_exitCallBack_client()
{
    DEBUG_COMMAND(printf("\nSTART QUIT CLIENT\n"));
    DEBUG_COMMAND(fflush(NULL));
    unlink(SOCKETNAME);
    DeleteSyncData(syncData);
    DEBUG_COMMAND(printf("\nCLIENT CLOSED\n"));
}
void AT_exitCallBack_server()
{
    DEBUG_COMMAND(printf("\nSTART QUIT SERVER\n"));
    DEBUG_COMMAND(fflush(NULL));
    unlink(SOCKETNAME);
    DeleteSyncData(syncData);
    DEBUG_COMMAND(printf("\nSERVER CLOSED\n"));
}

void SIGHUP_SoftExit()
{
    SafeExit();
}

void SIGINT_SoftSoket()
{
    SafeExit();
}

void SIGTERM_SoftExit()
{
    SafeExit();
}

void SIGQUIT_SoftExit()
{
    SafeExit();
}

void SIGPIPE_Server()
{
    printf("Socket shutdown or no more connected");
}

void SIGPIPE_Client()
{
    printf("Socket shutdown");
}

void SetSignals_client()
{
    SET_SIGNAL_HANDLER(s1, SIGHUP, SIGHUP_SoftExit);
    SET_SIGNAL_HANDLER(s2, SIGINT, SIGINT_SoftSoket);
    SET_SIGNAL_HANDLER(s3, SIGQUIT, SIGQUIT_SoftExit);
    SET_SIGNAL_HANDLER(s4, SIGTERM, SIGTERM_SoftExit);
    SET_SIGNAL_HANDLER(s5, SIGPIPE, SIGPIPE_Client);
}

void SetSignals_server()
{
    signal(SIGHUP, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    SET_SIGNAL_HANDLER(s, SIGPIPE, SIGPIPE_Server);
}

// SIGNAL HANDLER
