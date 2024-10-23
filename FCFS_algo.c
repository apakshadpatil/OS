#include<stdio.h>

struct Process{
    int id;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
};

void calculateTimes(struct Process processes[], int n)
{
 processes[0].completion=processes[0].arrival + processes[0].burst;
 for(int i=1;i<n;i++)
 {
  processes[i].completion=processes[i-1].completion + processes[i].burst;
 }
 for(int i=0;i<n;i++)
 {
  processes[i].turnaround=processes[i].completion - processes[i].arrival;
  processes[i].waiting=processes[i].turnaround - processes[i].burst;
 }
}

void printProcessinfo(struct Process processes[], int n)
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

int main()
{
 int n;
 printf("Enter no. of processes:");
 scanf("%d",&n);
 struct Process processes[n];
 for(int i=0;i<n;i++)
 {
  processes[i].id=i+1;
  printf("Enter arrival and burst time for process %d:",processes[i].id);
  scanf("%d %d",&processes[i].arrival,&processes[i].burst);
 }
 calculateTimes(processes,n);
 printProcessinfo(processes,n);
 return 0;
}
