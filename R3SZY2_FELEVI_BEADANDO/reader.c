#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

typedef struct equation
{
    float a;
    float b;
    float c;
    float root1;
    float root2;
    float realPart;
    float imaginaryPart;
    int isImaginary;
}eq_t;

struct msg_buffer
{
    long mtype;
    int msg;
}message;

int main()
{
    key_t key = ftok("input", 65);
    printf("Key: %x\n",key);    

    int msgid = msgget(key, 0644|IPC_CREAT);
    message.mtype = 2;

    FILE* fptr;
    fptr = fopen("input","r");
    if(fptr == NULL)
    {
        perror("File cannot be opened!");
        return 1;    
    }
   
    int numofequations = 0;
    fscanf(fptr,"%d",&numofequations);

    eq_t eqarray[numofequations];
    printf("Number of equations: %d\n", numofequations);

    for(int i = 0; i < numofequations; i++)
    {
        float a, b, c;
        fscanf(fptr,"%f %f %f", &a, &b, &c);
        eqarray[i].a = a;
        eqarray[i].b = b;
        eqarray[i].c = c;
        eqarray[i].root1 = 0;
        eqarray[i].root2 = 0;
        eqarray[i].isImaginary = 0;
        eqarray[i].realPart = 0;
        eqarray[i].imaginaryPart = 0;
    }

    fclose(fptr);
    printf("Size of eqarray: %ld\n",sizeof(eqarray));

    message.msg = sizeof(eqarray);
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Message sent: %d\n",message.msg);

    int shmid = shmget(key, sizeof(eqarray), 0666|IPC_CREAT);
    if(shmid == -1)
    {
        perror("Shared memory segment allocation error!");
        return 1;
    }
    
    eq_t* eq = (eq_t*) shmat(shmid, 0, 0);
    
    memcpy(eq, eqarray, sizeof(eqarray));

    for(int i = 0; i < numofequations; i++)
    {
       printf("%f %f %f\n", eq[i].a, eq[i].b, eq[i].c);
    }

    shmdt(eq);
    return 0;
}
