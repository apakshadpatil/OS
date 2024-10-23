#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void fcfs(int requests[], int n, int head)
{
    int total_head_movement = 0;
    int current_position = head;

    printf("FCFS Scheduling Order:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Move from %d to %d\n", current_position, requests[i]);
        total_head_movement += abs(current_position - requests[i]);
        current_position = requests[i];
    }

    printf("Total head movement: %d\n", total_head_movement);
}

void scan(int requests[], int n, int head, int disk_size)
{
    int total_head_movement = 0;
    int current_position = head;
    int sorted_requests[MAX_REQUESTS];

    for (int i = 0; i < n; i++)
    {
        sorted_requests[i] = requests[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (sorted_requests[j] > sorted_requests[j + 1])
            {
                int temp = sorted_requests[j];
                sorted_requests[j] = sorted_requests[j + 1];
                sorted_requests[j + 1] = temp;
            }
        }
    }

    printf("SCAN Scheduling Order:\n");

    for (int i = 0; i < n; i++)
    {
        if (sorted_requests[i] >= current_position)
        {
            printf("Move from %d to %d\n", current_position, sorted_requests[i]);
            total_head_movement += abs(current_position - sorted_requests[i]);
            current_position = sorted_requests[i];
        }
    }

    if (current_position != disk_size - 1)
    {
        printf("Move from %d to %d\n", current_position, disk_size - 1);
        total_head_movement += abs(current_position - (disk_size - 1));
        current_position = disk_size - 1;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (sorted_requests[i] <= head)
        {
            printf("Move from %d to %d\n", current_position, sorted_requests[i]);
            total_head_movement += abs(current_position - sorted_requests[i]);
            current_position = sorted_requests[i];
        }
    }

    printf("Total head movement: %d\n", total_head_movement);
}

int main()
{
    int requests[MAX_REQUESTS];
    int n, head, disk_size;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    if (n > MAX_REQUESTS)
    {
        printf("Error: Maximum requests exceeded.\n");
        return 1;
    }

    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    fcfs(requests, n, head);
    printf("\n");
    scan(requests, n, head, disk_size);

    return 0;
}
