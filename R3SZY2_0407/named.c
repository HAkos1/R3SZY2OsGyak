#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    char* fifo = "/ujtwll";
    char* kiirando = "";
    mkfifo(fifo, 0666);
    int fd = open(fifo, O_RDWR);

    if(pipe(fd) < 0) exit(1);
    if(fork() == 0){
        char* szoveg = "Horvath Akos";
        write(fd, szoveg, 16);
    }
    else{
        read(fd, kiirando, 16);
        printf("%s\n", kiirando);
    }
	return 0;
}
