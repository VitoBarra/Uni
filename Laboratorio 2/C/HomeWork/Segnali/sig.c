#include "../MyLib.c"

volatile int SigCount = 0;

void SIGTSTPHandler_WriteSigCount();
void SIGINTHandler_IncrementSigCount();
void SIGALRMHandler_exit();

int main(int argnc, char const *argv[])
{

    SET_SIGNAL_HANDLER(s1, SIGINT, SIGINTHandler_IncrementSigCount);

    SET_SIGNAL_HANDLER(s2, SIGTSTP, SIGTSTPHandler_WriteSigCount);

    SET_SIGNAL_HANDLER(s3, SIGALRM, SIGTSTPHandler_WriteSigCount);

    while (1)
        ;
}

void SIGINTHandler_IncrementSigCount()
{
    SigCount++;
}

void SIGALRMHandler_exit()
{
    exit(1);
}

void SIGTSTPHandler_WriteSigCount()
{
    static int SIGTSTPcallCount;

    itos(s, SigCount);
    WRITE_ON_STDOUT("\n");
    WRITE_ON_STDOUT(s);
    WRITE_ON_STDOUT("\n");
    if (SIGTSTPcallCount < 3)
        SIGTSTPcallCount++;
    else
        SIGTSTPcallCount = 1;

    if (SIGTSTPcallCount >= 3)
    {
        alarm(10);
        WRITE_ON_STDOUT("\nvuoi chiudere il programma(0:no | 1:yes):");
        READ_FROM_STDOUT(buffer, 4);

        switch (atoi(buffer))
        {
        case 0:
            alarm(0);
            break;
        case 1:
            exit(1);
            break;
        default:
            WRITE_ON_STDOUT("\nERRORE IN Input")
            break;
        }
    }
}