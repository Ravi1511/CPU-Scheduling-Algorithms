#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define RED   "\x1b[31m"
#define RESET "\x1B[0m"
#define GREEN "\x1b[32m"

int finish[]={0,0,0};
struct pstruct
{   
	int process_id;
	int arrival_time;
	int completion_time;
	int burst_time;
	int turn_around_time;

};
struct cstruct
{
float total_wait;
float total_tat;
int total;
float idle_time;
};

int fin(int n)
{
	for(int i=0;i<n;i++)
	{
		if(finish[i]!=1)
		    return 0;
	}
	return 1;
}
//------------------------------------------------------------------------------------
int main()
{
   int n,i,j;
   struct cstruct c1;
   srand(time(0));
   n= rand() % 5+2;
   printf("\nNumber of processes are : %d\n",n);
   struct pstruct q2[n];
   struct pstruct key[n];
   
   int rough[n];
   float total_wait=0;
   float total_tat=0;
   int idle=0;
   
   printf("\nCPU scheduling algo to be used is Pre-emptive SJF\n");
	for(i=0;i<n;i++)
	{   
		q2[i].process_id=i; 
		q2[i].arrival_time=rand() % 10 + 1;
		q2[i].burst_time=rand() % 10 + 1;
		
	}

	printf("\n\nProcess_id     Arrival time     Burst Time  \n");
	printf("---------------------------------------------\n");
	for(i=0;i<n;i++)
	printf("\n   %d        |    %d        |     %d\n",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time);
	
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


   printf("\nAfter Sorting according to arrival time: (P_id,AT,BT)\n");
	for(i=0;i<n;i++)
	{
		printf("(%d,%d,%d) ",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time);
		rough[i]=q2[i].burst_time;
		
	}
	printf("\n*********************************************************");
	printf("\nTime Instance         Process/Idle");
	printf("\n----------------------------------------------");
    //sjf sorting as per arrival time
    int t=q2[0].arrival_time;
    idle=t;
    int less=0;
    int min=0;
    int prev=0;
    int first=1;
    while(fin(n)!=1)
    {
    	printf("\n        %d                 ",t);
    	for(j=0;j<n;j++)
    	{
    		if(finish[j]!=1)
    		{
    			min=j;
    			break;
			}
		}
    	less=-1;
    	for(j=0;j<n;j++)
    	{
    		if(q2[j].arrival_time>t)
    	        break;
    	    else
    	        less++;
		}
		for(j=min;j<=less;j++)
		{
			if(finish[j]!=1)
			{
				if(rough[j]<=rough[min])
			   {
				    min=j;
			   }
			}
			
		}
		if(min>less)
		{
			printf(GREEN"CPU Idle(%d,%d)"RESET,t,t+1);
			idle++;
		}
		else
		{     
		      if(prev!=min&&first!=1)
			  {
			  	printf(RED"P%d pre-empted ,P%d assigned to the CPU"RESET,q2[prev].process_id,q2[min].process_id);
			  }else
			  {
			  	printf("P%d	",q2[min].process_id)	;
			  }
			  if(first==1)
                               first=0;
		      rough[min]--;
		      //printf("%d",q2[min].burst_time);
		      if(rough[min]==0)
		      {
		      	  finish[min]=1;
		      	  q2[min].completion_time=t;
		      	  q2[min].turn_around_time=t-q2[min].arrival_time+1;
			  }
		           
		}
		prev=min;  
    	t=t+1;
	}
    //ends
    printf("\n*********************************************************");
   
    
    
    printf("\n\nProcess ID     Arrival Time     Completion  Time       Turnaround Time 	   Burst Time      Waiting Time \n");
    printf("---------------------------------------------------------------------------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		int waiting_time=q2[i].turn_around_time-q2[i].burst_time;
		total_wait+=waiting_time;
		total_tat+=q2[i].turn_around_time;
		printf("    %d       |      %d	   |       %d	     |	       %d	     |    	  %d	   |	    %d\n",q2[i].process_id,q2[i].arrival_time,q2[i].completion_time,q2[i].turn_around_time,q2[i].burst_time,waiting_time);
	
	}
    
    
	printf("\n\nAvg Turnaround time 		    Avg Waiting Time                   CPU Idle Time\n");
	printf("---------------------------------------------------------------------------------------\n");
	printf("\n     %f       	      |    		%f       |        %d      \n",total_tat/n,total_wait/n,idle);
	printf("***************************************************************************************\n");



	return 0;

}
