#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[20], b[20], n, head, size;
    int i, j, temp, total;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &size);

    // SSTF
    int visited[20] = {0};
    int pos = head;
    total = 0;

    printf("\nSSTF: %d", head);

    for(i = 0; i < n; i++)
    {
        int min = 9999, index = -1;

        for(j = 0; j < n; j++)
        {
            if(!visited[j] && abs(pos - a[j]) < min)
            {
                min = abs(pos - a[j]);
                index = j;
            }
        }

        visited[index] = 1;
        total += abs(pos - a[index]);
        pos = a[index];

        printf(" -> %d", pos);
    }

    printf("\nTotal SSTF Movement: %d\n", total);

    // Sort requests for SCAN and C-LOOK
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

    // SCAN - Moving towards higher tracks first
    total = 0;
    pos = head;

    printf("\nSCAN: %d", head);

    for(i = 0; i < n; i++)
    {
        if(b[i] >= head)
        {
            total += abs(pos - b[i]);
            pos = b[i];
            printf(" -> %d", pos);
        }
    }

    total += abs(pos - (size - 1));
    pos = size - 1;
    printf(" -> %d", pos);

    for(i = n - 1; i >= 0; i--)
    {
        if(b[i] < head)
        {
            total += abs(pos - b[i]);
            pos = b[i];
            printf(" -> %d", pos);
        }
    }

    printf("\nTotal SCAN Movement: %d\n", total);

    // C-LOOK - Moving towards higher tracks first
    total = 0;
    pos = head;

    printf("\nC-LOOK: %d", head);

    for(i = 0; i < n; i++)
    {
        if(b[i] >= head)
        {
            total += abs(pos - b[i]);
            pos = b[i];
            printf(" -> %d", pos);
        }
    }

    for(i = 0; i < n; i++)
    {
        if(b[i] < head)
        {
            if(pos != b[i])
            {
                total += abs(pos - b[i]);
                pos = b[i];
                printf(" -> %d", pos);
            }
        }
    }

    printf("\nTotal C-LOOK Movement: %d\n", total);

    return 0;
}
