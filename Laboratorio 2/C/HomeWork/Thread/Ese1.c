// #include "../MyLib.c"
// #include "../util.c"
// #include "../DataStructure/boundedqueue.c"

// #define BUFFER_SIZE 256;
// BQueue_t *ReaderToTokenizer, TokenizerToWriter;

// int main(int argc, const char *argv[])
// {
//     ReaderToTokenizer = initBQueue(sizeof(char) * BUFFER_SIZE);
//     TokenizerToWriter = initBQueue(sizeof(char) * BUFFER_SIZE);

//     pthread_mutex_init(&ReaderToTokenizer.m, NULL);
//     pthread_mutex_init(&TokenizerToWriter.m, NULL);

//     if (argc != 2)
//     {
//         WRITE_ON_STDOUT("to many argument");
//         return -1;
//     }
// }

// void ReadFile(char fileName[])
// {

//     // FILE *fp;
//     // char *line = NULL;
//     // size_t len = 0;
//     // ssize_t read;

//     // fp = fopen(fileName, "r");
//     // if (fp == NULL)
//     //     exit(EXIT_FAILURE);

//     // while ((read = getline(&line, &len, fp)) != -1)
//     // {
//     //     LockQueue(&ReaderToTokenizer);

//     //     int n = strlen(line);
//     //     push(&ReaderToTokenizer, line);
//     //     write(pipe, line, n);
//     //     int n1 = n / sizeof(char);
//     //     while ()
//     //         pthread_cond_wait(&ReaderToTokenizer.cfull, &ReaderToTokenizer.m);

//     //     ;
//     //     pthread_cond_signal(&ReaderToTokenizer.cempty);

//     //     UnlockQueue(&ReaderToTokenizer);
//     // }

//     // fclose(fp);
//     // close(pipe);

//     // if (line)
//     //     free(line);
// }

// void Tokenize(char fileName[])
// {

//     // char buff[256];

//     // LOCK(&mutex);
//     // // while (PipeNElement <= 0)
//     // //     pthread_cond_wait(&NotEmpty, &mutex);

//     // read(pipe, buff, sizeof(char) * 256);

//     // UNLOCK(&mutex);

//     // pthread_cond_signal(&NotEmpty);

//     // close(pipe);
// }