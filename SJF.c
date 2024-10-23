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
 int completed=0, time=0;
 
 for (int i = 0; i < n; i++) {
        processes[i].completion = 0;
    }
 while(completed<n)
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
   time += processes[idx].burst;
   processes[idx].completion=time;
   completed++;
  } 
  else
  {
   time++;
  }
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
