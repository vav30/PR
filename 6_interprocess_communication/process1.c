#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd;
    char str[100];

    fd = open("fifo1", O_WRONLY);

    printf("Enter sentences (END to stop):\n");

    while(1)
    {
        fgets(str, 100, stdin);

        if(strncmp(str, "END", 3) == 0)
            break;

        write(fd, str, strlen(str));
    }

    close(fd);

    fd = open("fifo2", O_RDONLY);

    printf("\nResult:\n");

    while(read(fd, str, 100) > 0)
        printf("%s", str);

    close(fd);

    return 0;
}
