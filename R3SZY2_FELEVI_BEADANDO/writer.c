#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void solve_equation(eq_t* e);

int main()
{
    key_t key = ftok("input", 65);
    printf("key: %x\n",key);
    
    int msgid = msgget(key, 0644|IPC_CREAT);

    msgrcv(msgid, &message, sizeof(message), 2, 0);
    printf("Waiting for message...\n");
    int buffer_size = message.msg;
    printf("Recieved message: %d\n", message.msg);

    int shmid = shmget(key, buffer_size, 0666|IPC_CREAT);
    if(shmid == -1)
    {
        perror("Shared memory error!");
        return 1;
    }

    eq_t* eq;
    eq = (eq_t*) shmat(shmid, 0, 0);

    for(int i = 0; i < buffer_size/sizeof(eq_t); i++)
    {
        eq_t e = eq[i];
        printf("%f %f %f %f+%f %f+%f\n", e.a, e.b, e.c, e.realPart, e.imaginaryPart, e.realPart, e.imaginaryPart);
    }    

    FILE* fptr;
    fptr = fopen("output","w");   
    if(fptr == NULL)
    {
        perror("Cannot open file!");
        return 1;    
    }

    for(int i = 0; i < buffer_size/sizeof(eq_t); i++)
    {
        solve_equation(&eq[i]);
        eq_t e = eq[i];
        if(e.isImaginary == 0)
        {
            printf("%f %f %f %f %f\n", e.a, e.b, e.c, e.root1, e.root2);
            fprintf(fptr,"%f %f %f %f %f\n", e.a, e.b, e.c, e.root1, e.root2);
        }
        else
        {
            printf("%f %f %f %f+%fi %f+%fi\n", e.a, e.b, e.c, e.realPart, e.imaginaryPart, e.realPart, e.imaginaryPart);
            fprintf(fptr,"%f %f %f %f+%fi %f+%fi\n", e.a, e.b, e.c, e.realPart, e.imaginaryPart, e.realPart, e.imaginaryPart);
        }
    }

    shmdt(eq);
    shmctl(shmid,IPC_RMID,NULL);

    
    return 0;
}

void solve_equation(eq_t* e)
{
    float discriminant = e->b * e->b - 4 * e->a * e->c;
    
    if(discriminant > 0)
    {
        e->root1 = (-e->b + sqrt(discriminant)) / 2 * e->a;
        e->root2 = (-e->b - sqrt(discriminant)) / 2 * e->a;
    }
    else if (discriminant == 0)
    {
        e->root1 = e->root2 = -e->b / (2*e->a);
    }
    else
    {
        e->isImaginary = 1;
        e->realPart = -e->b / (2*e->a);
        e->imaginaryPart = sqrt(-discriminant) / (2*e->a);
    }
}
