#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define N 4


typedef struct{
   int row;
   int (*A)[N];
   int (*B)[N];
   int (*C)[N];
}ThreadData;

void* multiply_row(void* arg)
{
 ThreadData* data = (ThreadData*)arg;
 int row=data->row;
 for(int j=0;j<N;j++)
 {
  data->C[row][j]=0;
  for(int k=0;k<N;k++)
  {
   data->C[row][j]+=data->A[row][k]*data->B[k][j];
  }
 }
 return NULL;
}

int main()
{
 int A[N][N]={
           {1,2,3,4},
           {5,6,7,8},
           {9,10,11,12},
           {13,14,15,16}
           };
 int B[N][N]={
           {1,2,3,4},
           {5,6,7,8},
           {9,10,11,12},
           {13,14,15,16}
           };
 int C[N][N];
 pthread_t threads[N];
 ThreadData threadData[N];
 for(int i=0;i<N;i++)
 {
  threadData[i].row=i;
  threadData[i].A=A;
  threadData[i].B=B;
  threadData[i].C=C;
  if(pthread_create(&threads[i],NULL,multiply_row,(void*)&threadData[i])!=0)
  {
   perror("Failed to create thread");
   return 1;
  }
 }
 for(int i=0;i<N;i++)
 {
 pthread_join(threads[i],NULL);
 }
 printf("Resultant matrix C:\n");
 for(int i=0;i<N;i++)
 {
  for(int j=0;j<N;j++)
  {
   printf("%d ",C[i][j]);
  }
  printf("\n");
 }
 return 0;
}
