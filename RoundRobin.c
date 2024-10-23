#include<stdio.h>

struct Process {
    int id;        
    int arrival;   
    int burst;     
    int remaining; 
    int completion;
    int turnaround;
    int waiting;   
};

void calculateTimes(struct Process processes[], int n, int quantum) {
    int time = 0;           
    int completed = 0;      
    int i = 0;             

    while (completed < n) {
        int done = 1;      

       
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining > 0) {
                done = 0;   

                if (processes[i].remaining > quantum) {
                    time += quantum;  
                    processes[i].remaining -= quantum; 
                } else {
                    
                    time += processes[i].remaining;
                    processes[i].remaining = 0;
                    processes[i].completion = time;
                    completed++;
                }
            }
        }
        if (done == 1)
            break;
    }
    for (int i = 0; i < n; i++) {
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
    }
}

void printProcessInfo(struct Process processes[], int n) {
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].id,
               processes[i].arrival,
               processes[i].burst,
               processes[i].completion,
               processes[i].turnaround,
               processes[i].waiting);
    }
}

int main() 
{
    int n, quantum;
    printf("Enter number of Processes: ");
    scanf("%d", &n);
    struct Process processes[n]; 
    for (int i = 0; i < n; i++) 
   {
        processes[i].id = i + 1; 
        printf("Enter Arrival time and Burst time for Process %d: ", processes[i].id);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].remaining = processes[i].burst; 
        processes[i].completion = 0; 
    }
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    calculateTimes(processes, n, quantum);    
    printProcessInfo(processes, n);
    return 0;
}
