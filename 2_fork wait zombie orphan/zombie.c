#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();

    if(pid == 0)
    {
        printf("Child process terminated\n");
        exit(0);
    }
    else
    {
        printf("Parent sleeping...\n");
        sleep(20);

        wait(NULL);
        printf("Parent completed\n");
    }

    return 0;
}
