#include <stdio.h>
#include <time.h>
#include <stdlib.h>



struct cstruct multilevel1(int,int);
struct cstruct multilevel2(int,int,int,float,float,int,int);


struct pstruct
{   
	int process_id;
	int arrival_time;
	int burst_time;
  int response_time;

};

struct cstruct
{
float total_wait;
float total_tat;
int total;
};

//---------------Main begins here--------------------------------
int main()
{
   int n=3,n1,n2,n3,set=1;
   struct cstruct c1,c2,c3;
   int i=2;
   int counter=1;
   printf("Number of levels in Multi level queue are: %d ",n);
   srand(time(0));//each time program run will create different random numbers
 // n1=3;
  n1= rand() % 5+1 ;
	printf("\nNumber of processes in queue 1 are : %d\n",n1);
	n2= rand() % 5+1 ;
  printf("Number of processes in queue 2 are : %d\n",n2);
	n3= rand() % 5+1 ;
	printf("Number of processes in queue 3 are : %d\n",n3);
	//printf("Priority Order is : queue1>queue2>queue3 \n");
  int p=n1+n2;
  int q=n1+n2+n3;
    if(n1!=0)
    	c1=multilevel1(set,n1);
    //printf("%d\n",c1.total );
      set++;
    if(n2!=0)
    	c2=multilevel2(set,n2,n1,c1.total_wait,c1.total_tat,c1.total,p);
   // printf("%d\n",c2.total );
      set++;
    if(n3!=0)
      c3=multilevel2(set,n3,n2,c2.total_wait,c2.total_tat,c2.total,q);
   // printf("%d\n",c3.total );


printf("*******************************************************************************\n");
printf("Total Average Turn Around Time: %f\n",c3.total_tat/q);
printf("Total Average waiting Time:%f\n",c3.total_wait/q);
printf("Total Time: %d\n",c3.total);
printf("*******************************************************************************\n");

  return 0;

}


struct cstruct multilevel1(int set,int n)
 {
   int i,j,l=1,quantum,k=0;
   struct cstruct c1;
   int rem_bt[100]={0};
   int Priority[n],fg[n];

   srand(time(0));
   //printf("\nNumber of processesin queue 1 are : %d\n",n);
   if(n==0)
   {
   	printf("No Process in read queue..Exiting Now\n");
   	exit(0);
   }
   struct  pstruct q2[n];
   struct  pstruct key[n];
   int waiting_time[n];
   int turn_around_time[n];
   c1.total=0;
   int res[n];

   printf("\nCPU scheduling algorithm to be used is Round Robin\n");
	for(i=0;i<n;i++)
	{   
		q2[i].process_id=i; 
		q2[i].arrival_time=rand() % 10 + 1;
		q2[i].burst_time=rand() % 10 + 1;
    q2[i].response_time=0;
		waiting_time[i]=0;
        turn_around_time[i]=0;
        Priority[i]=set;
        fg[i]=1;
        res[i]=0;

	}

	
	//scanf("%d",&quantum);
  quantum=rand()%3+1;
  printf("quantum : %d",quantum);

	printf("\n\nProcess_id     Arrival time     Burst Time     Priority      fg  \n");
	printf("------------------------------------------------------------------------\n");
	for(i=0;i<n;i++)
	printf("\n   %d         |     %d        |     %d       |    %d       |     %d     \n",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time,Priority[i],fg[i]);
	
	
     
 for(i=1;i<n;i++)
   {
       key[i]=q2[i];
       j = i-1;
 	   while (j >= 0 && q2[j].arrival_time> key[i].arrival_time)
       {
       	   q2[j+1]=q2[j];
           j = j-1;
       }
       q2[j+1] = key[i];
   }

  
   for(i=0;i<n;i++)
	{
	rem_bt[i]=q2[i].burst_time;
	}
    
	int counter=n;
    c1.total=q2[0].arrival_time;
    c1.total_tat=0;
    c1.total_wait=0;
   
    printf("------------------------------------------------------------------\n");
    while(counter!=0)
    {
    	 
	printf("\nIteration %d ",l++);
    for(i=0;i<n;i++)
    {
    	if(c1.total<q2[i].arrival_time)
		{ 
      int j=0;
			while(c1.total!=q2[i].arrival_time)
      {
				c1.total++;
       int c=0;
       if(i-1>=0)
        {
        rem_bt[j]--;
        if(rem_bt[j]==0)
        {
           turn_around_time[j]=c1.total-q2[j].arrival_time;
           waiting_time[j]=turn_around_time[j]-q2[j].burst_time;
           printf("\nProcess %d Completed at time %d\n",q2[j].process_id,c1.total);
           printf("turn_around_time = %d\n",turn_around_time[j] );
           printf("waiting_time = %d\n",waiting_time[j] );

        }
          c++;
          if(c==quantum)
            j=j+1;
        }
      }
    }
      if(res[i]==0)
      {
      q2[i].response_time=c1.total-q2[i].arrival_time;
     
      res[i]=1;
    }
		
    	

      if(rem_bt[i]!=0)
     {
    	if(rem_bt[i]<=quantum)
    	{
    		while(rem_bt[i]>0)
    		{
    			rem_bt[i]-=1;
    			c1.total+=1;
    		}
        turn_around_time[i]=c1.total-q2[i].arrival_time;
    
    	  waiting_time[i]=turn_around_time[i]-q2[i].burst_time;
      printf("\nProcess %d Completed at time %d\n",q2[i].process_id,c1.total);
     // printf("\n%d      |   %d    |    %d    |    %d    \n",q2[i].process_id,turn_around_time[i],waiting_time[i],c1.total);
      c1.total_tat+=(float)turn_around_time[i];
	    c1.total_wait+=(float)waiting_time[i];
    	counter--;
    	}
     }
    	if(rem_bt[i]>quantum)
    	{    
    		c1.total+=quantum;
    		rem_bt[i]-=quantum;
    	}
    
    }
  }
  printf(" \n\nProcess_id     AT    BT   TAT    WT    RT     \n");
  printf("--------------------------------------------------------\n"); 
  for(i=0;i<n;i++)
     printf (  "  %d      |  %d   |   %d  |   %d  |   %d    |    %d   \n",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time,turn_around_time[i],waiting_time[i],q2[i].response_time );

  printf("\nGiantt Chart Total Time at the end of queue 1 is : %d\n",c1.total);
  printf("\n\nTotal Turnaround time     Total Waiting Time\n");
  printf("--------------------------------------------------------------\n");
  printf("\n     %f               |       %f       \n",c1.total_tat,c1.total_wait);
//	printf("\n\nAvg Turnaround time 		Avg Waiting Time\n");
	printf("--------------------------------------------------------------\n");
//	printf("\n     %f       	      |    		%f       \n",c1.total_tat/n,c1.total_wait/n);
	printf("**************************************************************\n");
	return c1;
}



struct cstruct multilevel2(int set,int n2,int n1,float pwait,float ptat,int ptotal,int p)
 {
	struct pstruct q2[n2];
	struct pstruct key[n2];
	struct cstruct c1;
	int waiting_time[n2];
	int turn_around_time[n2];
  int Priority[n2],fg[n2];
	int i,j;
	srand(time(0));
	int k=2;
	printf("\nCPU scheduling algo to be used in queue %d is FIFO\n",k++);
	for(i=0;i<n2;i++)
	{   
		q2[i].process_id=i; 
		q2[i].arrival_time=rand() % 10 + 1;
		q2[i].burst_time=rand() % 10 + 1;
		waiting_time[i]=0;
		turn_around_time[i]=0;
    Priority[i]=set;
    fg[i]=0;
	}

	printf("\n\nProcess_id     Arrival time     Burst Time       Priority       fg  \n");
	printf("-------------------------------------------------------------------------\n");
	for(i=0;i<n2;i++)
	printf("\n   %d        |    %d        |     %d         |     %d      |      %d    \n",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time,Priority[i],fg[i]);
    
   
   for(i=1;i<n2;i++)
   {
       key[i]=q2[i];
       j = i-1;
 	   while (j >= 0 && q2[j].arrival_time> key[i].arrival_time)
       {
       	   q2[j+1]=q2[j];
           j = j-1;
       }
       q2[j+1] = key[i];
   }
     
    printf("\nAfter Sorting: (P_id,AT,BT)\n");
	for(i=0;i<n2;i++)
	{
		printf("(%d,%d,%d) ",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time);
		
	}
  
  c1.total=ptotal;//time where queue1 finished
     if(q2[0].arrival_time>c1.total)
     {
      while(c1.total!=q2[0].arrival_time)
        c1.total++;//wait till first process of queue2 arrive after queue 1 finishes
     }
    
    
    c1.total+=q2[0].burst_time;
    c1.total_tat=ptat;
    c1.total_wait=pwait;
   printf("\nAfter Sorting: (TAT,WT,Total): (%f ,%f , %d)\n",c1.total_tat,c1.total_wait,c1.total);
  int queue=2;
    printf("\n\nProcess_id        Turnaround Time 	   Waiting Time      Total Time\n");
    printf("-------------------------------------------------------------------------\n");
   
	for(int i=0;i<n2;i++)
	{
		
    turn_around_time[i]=c1.total-q2[i].arrival_time;
    waiting_time[i]=turn_around_time[i]-q2[i].burst_time;
    printf("     %d            |    %d              |     %d             |     %d\n",q2[i].process_id,turn_around_time[i],waiting_time[i],c1.total);
    if(c1.total<q2[i+1].arrival_time)
    {
      while(c1.total!=q2[i+1].arrival_time)
        c1.total++;//waiting till next process comes
    }
    if((i+1)!=n2)
    c1.total=c1.total+q2[i+1].burst_time;
    c1.total_tat+=(float)turn_around_time[i];
    c1.total_wait+=(float)waiting_time[i];
	}
    
  float tat,wt;
  wt=c1.total_wait/p;
  tat=c1.total_tat/p;
	
  printf("Till Queue : %d\n",set );
	printf("Avg Turnaround time 		Avg Waiting Time\n");
	printf("---------------------------------------------------------\n");
	printf("\n     %f      	 |    		%f        \n",tat,wt);
  printf("*******************************************************************************\n");
  
	return c1;
}

