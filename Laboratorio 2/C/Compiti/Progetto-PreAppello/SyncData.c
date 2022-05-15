#include "util.c"
#include "SyncCounter.c"

typedef struct SyncData
{
    SyncCounter_t *shm_SyncCounter;
    pthread_cond_t ServerOpened;
    pthread_mutex_t mut;
    int ServerInit;
} SyncData_t;

static inline void LockInit(SyncData_t *sd) { LOCK(&sd->mut); }
static inline void UnlockInit(SyncData_t *sd) { UNLOCK(&sd->mut); }
static inline void WaitServerOpened(SyncData_t *sd) { WAIT(&sd->ServerOpened, &sd->mut); }
static inline void BcastServerOpened(SyncData_t *sd) { BCAST(&sd->ServerOpened); }

void DeleteSyncData(SyncData_t *sd)
{

    if (!sd)
        return;
    int myerrno = errno;
    if (&sd->mut)
        pthread_mutex_destroy(&sd->mut);
    if (&sd->ServerOpened)
        pthread_cond_destroy(&sd->ServerOpened);
    if (sd->shm_SyncCounter)
    {
        munmap(sd->shm_SyncCounter, sizeof(SyncCounter_t));
        // DeleteSyncCounter(sd->shm_SyncCounter);
    }
    // free(sd);
    munmap(sd, sizeof(SyncData_t));
    errno = myerrno;
}

SyncData_t *InitSincData()
{

    SyncData_t *sd = (SyncData_t *)create_anony_shared_memory(sizeof(SyncData_t));

    sd->shm_SyncCounter = (SyncCounter_t *)create_anony_shared_memory(sizeof(SyncCounter_t));

    SyncCounter_t *SyncToCopy = InitSyncCounter();
    *sd->shm_SyncCounter = *SyncToCopy;
    free(SyncToCopy);

    sd->ServerInit = 0;
    if (!sd)
    {
        perror("malloc");
        return NULL;
    }

    pthread_mutexattr_t attrmutex;
    if (pthread_mutexattr_init(&attrmutex))
    {
        perror("pthread_mutexattr_init");
        goto error;
    }
    pthread_mutexattr_setpshared(&attrmutex, PTHREAD_PROCESS_SHARED);

    if (pthread_mutex_init(&sd->mut, &attrmutex) != 0)
    {
        perror("pthread_mutex_init");
        goto error;
    }
    pthread_condattr_t attrcond;
    if (pthread_condattr_init(&attrcond))
    {
        perror("thread_condattr_init");
        goto error;
    }
    pthread_condattr_setpshared(&attrcond, PTHREAD_PROCESS_SHARED);

    if (pthread_cond_init(&sd->ServerOpened, &attrcond) != 0)
    {
        perror("pthread_cond_init OnAzeration");
        goto error;
    }

    return sd;
error:
    if (&sd->mut)
        pthread_mutexattr_destroy(&attrmutex);
    if (&sd->ServerOpened)
        pthread_cond_destroy(&sd->ServerOpened);

    DeleteSyncData(sd);
    return NULL;
}

void OpenServer(SyncData_t *sd)
{
    LockInit(sd);
    sd->ServerInit = 1;
    BcastServerOpened(sd);
    UnlockInit(sd);
}
void WaitOnServerOpened(SyncData_t *sd)
{
    LockInit(sd);
    if (sd->ServerInit == 0)
        while (sd->ServerInit == 0)
        {
            DEBUG_COMMAND(printf("Waiting on serve Init %d\n", sd->ServerInit));
            WaitServerOpened(sd);
        }
    else
        DEBUG_COMMAND(printf("SKIP on serve Init %d\n", sd->ServerInit));
    UnlockInit(sd);
}
