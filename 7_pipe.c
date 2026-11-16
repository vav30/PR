#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int p1[2], p2[2];
    char filename[100], buffer[100];
    int pid, n;

    pipe(p1);
    pipe(p2);

    pid = fork();

    if(pid > 0)
    {
        // Parent Process

        close(p1[0]);
        close(p2[1]);

        printf("Enter file name: ");
        scanf("%99s", filename);

        write(p1[1], filename, strlen(filename) + 1);
        close(p1[1]);

        printf("\nFile Contents:\n");

        while((n = read(p2[0], buffer, sizeof(buffer))) > 0)
        {
            write(1, buffer, n);
        }

        close(p2[0]);
        wait(NULL);
    }
    else if(pid == 0)
    {
        // Child Process

        close(p1[1]);
        close(p2[0]);

        read(p1[0], filename, sizeof(filename));
        close(p1[0]);

        FILE *fp = fopen(filename, "r");

        if(fp != NULL)
        {
            while((n = fread(buffer, 1, sizeof(buffer), fp)) > 0)
            {
                write(p2[1], buffer, n);
            }

            fclose(fp);
        }
        else
        {
            char msg[] = "File not found!\n";
            write(p2[1], msg, strlen(msg));
        }

        close(p2[1]);
    }

    return 0;
}
