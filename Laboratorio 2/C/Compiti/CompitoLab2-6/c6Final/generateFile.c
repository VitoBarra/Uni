#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>


///genera un file binario con nome argv[2], contenente argv[1] numeri long random 

int main(int argc, char** argv){
	char* F=argv[2];//name of file
	int N=atoi(argv[1]);//number of  numbers
	srand(time(NULL));
	int f=open(F,O_CREAT|O_RDWR);
	for (int i=0;i<N;i++){
		long l =rand()%100;
		write(f,&l,sizeof(l));
	}
	close(f);

}
