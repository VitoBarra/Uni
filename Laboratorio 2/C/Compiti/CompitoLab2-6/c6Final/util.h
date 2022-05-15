#if !defined(_UTIL_H)
#define _UTIL_H

#include <assert.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>


#if !defined(BUFSIZE)
#define BUFSIZE 256
#endif

#if !defined(EXTRA_LEN_PRINT_ERROR)
#define EXTRA_LEN_PRINT_ERROR   512
#endif

#if !defined(MAX_FILENAME_LENGTH)
#define MAX_FILENAME_LENGTH     255
#endif


#define SYSCALL_EXIT(name, r, sc, str, ...)		\
  if ((r=sc) == -1) {					\
      perror(#name);					\
      int errno_copy = errno;				\
      print_prefix(str,"ERROR:", ##__VA_ARGS__);	\
      exit(errno_copy);					\
    }

#define SYSCALL_PRINT(name, r, sc, str, ...)		\
  if ((r=sc) == -1) {					\
      perror(#name);					\
	int errno_copy = errno;				\
	print_prefix(str,"ERROR:", ##__VA_ARGS__);	\
	errno = errno_copy;				\
    }

#define SYSCALL_RETURN(name, r, sc, str, ...)		\
  if ((r=sc) == -1) {					\
    perror(#name);					\
    int errno_copy = errno;				\
    print_prefix(str,"ERROR:", ##__VA_ARGS__);		\
    errno = errno_copy;					\
    return r;						\
  }

#define CHECK_EQ_EXIT(name, X, val, str, ...)		\
  if ((X)==val) {					\
    perror(#name);					\
    int errno_copy = errno;				\
    print_prefix(str,"ERROR:", ##__VA_ARGS__);		\
    exit(errno_copy);					\
  }

#define CHECK_NEQ_EXIT(name, X, val, str, ...)		\
  if ((X)!=val) {					\
    perror(#name);					\
    int errno_copy = errno;				\
    print_prefix(str,"ERROR:",##__VA_ARGS__);		\
    exit(errno_copy);					\
  }

#if defined(DEBUG)
#define DBG(str, ...)			         	\
  print_prefix(str, "DBG:", ##__VA_ARGS__)
#else
#define DBG(str, ...)
#endif

static inline void print_prefix(const char * str, const char *prefix, ...) {
    va_list argp;
    char * p=(char *)malloc(strlen(str)+strlen(prefix)+EXTRA_LEN_PRINT_ERROR);
    if (!p) {
	perror("malloc");
        fprintf(stderr,"FATAL ERROR in print_prefix\n");
        return;
    }
    strcpy(p,prefix);
    strcpy(p+strlen(prefix), str);
    va_start(argp, prefix);
    vfprintf(stderr, p, argp);
    va_end(argp);
    free(p);
}

/**
 * @function isNumber
 * @brief Check if the string is a number. 
 *        It returns 0 if ok, 1 if it is not a number, and 2 if overflow/underflow occurs.
 */
static inline int isNumber(const char* s, long* n) {
  if (s==NULL) return 1;
  if (strlen(s)==0) return 1;
  char* e = NULL;
  errno=0;
  long val = strtol(s, &e, 10);
  if (errno == ERANGE) return 2;    // overflow/underflow
  if (e != NULL && *e == (char)0) {
    *n = val;
    return 0;   // ok
  }
  return 1;   // it's not a number
}
/**
 * @function isRegular
 * @brief Check if the name provided as first argument is a regular file.
 *        It returns 1 if success, 0 if it is not a regular file, and -1 if error.
 *        The argument size is set only if name is a regular file and if size is not NULL.
 */
static inline int isRegular(const char name[], size_t *size) {
  struct stat statbuf;
  if (stat(name, &statbuf) == -1) return -1;
  if (!S_ISREG(statbuf.st_mode)) return 0;

  if (size != NULL) {
    *size = statbuf.st_size;
  }
  
  return 1;
}


#define LOCK(l)      if (pthread_mutex_lock(l)!=0)        {             \
    fprintf(stderr, "FATAL ERROR lock\n");				\
    pthread_exit((void*)EXIT_FAILURE);					\
  }   
#define LOCK_RETURN(l, r)  if (pthread_mutex_lock(l)!=0)  {		\
    fprintf(stderr, "FATAL ERROR lock\n");				\
    return r;								\
  }   

#define UNLOCK(l)    if (pthread_mutex_unlock(l)!=0) {		        \
    fprintf(stderr, "FATAL ERROR unlock\n");				\
    pthread_exit((void*)EXIT_FAILURE);					\
  }
#define UNLOCK_RETURN(l,r)    if (pthread_mutex_unlock(l)!=0)  {	\
    fprintf(stderr, "FATAL ERROR unlock\n");				\
    return r;								\
  }
#define WAIT(c,l)    if (pthread_cond_wait(c,l)!=0)       {	        \
    fprintf(stderr, "FATAL ERROR wait\n");				\
    pthread_exit((void*)EXIT_FAILURE);					\
  }
/* ATTENZIONE: t e' un tempo assoluto! */
#define TWAIT(c,l,t) {							\
    int r=0;								\
    if ((r=pthread_cond_timedwait(c,l,t))!=0 && r!=ETIMEDOUT) {		\
      fprintf(stderr, "FATAL ERROR timed wait\n");			\
      pthread_exit((void*)EXIT_FAILURE);				\
    }									\
  }
#define SIGNAL(c)    if (pthread_cond_signal(c)!=0)       {		\
    fprintf(stderr, "FATAL ERROR signal\n");				\
    pthread_exit((void*)EXIT_FAILURE);					\
  }
#define BCAST(c)     if (pthread_cond_broadcast(c)!=0)    {		\
    fprintf(stderr, "FATAL ERROR broadcast\n");				\
    pthread_exit((void*)EXIT_FAILURE);					\
  }
static inline int TRYLOCK(pthread_mutex_t* l) {
  int r=0;		
  if ((r=pthread_mutex_trylock(l))!=0 && r!=EBUSY) {		    
    fprintf(stderr, "FATAL ERROR unlock\n");		    
    pthread_exit((void*)EXIT_FAILURE);			    
  }								    
  return r;	
}
static inline int P(sem_t* sem) {
  if (sem_wait(sem) == -1) {
    perror("sem_wait");
    return -1;
  }
  return 0;
}
static inline int V(sem_t* sem) {
  if (sem_post(sem) == -1) {
    perror("sem_post");
    return -1;
  }
  return 0;
}


#endif /* _UTIL_H */

