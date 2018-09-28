#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
};

int queue2(int,int,int*,int *,int,int*,int *,float,float);
int queue3(int,int*,int*,int,int,int*,int *,float,float);

int turn_around_time[100]={0};
int waiting_time[100]={0};
int bt1[100]={0};
int at[100]={0};
int rem_bt[100]={0};
int bt2[100]={0};
int pid[100]={0};

int main()
{
   int n=3,n1,i,t=0,quantum,counter1=0,j=0,l=1;
   struct cstruct c1,c2,c3;
   struct pstruct key[n];

   
   printf("Number of levels in Multi level queue are: %d ",n);
   srand(time(0));
   n1= rand() % 10  ;
   //n1=7;
   printf("\nNumber of processes are : %d\n",n1);
   struct pstruct q2[n1];
   struct pstruct q1[n1];
   struct pstruct q3[n1];
   int Priority[n1];
   
   srand(time(0));
   printf("\nCPU scheduling algo to be used in queue 1 is RR\n");
	for(i=0;i<n1;i++)
	{   
		q2[i].process_id=i; 
		q2[i].arrival_time=rand() % 10 ;
		q2[i].burst_time=rand() % 10 + 1;
		Priority[i]=1;

	}
	
	
	//scanf("%d",&quantum);
  quantum=rand()%3+1;
  printf("quantum : %d",quantum);
    printf("\nProcess_id     Arrival time     Burst Time      Priority \n");
	printf("---------------------------------------------\n");
	for(i=0;i<n1;i++)
	printf("\n   %d        |    %d        |     %d     |     %d    \n",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time,Priority[i]);
   
//-------------------------------------------------------------------------------------
   for(i=1;i<n1;i++)
   {
       key[i]=q2[i];
       j = i-1;
 	   while (j >= 0 && q2[j].arrival_time > key[i].arrival_time)
       {
       	   q2[j+1]=q2[j];
           j = j-1;
       }
       q2[j+1] = key[i];
   }
    
   // printf("\nSorted values in queue 1 : \n");
    for(i=0;i<n1;i++)
	{
//	printf("\n   %d        |    %d        |     %d\n",q2[i].process_id,q2[i].arrival_time,q2[i].burst_time);
		q1[i]=q2[i];
		bt1[i]=q1[i].burst_time;
	}


    c1.total=q2[0].arrival_time;
    c1.total_tat=0;
    c1.total_wait=0;
    waiting_time[0]=q2[0].arrival_time;

    printf("\n\nQUEUE 1 ");
   // printf(" \nprocess_id    AT      BT     TAT       WT      \n");
    for(i=0;i<n1;i++)
    {
    	if(c1.total<q2[i].arrival_time)
		{
			while(c1.total!=q2[i].arrival_time)
				c1.total++;
		}
    	

      if(q1[i].burst_time!=0)
     {
    	if(q1[i].burst_time<=quantum)
    	{
    		while(q1[i].burst_time>0)
    		{
    			q1[i].burst_time-=1;
    			c1.total+=1;
    		}
    	//printf("\nProcess %d Completed at time %d\n",q2[i].process_id,c1.total);
        turn_around_time[i]=c1.total-q2[i].arrival_time;
    	//printf("turn_around_time = %d\n",turn_around_time[i] );
    	if(i!=0)
    	{
    		//printf("tat,bt : %d %d\n",turn_around_time[i],q2[i].burst_time );
    	  waiting_time[i]=turn_around_time[i]-q2[i].burst_time;
    	}
		//printf("waiting_time = %d\n",waiting_time[i] );
	   
       printf (  "  %d      |  %d	|  %d 	|	%d	|	%d	|	%d\n",q1[i].process_id,q1[i].arrival_time,q1[i].burst_time,turn_around_time[i],waiting_time[i] );
        c1.total_tat+=(float)turn_around_time[i];
	    c1.total_wait+=(float)waiting_time[i];
    	}
     }
    	if(q1[i].burst_time>quantum)
    	{    
    		c1.total+=quantum;
    		q1[i].burst_time-=quantum;
    		//printf("\nprocessid,GiantTotal,Remaining_bursttime: ");
    		//printf("(%d,%d,%d) ",q1[i].process_id,c1.total,q1[i].burst_time );
    	}//printf("\n");
    }
//------
    //printf("\n\npid,rem_bt,gianttime,tat,wt: ");
	//for(i=0;i<n1;i++)
		//printf("(%d,%d,%d,%d,%d)  ",q1[i].process_id,q1[i].burst_time,c1.total,turn_around_time[i],waiting_time[i] );
		
  

	printf("\nValue of total time after queue1 = %d",c1.total);
	
	int k=0;
	int b1[n1];
	for ( i = 0; i < n1;i++)
	{    
		 if(q1[i].burst_time>0)
		 {  
		 	q3[k]=q1[i];
		 	b1[k]=bt1[i];
		 	k++;
		 	counter1++;
         }
    } 
    printf("\nProcesses Entering queue 2 remaining: (Process_id,Remaining_bursttime)%d\n",counter1);

	for(i=0;i<counter1;i++)
	{
	printf("(%d,%d),",q3[i].process_id,q3[i].burst_time );
	pid[i]=q3[i].process_id;
    bt2[i]=q3[i].burst_time;//this burst time is will not change
    at[i]=q3[i].arrival_time;
	}
	t=c1.total;
	float tat=c1.total_tat;
	float wait=c1.total_wait;
	printf("\n--------------------------------------\n");
	queue2(n1,counter1,pid,bt2,t,at,b1,tat,wait);

return 0;
}

int queue2(int n1,int counter,int *pid,int *rem_bt,int t,int *at,int *bt1,float tat,float wait)
{   
	struct cstruct c1;
	c1.total=t;
	c1.total_tat=tat;
	c1.total_wait=wait;


	int quantum;
	int i;
	int counter1=0,j=0,l=1;
	struct pstruct q1[counter],q2[counter],q3[counter];
	int turn_around_time[counter];
	int waiting_time[counter];
    int Priority[n1];
	//printf("Enter quantum for queue2 : ");
	//scanf("%d",&quantum);
  quantum=rand()%3+1;
  printf("quantum : %d",quantum);
	printf("\nRemaining BT initially in queue2 : (pid,rem_bt,at,priority)\n");
	printf(" Process_id 	Rem_BT			arrival_time		Priority\n");
	for(i=0;i<counter;i++)
	{
		Priority[i]=2;
    	printf(" %d       |       %d		  |       %d     |       %d   \n",pid[i],rem_bt[i],at[i],Priority[i]);
    	q2[i].process_id=pid[i];
    	q2[i].burst_time=rem_bt[i];
    	q2[i].arrival_time=at[i];
    	q1[i]=q2[i];
    	
	}
    //printf("Counter %d\n",counter);
    printf("\nRemaining_BT After queue2 : ");
    //--
   // printf("\n\nQUEUE 2 ");
   // c1.total=ptotal;
    // if(q2[0].arrival_time>c1.total)
    // {
     // while(c1.total!=q2[0].arrival_time)
      //  c1.total++;
        //c1.total_wait=q2[0].arrival_time;
       // c1.total_tat=ptat;
    // }
    // c1.total+=q2[0].arrival_time;
    printf(" \nProcess_id    AT      BT     TAT       WT      \n");
    for(i=0;i<counter;i++)
    {
    	if(c1.total<q2[i].arrival_time)
		{
			while(c1.total!=q2[i].arrival_time)
				c1.total++;
		}
	    if(q1[i].burst_time!=0)
    {
    	if(q1[i].burst_time<=quantum)
    	{
    		while(q1[i].burst_time>0)
    		{
    			q1[i].burst_time-=1;
    			c1.total+=1;
    		}
    	//printf("\nProcess %d Completed at time %d\n",q2[i].process_id,c1.total);
        turn_around_time[i]=c1.total-q2[i].arrival_time;
    	//printf("turn_around_time = %d\n",turn_around_time[i] );
    	//if(i!=0)
    	  waiting_time[i]=turn_around_time[i]-bt1[i];
		//printf("waiting_time = %d\n",waiting_time[i] );
		 printf (  "  %d      |  %d	 	|	%d	|	%d	|	%d\n",q1[i].process_id,q1[i].arrival_time,q1[i].burst_time,turn_around_time[i],waiting_time[i] );
        c1.total_tat+=(float)turn_around_time[i];
	    c1.total_wait+=(float)waiting_time[i];
    	//counter--;
    	}
      }
    	if(q1[i].burst_time>quantum)
    	{    
    		c1.total+=quantum;
    		q1[i].burst_time-=quantum;
    		//printf("\npid,c1.total,rem_bt: ");
    		//printf("(%d,%d,%d) ",q1[i].process_id,c1.total,q1[i].burst_time);
    	}//printf("\n");
    }
//------
   // printf("\n\npid,rem_bt,t,tat,wt: ");
	/*for(i=0;i<counter;i++)
	{
		printf("(%d,%d,%d,%d,%d)  ",q1[i].process_id,q1[i].burst_time,c1.total,turn_around_time[i],waiting_time[i] );
		
	}*/

	printf("\nValue of total time after queue2 = %d",c1.total);
	//printf("\nEntering queue 3 remaining\n");
	int k=0;
	int b3[counter];
	for ( i = 0; i < counter;i++)
	{    
		 if(q1[i].burst_time>0)
		 {  
		 	q3[k]=q1[i];
		 	b3[k]=bt1[i];
		 	k++;
		    counter1++;
         }
    }
    printf("\nProcesses Entering queue 3 remaining: %d\n",counter1);

    //printf("%d\n",counter1);
	for(i=0;i<counter1;i++)
	{
	//printf("(%d,%d),",q3[i].process_id,q3[i].burst_time);
	pid[i]=q3[i].process_id;
    bt2[i]=q3[i].burst_time;//this burst time is will not change
    at[i]=q3[i].arrival_time;
	}

    t=c1.total;
	tat=c1.total_tat;
	wait=c1.total_wait;

	printf("\n--------------------------------------\n");
	queue3(n1,pid,bt2,t,counter1,at,b3,tat,wait);
	
return 0;
}

int queue3(int n1,int pid[],int bt2[],int t,int counter1,int *at,int *bt1,float tat,float wait)
{ 

	struct cstruct c1;
	struct pstruct q2[counter1];

	c1.total=t;
	c1.total_tat=tat;
	c1.total_wait=wait;
	int priority[n1];

	int i;
	printf("\n");
 	printf("pid   burst time    arrival_time    Burst time remaining   priority\n");

  for(i=0;i<counter1;i++)
  {  
  	    priority[i]=3;
  	 printf("%d |	%d	    | 	 %d	 |	    %d	      |   %d  \n",pid[i],bt2[i],at[i],bt1[i],priority[i]);
        q2[i].process_id=pid[i];
    	q2[i].burst_time=bt2[i];
    	q2[i].arrival_time=at[i];
    	
    	
  }
   
   if(c1.total<q2[0].arrival_time)
		{
			while(c1.total!=q2[0].arrival_time)
				c1.total++;
		}

  //c1.total+=q2[0].burst_time;

   c1.total+=bt2[0];

   printf("\n\n Turnaround Time 	   Waiting Time     		 Total Time\n");
    printf("----------------------------------------------------------------------\n");
	for(i=0;i<counter1;i++)
	{
		turn_around_time[i]=c1.total-q2[i].arrival_time;
		waiting_time[i]=turn_around_time[i]-bt1[i];
		printf("   %d		|		%d		|		%d\n",turn_around_time[i],waiting_time[i],c1.total);
		if(c1.total<q2[i+1].arrival_time)
		{
			while(c1.total!=q2[i+1].arrival_time)
				c1.total++;
		}
		if((i+1)!=counter1)
		c1.total=c1.total+q2[i+1].burst_time;
		c1.total_tat+=(float)turn_around_time[i];
	    c1.total_wait+=(float)waiting_time[i];
	}
     
    
	printf("\n\nAvg Turnaround time 		Avg Waiting Time\n");
	printf("--------------------------------------------------------\n");
	printf("\n     %f       	      |    		%f       \n",c1.total_tat/n1,c1.total_wait/n1);
	printf("*********************************************************\n");

return 0;
}





