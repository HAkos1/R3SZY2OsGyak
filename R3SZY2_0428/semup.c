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
    unsigned nsops;

	if (semid < 0 ) 
    {
        perror("Semget error!");
        return 1;
    }
	else printf("semid: %d\n",semid);

    nsops = 1;
    sembuf.sem_num = 0;
    sembuf.sem_op = 1;
    sembuf.sem_flg = 0666;
    sop = &sembuf;
    returnvalue = semop(semid, sop, nsops);

	printf("up return: %d\n",returnvalue);
    return 0;
}