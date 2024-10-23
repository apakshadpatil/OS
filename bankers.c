#include <stdio.h>

#define P 5 
#define R 3 

int isSafe(int processes[], int avail[], int max[][R], int alloc[][R]) 
{
    int need[P][R], finish[P], safeSeq[P], work[R];
    
    for (int i = 0; i < P; i++) 
    {
        for (int j = 0; j < R; j++) 
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    for (int i = 0; i < R; i++) 
    {
        work[i] = avail[i];
    }
    for (int i = 0; i < P; i++) 
    {
        finish[i] = 0;
    }

    int count = 0; 

    while (count < P) 
    {
        int found = 0;
        for (int p = 0; p < P; p++) 
        {
            if (finish[p] == 0) 
            { 
                int canProceed = 1;
                for (int j = 0; j < R; j++) 
                {
                    if (need[p][j] > work[j]) 
                    {
                        canProceed = 0;
                        break;
                    }
                }
                
                if (canProceed) 
                {
                    for (int k = 0; k < R; k++) 
                    {
                        work[k] += alloc[p][k]; 
                    }
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }

        if (!found) 
        {
            printf("The system is not in a safe state.\n");
            return 0;
        }
    }

    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) 
    {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
    return 1;
}

int main() 
{
    int processes[] = {0, 1, 2, 3, 4};
    int avail[] = {3, 3, 2};

    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int alloc[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    isSafe(processes, avail, max, alloc);

    return 0;
}
