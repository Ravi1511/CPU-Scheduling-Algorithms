#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct pstruct
{   
	int process_id;
	int arrival_time;
	int burst_time;

};

struct cstruct
{
float total_wait;
float total_tat;
int total;
float idle_time;
};
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
   int waiting_time[n];
   int turn_around_time[n];
   printf("\nCPU scheduling algo to be used is SJF\n");
	for(i=0;i<n;i++)
	{   
		q2[i].process_id=i; 
		q2[i].arrival_time=rand() % 30 + 1;
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
		
	}
    //sjf sorting as per arrival time
    int t=q2[0].arrival_time+q2[0].burst_time;
    int less=0;
    struct pstruct temp1;
    int min=0;
    for(i=1;i<n;i++)
    {
    	less=min=i;
    	for(j=i;j<n;j++)
    	{
    		if(q2[j].arrival_time>t)
    	        break;
    	    else
    	        less++;
		}
		//printf("\nless=%d",less);
		for(j=i;j<less;j++)
		{
			if(q2[j].burst_time<q2[min].burst_time)
			{
				min=j;
			}
		}
			temp1.process_id=q2[i].process_id;
			q2[i].process_id=q2[min].process_id;
			q2[min].process_id=temp1.process_id;
			
			temp1.arrival_time=q2[i].arrival_time;
			q2[i].arrival_time=q2[min].arrival_time;
			q2[min].arrival_time=temp1.arrival_time;
			
			temp1.burst_time=q2[i].burst_time;
			q2[i].burst_time=q2[min].burst_time;
			q2[min].burst_time=temp1.burst_time;
    	t=t+q2[i].burst_time;
	}
    //ends
    printf("\nAfter Sorting according to burst time: (P_id,AT,BT)\n");
	for(i=0;i<n;i++)
	{
		printf("(%d,%d,%d) ",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time);
		
	}
	int temp=q2[0].arrival_time;
	waiting_time[0]=q2[0].arrival_time;
    c1.total=temp+q2[0].burst_time;
    c1.total_tat=0;
    c1.total_wait=0;
    q2[n].arrival_time=0;
    c1.idle_time=temp;
    
    
    printf("\n\nArrival Time       	 Completion  Time            Turnaround Time 	         Burst Time             Waiting Time \n");
    printf("---------------------------------------------------------------------------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		turn_around_time[i]=c1.total-q2[i].arrival_time;
		waiting_time[i]=turn_around_time[i]-q2[i].burst_time;
		
		printf("   %d	    |		%d		|		%d		|		%d		|		%d\n",q2[i].arrival_time,c1.total,turn_around_time[i],q2[i].burst_time,waiting_time[i]);
		if(c1.total<q2[i+1].arrival_time)
		{
			while(c1.total!=q2[i+1].arrival_time)
			{
				c1.total++;
				c1.idle_time++;
			}
				
		}
		if((i+1)!=n)
		c1.total=c1.total+q2[i+1].burst_time;
		c1.total_tat+=(float)turn_around_time[i];
	    c1.total_wait+=(float)waiting_time[i];
	}
    
    
	printf("\n\nAvg Turnaround time 		    Avg Waiting Time                   CPU Idle Time\n");
	printf("---------------------------------------------------------------------------------------\n");
	printf("\n     %f       	      |    		%f       |        %f       \n",c1.total_tat/n,c1.total_wait/n,c1.idle_time);
	printf("***************************************************************************************\n");



	return 0;

}
