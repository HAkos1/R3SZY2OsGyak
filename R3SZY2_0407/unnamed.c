#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int p[2];
    char* kiirando = "";
    
    if(pipe(p) < 0) exit(1);
    if(fork() == 0){
        char* szoveg = "Horvath Akos";
        write(p[1], szoveg, 23);
    }
    else{
        read(p[0], kiirando, 23);
        printf("%s\n", kiirando);
    }
	return 0;
}
