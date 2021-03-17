#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
  
int main(void) 
{ 
    pid_t pid1 = fork(); 
    pid_t pid2 = fork(); 
    pid_t pid3 = fork(); 
    char *args1[]={"./exit",NULL}; 
    char *args2[]={"./abort",NULL}; 
    char *args3[]={"./nullavalosztas",NULL}; 
    if ( pid1 == 0) 
    {
       execvp(args1[0],args1);  
    }
    if ( pid2 == 0) 
    {
       execvp(args2[0],args2);  
    }
    
    if ( pid3 == 0) 
    {
       execvp(args3[0],args3);  
    }
  
    int status1; 
    int status2; 
    int status3; 
      
    waitpid(pid1, &status1, 0); 
    waitpid(pid2, &status2, 0); 
    waitpid(pid3, &status3, 0); 
    
       
    int exit_status1 = WEXITSTATUS(status1);         
    printf("Exit code: %d\n",exit_status1);
    
    int exit_status2 = WEXITSTATUS(status2);         
    printf("Exit code: %d\n",exit_status2);
    
    int exit_status3 = WEXITSTATUS(status3);         
    printf("Exit code: %d\n",exit_status3); 
     
    return 0; 
} 
