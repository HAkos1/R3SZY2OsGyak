#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    printf("Kilepes CTRL+c billentyukombinacioval\n");
    while(true)
    {
        char cmd[50];
        printf("Irjon be egy unix parancsot!\n");
        fgets(cmd, 50, stdin);
        system(cmd);
    }
    
    return 0;
}

