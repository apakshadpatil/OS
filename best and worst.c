#include <stdio.h> 
#include <string.h> // For memcpy

void worstFit(int b[], int m, int p[], int n) { 
    for (int i = 0; i < n; i++) { 
        int maxIdx = -1; 
        for (int j = 0; j < m; j++) { 
            if (b[j] >= p[i] && (maxIdx == -1 || b[maxIdx] < b[j])) { 
                maxIdx = j; 
            } 
        } 
        if (maxIdx != -1) { 
            printf("Process %d allocated to Block %d\n", i + 1, maxIdx + 1); 
            b[maxIdx] -= p[i]; 
        } else { 
            printf("Process %d not allocated\n", i + 1); 
        } 
    } 
}

void bestFit(int b[], int m, int p[], int n) { 
    for (int i = 0; i < n; i++) { 
        int bestIdx = -1; 
        for (int j = 0; j < m; j++) { 
            if (b[j] >= p[i] && (bestIdx == -1 || b[bestIdx] > b[j])) { 
                bestIdx = j; 
            } 
        } 
        if (bestIdx != -1) { 
            printf("Process %d allocated to Block %d\n", i + 1, bestIdx + 1); 
            b[bestIdx] -= p[i]; 
        } else { 
            printf("Process %d not allocated\n", i + 1); 
        } 
    } 
}

void firstFit(int b[], int m, int p[], int n) { 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) { 
            if (b[j] >= p[i]) { 
                printf("Process %d allocated to Block %d\n", i + 1, j + 1); 
                b[j] -= p[i]; 
                break; 
            } 
        } 
    } 
}

int main() { 
    int blockSize[10], processSize[10], m, n; 
    int originalBlockSize[10]; // Array to hold the original block sizes

    printf("Enter number of blocks: "); 
    scanf("%d", &m); 
    printf("Enter block sizes:\n"); 
    for (int i = 0; i < m; i++) { 
        printf("block %d=", i + 1);
        scanf("%d", &blockSize[i]); 
        originalBlockSize[i] = blockSize[i]; // Save the original block sizes
    }

    printf("Enter number of processes: "); 
    scanf("%d", &n); 
    printf("Enter process sizes:\n"); 
    for (int i = 0; i < n; i++) { 
        printf("process %d=", i + 1);
        scanf("%d", &processSize[i]); 
    }

    // Worst Fit Allocation
    printf("\nWorst Fit Allocation:\n"); 
    worstFit(blockSize, m, processSize, n); 

    // Reset block sizes for Best Fit Allocation
    memcpy(blockSize, originalBlockSize, m * sizeof(int)); 
    printf("\nBest Fit Allocation:\n"); 
    bestFit(blockSize, m, processSize, n); 

    // Reset block sizes for First Fit Allocation
    memcpy(blockSize, originalBlockSize, m * sizeof(int)); 
    printf("\nFirst Fit Allocation:\n"); 
    firstFit(blockSize, m, processSize, n); 

    return 0; 
}
