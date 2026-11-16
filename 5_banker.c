#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    int alloc[10][10], max[10][10];
    int need[10][10], avail[10];
    int finish[10] = {0}, safe[10];
    int count = 0, found;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for(j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need Matrix
    printf("\nNeed Matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Banker's Algorithm
    while(count < n)
    {
        found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > avail[j])
                        break;
                }

                if(j == m)
                {
                    for(k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safe[count] = i;
                    count++;

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    if(count == n)
    {
        printf("\nSystem is in SAFE STATE\n");
        printf("Safe Sequence: ");

        for(i = 0; i < n; i++)
            printf("P%d ", safe[i]);
    }
    else
    {
        printf("\nSystem is in UNSAFE STATE");
    }

    return 0;
}
