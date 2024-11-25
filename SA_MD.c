#include<stdio.h>

struct process{
    int id;
    int arrival;
    int completion;
    int burst;
    int turnaround;
    int waiting;
    int remaining;
};
void printProcessInfo(struct process processes[], int n)
{
 printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
 for(int i=0;i<n;i++)
 {
  printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
  processes[i].id,
  processes[i].arrival,
  processes[i].burst,
  processes[i].completion,
  processes[i].turnaround,
  processes[i].waiting);
 }
}
int calculateTimesSJF(struct process processes[], int n)
{
    int completed=0,time=0;
    for(int i=0;i<n;i++)
    {
        processes[i].completion=0;
    }
    while (completed<n)
    {
        int idx=-1;
        int min_burst=9999;
        for(int i=0;i<n;i++)
        {
            if(processes[i].arrival<=time && processes[i].completion==0)
            {
                if(processes[i].burst<min_burst)
                {
                    min_burst=processes[i].burst;
                    idx=i;
                }
            }
        }
        if(idx!=-1)
        {
            time+=processes[idx].burst;
            processes[idx].completion=time;
            completed++;
        }
        else{
            time++;
        }
    }
    for(int i=0;i<n;i++)
    {
        processes[i].turnaround=processes[i].completion-processes[i].arrival;
        processes[i].waiting=processes[i].turnaround-processes[i].burst;
    }
    
}
int SJF(){
    int n;
    printf("Enter the number of processes:");
    scanf("%d",&n);
    struct process processes[n];
    for(int i=0;i<n;i++)
    {
        processes[i].id = i + 1; 
        printf("Enter Arrival time and Burst time for Process %d: ", processes[i].id);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].remaining = processes[i].burst; 
        processes[i].completion = 0;
    }
    calculateTimesSJF(processes,n);
    printProcessInfo(processes,n);
}
int calculateTimesFCFS(struct process processes[],int n)
{
    processes[0].completion=processes[0].arrival+processes[0].burst;
    for(int i=0;i<n;i++)
    {
        processes[i].completion=processes[i-1].completion+processes[i].burst;
    }
    for(int i=0;i<n;i++)
    {
        processes[i].turnaround=processes[i].completion-processes[i].arrival;
        processes[i].waiting=processes[i].turnaround-processes[i].burst;
    }
}
int FCFS()
{
    int n;
    printf("Enter the number of processes:");
    scanf("%d",&n);
    struct process processes[n];
    for(int i=0;i<n;i++)
    {
        processes[i].id = i + 1; 
        printf("Enter Arrival time and Burst time for Process %d: ", processes[i].id);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].remaining = processes[i].burst; 
        processes[i].completion = 0;
    }
    calculateTimesFCFS(processes,n);
    printProcessInfo(processes,n);
}
int calculateTimesRR(struct process processes[], int n, int quantum)
{   
    int time=0;
    int completed=0;
    int i=0;
    while(completed<n)
    {
        int done=1;
        for( int i=0;i<n;i++)
        {
            if(processes[i].remaining>0)
            {
                done=0;
                if(processes[i].remaining>quantum)
                {
                    time+=quantum;
                    processes[i].remaining-=quantum;
                }
                else
                {
                    time+=quantum;
                    processes[i].remaining=0;
                    processes[i].completion=time;
                    completed++;
                }
            }
        }
        if(done=1)
        {
            break;
        }
    }
    for(int i=0;i<n;i++)
    {
        processes[i].turnaround=processes[i].completion-processes[i].arrival;
        processes[i].waiting=processes[i].turnaround-processes[i].burst;
    }
}
int RoundRobin()
{
    int n, quantum;
    printf("Enter the number of processes:");
    scanf("%d",&n);
    struct process processes[n];
    for(int i=0;i<n;i++)
    {
        processes[i].id = i + 1; 
        printf("Enter Arrival time and Burst time for Process %d: ", processes[i].id);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].remaining = processes[i].burst; 
        processes[i].completion = 0;
    }
    calculateTimesRR(processes,n, quantum);
    printProcessInfo(processes,n);
}
int main()
{
    int choice;
    printf("Select the option for scheduling:\n1.SJF\n2.FCFS\n3.Round Robin");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            SJF();
            break;
        case 2:
            FCFS();
            break;
        case 3:
            RoundRobin();
            break;
        default:
            printf("Select a valid option");
            break;
    }
}
