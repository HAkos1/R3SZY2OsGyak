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

const long SEMKEY = 123456;

int main()
{
    union semun arg;
    int cmd;
	int nsems = 1;
	int semflg = 00666 | IPC_CREAT;
	int semid = semget (SEMKEY, nsems, semflg);
    int returnvalue;

	if (semid < 0 ) 
    {
        perror("Semget error!");
        return 1;
    }
	else printf("semid: %d\n",semid);

	cmd = GETVAL;
	returnvalue = semctl(semid,0, cmd, NULL);

	printf("semval: %d\n",returnvalue);
    return 0;
}