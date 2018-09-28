#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

//------------------Main Begins Here---------------------------------------
int main()
{
   //int n=3;
   int i,j,l=1,quantum,k=0;
   struct cstruct c1;
   int rem_bt[100]={0};

   srand(time(0));//each time program run will create different random numbers
   int n=rand()%10+1;
   printf("\nNumber of processes are : %d\n",n);
   if(n==0)
   {
   	printf("No Process in read queue..Exiting Now\n");
   	exit(0);
   }

   struct pstruct q2[n];//stores process parameters
   struct pstruct key[n];
   int waiting_time[n];//waiting_time=(turn_around_time-Burst_time)
   int turn_around_time[n];//turn_around_time=(Completion time - Arrival time)
   c1.total=0;//giantt chart starting
   int res[n];

   printf("\nCPU scheduling algo to be used is Round Robin\n");
	for(i=0;i<n;i++)
	{   
		q2[i].process_id=i; 
		q2[i].arrival_time=rand() % 10 + 0;//process can arrive any time earlier than 10
		q2[i].burst_time=rand() % 10 + 1;//burstime for each process varies between 1 to 9
	  q2[i].response_time=0;
    res[i]=0;
  }

	//printf("Enter quantum : ");
	//scanf("%d",&quantum);
  quantum=rand()%3+1;
  printf("quantum : %d ",quantum);

	printf("\n\nProcess_id     Arrival time     Burst Time  \n");
	printf("----------------------------------------------------\n");
	for(i=0;i<n;i++)
	printf("\n   %d         |     %d        |     %d\n",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time);
	
	/*printf("\nRemaining_Burst Time initially : ");
    for(i=0;i<n;i++)
    	printf("%d ",q2[i].burst_time);
     */
     
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

  
  //initially remaining burst time = burst time of process
   for(i=0;i<n;i++)
	{
	rem_bt[i]=q2[i].burst_time;
	}
    

    int counter=n;//will iterate till all processes finishes 
    c1.total=q2[0].arrival_time;
    c1.total_tat=0;
    c1.total_wait=0;
   // waiting_time[0]=q2[0].arrival_time;
   // waiting_time[0]=0;
   // q2[0].response_time=q2[0].arrival_time;
   
  // printf(" \nProcess_id    AT      BT     TAT       WT      RT     \n");
    printf("--------------------------------------------------------\n"); 
    while(counter!=0)
    {
    	 
	printf("\n\nIteration %d ",l++);
    for(i=0;i<n;i++)
    {  
       
    	if(c1.total<q2[i].arrival_time)
		{
      int j=0;
			while(c1.total!=q2[i].arrival_time)
      {
				c1.total++;//Untill next process arrives,giantt chart will increase with no process in it
		    //new update
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
     printf("\nResponse time for process_id %d is = %d\n",q2[i].process_id,q2[i].response_time );
      res[i]=1;
    }
      //res[i]=c1.total-q2[i].arrival_time;
      if(rem_bt[i]!=0)//Process already finished do not take part again
     {
    	if(rem_bt[i]<=quantum)//if remaining_Bt is less than quantum,then process is going to finish in this iteration
    	{
    		while(rem_bt[i]>0)//This is done because remaining_Bursttime need not be multiple of quanta
    		{
    			rem_bt[i]-=1;
    			c1.total+=1;
    		}

    	printf("\nProcess %d Completed at time %d\n",q2[i].process_id,c1.total);
        turn_around_time[i]=c1.total-q2[i].arrival_time;
    	//printf("turn_around_time = %d\n",turn_around_time[i] );
    	//if(i!=0)//We have calulated before loop for i=0
       // {
         // printf("tat,bt= %d %d\n",turn_around_time[i],q2[i].burst_time );
    	  waiting_time[i]=turn_around_time[i]-q2[i].burst_time;
     // }
		//printf("waiting_time = %d\n",waiting_time[i] );
    //printf("Response time = %d\n",q2[i].response_time );
     //  printf (  "  %d      |  %d   |   %d  |   %d  |   %d    |    %d   \n",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time,turn_around_time[i],waiting_time[i],q2[i].response_time );
        c1.total_tat+=(float)turn_around_time[i];
	    c1.total_wait+=(float)waiting_time[i];
    	counter--;
    	}
     }
    	if(rem_bt[i]>quantum)//if rem_bt is greater than quanta then process will come again in next iteration
    	{    
    		c1.total+=quantum;
    		rem_bt[i]-=quantum;
    		printf("\nprocess_id,Gantt_total,Remaining_bursttime: ");
    		printf("(%d,%d,%d) ",q2[i].process_id,c1.total,rem_bt[i] );
    	}
    }
  }
  printf(" \nProcess_id     AT    BT   TAT    WT    RT     \n");
  printf("--------------------------------------------------------\n"); 
  for(i=0;i<n;i++)
     printf (  "  %d      |  %d   |   %d  |   %d  |   %d    |    %d   \n",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time,turn_around_time[i],waiting_time[i],q2[i].response_time );

    printf("\nGiantt Chart Ends at time : %d\n",c1.total);
	printf("\n\nAvg Turnaround time 		Avg Waiting Time\n");
	printf("--------------------------------------------------------\n");
	printf("\n     %f       	      |    		%f       \n",c1.total_tat/n,c1.total_wait/n);
	printf("*********************************************************\n");
	return 0;
}