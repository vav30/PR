
/*
nano filename.c
gcc filename.c -o process
./process
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int a[20], b[20], n, i, j, temp;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    int pid = fork();

    if(pid == 0)
    {
        // Child process - Selection Sort

        for(i = 0; i < n; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                if(b[i] > b[j])
                {
                    temp = b[i];
                    b[i] = b[j];
                    b[j] = temp;
                }
            }
        }

        printf("\nChild Sorted Array: ");
        for(i = 0; i < n; i++)
            printf("%d ", b[i]);
    }
    else
    {
        // Parent process - Bubble Sort

        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n-i-1; j++)
            {
                if(a[j] > a[j+1])
                {
                    temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                }
            }
        }

        printf("\nParent Sorted Array: ");
        for(i = 0; i < n; i++)
            printf("%d ", a[i]);

        wait(NULL);

        printf("\n\nParent process completed.");
    }

    return 0;
}
