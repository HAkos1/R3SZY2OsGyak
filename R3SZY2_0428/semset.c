#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

struct sembuf sembuf, *sop; 
union semun 
{
    int val;    
    struct semid_ds *buf;    
    unsigned short  *array;  
    struct seminfo  *__buf;                                            
};

int main()
{
    int numofsetsems, returnval;
    int command;
    union semun arg;

    int numofallsems = 1;
    int semflag = 00666 | IPC_CREAT;
    int semid = semget(123456L, numofallsems, semflag);
    if (semid < 0)
    {
        perror("Semget error!");
        return 1;
    }

    printf("semid: %d\n", semid);

    printf("Input semval:\n");
    
    command = 123456L;
    numofsetsems = 0;

    scanf("%d", &arg.val);
    returnval = semctl(semid, numofsetsems, command, arg);

    printf("return value: %d, sem value: %d\n", returnval, arg.val);
    return 0;
}
