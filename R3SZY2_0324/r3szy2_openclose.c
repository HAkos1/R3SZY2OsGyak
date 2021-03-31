#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/fcntl.h>

#define BYTE_COUNT 100

int main()
{
    char str[BYTE_COUNT];
    int bytesread = 0;
    int cursorpos = 0;

    int file = open("r3szy2.txt", O_RDWR);
    if(file < 0)
    {
        printf("File megnyitasa sikertelen\n"); 
        return 1;    
    }

    bytesread = read(file, str, BYTE_COUNT);
    if(bytesread < 0)
    {
        printf("File olvasasa sikertelen\n"); 
        return 1;    
    }

    printf("%d byte kiolvasva a fajlbol\n", bytesread);
    
    cursorpos = lseek(file, 0, SEEK_SET);

    if(cursorpos < 0)
    {
        printf("Kurzor allitasa sikertelen\n");
        return 1;
    }

    printf("Kurzor tavolsaga a fajl elejetol: %d\n", cursorpos);

    return 0;
}
