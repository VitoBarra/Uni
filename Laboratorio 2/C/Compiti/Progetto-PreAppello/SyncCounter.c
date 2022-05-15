#include "util.c"

typedef struct SyncCounter
{
    pthread_cond_t OnAzeration;
    pthread_mutex_t mut;
    int counter;
} SyncCounter_t;

static inline void LockCounter(SyncCounter_t *ssc) { LOCK(&ssc->mut); }
static inline void UnlockCounter(SyncCounter_t *ssc) { UNLOCK(&ssc->mut); }
static inline void WaitToAzzeration(SyncCounter_t *ssc) { WAIT(&ssc->OnAzeration, &ssc->mut); }
static inline void SignalAzeration(SyncCounter_t *ssc) { SIGNAL(&ssc->OnAzeration); }

SyncCounter_t *InitSyncCounter()
{
    SyncCounter_t *ssc = malloc(sizeof(SyncCounter_t));

    if (!ssc)
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

    if (pthread_mutex_init(&ssc->mut, &attrmutex) != 0)
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

    if (pthread_cond_init(&ssc->OnAzeration, &attrcond) != 0)
    {
        perror("pthread_cond_init OnAzeration");
        goto error;
    }

    ssc->counter = 0;

    return ssc;
error:
    if (!ssc)
        return NULL;
    int myerrno = errno;
    if (&ssc->mut)
    {
        pthread_mutex_destroy(&ssc->mut);
        pthread_mutexattr_destroy(&attrmutex);
    }
    if (&ssc->OnAzeration)
    {
        pthread_condattr_destroy(&attrcond);
        pthread_cond_destroy(&ssc->OnAzeration);
    }
    free(ssc);
    errno = myerrno;
    return NULL;
}

void DeleteSyncCounter(SyncCounter_t *ssc)
{
    if (!ssc)
        return;
    if (&ssc->mut)
        pthread_mutex_destroy(&ssc->mut);
    if (&ssc->OnAzeration)
        pthread_cond_destroy(&ssc->OnAzeration);
    free(ssc);
}

void IncreseSyncCounter(SyncCounter_t *ssc)
{
    LockCounter(ssc);

    ssc->counter++;
    DEBUG_COMMAND(printf("counter inc:%d\n", ssc->counter));
    fflush(NULL);

    UnlockCounter(ssc);
}

void DecreseSyncCounter(SyncCounter_t *ssc)
{
    LockCounter(ssc);
    ssc->counter--;
    DEBUG_COMMAND(printf("counter dec:%d\n", ssc->counter));
    if (ssc->counter <= 0)
        SignalAzeration(ssc);

    UnlockCounter(ssc);
}

void WaitUntilAzeration(SyncCounter_t *ssc)
{

    LockCounter(ssc);
    while (ssc->counter > 0)
    {
        DEBUG_COMMAND(printf("Wait %d \n", ssc->counter));
        WaitToAzzeration(ssc);
    }
    DEBUG_COMMAND(printf("Wait %d \n", ssc->counter));
    UnlockCounter(ssc);
}