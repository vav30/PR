#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pid = fork();

    if(pid == 0)
    {
        sleep(5);

        printf("Child PID: %d\n", getpid());
        printf("New Parent PID: %d\n", getppid());
    }
    else
    {
        printf("Parent process terminated\n");
        exit(0);
    }

    return 0;
}
