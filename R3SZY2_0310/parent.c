#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]){
    char *args[]={"./child",NULL};
    
	int child_pid, wait_pid, status;
	child_pid=fork();
    
	if(child_pid==0)
    { // child process
    execvp(args[0],args); 
		printf("ERROR\n");
                exit(1);
	}
	else
    { // parent process 
		wait_pid=wait(NULL);
		printf("%d %d",getpid(),wait_pid);
	}
}
