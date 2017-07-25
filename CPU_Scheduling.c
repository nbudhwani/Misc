#include <stdio.h>
#include <stdlib.h>
//Priority levels assigned to queues within struct
//Time quantum assigned to queue 2 within queue2Struct

typedef struct{ 
	int id, arrivalTime, burstTime, waitTime, remainingTime;
	int queue1PriorityLevel;
}queue1Struct; 

typedef struct{ 
	int arrivalTime, burstTime, waitTime, remainingTime, flag;
	int queue2PriorityLevel;
}queue2Struct; 

typedef struct{ 
	int arrivalTime, burstTime, id, waitTime;
	int queue3PriorityLevel;
}queue3Struct; 

int getQueueNumber(int level){ 
	if (level == 2){return 1;} 
	else if (level == 3){return 2;}
	else{return 3;}
} 

int main(){
	 char sentence[1000];
  	 FILE *filePointer;

     filePointer = fopen("program.txt", "w");
     if(filePointer == NULL){
      printf("Error!");
      exit(1);
     }

	//Create 3 ready queues

	int n = 10; 				//allocate 10 processes in each queue
	queue1Struct queue1[10];
	queue2Struct queue2[10];
	queue3Struct queue3[10];

	//assign priority levels and queue numbers
	for (int i=0;i<n;i++)queue1[i].queue1PriorityLevel = 2;
	for (int i=0;i<n;i++)queue2[i].queue2PriorityLevel = 3;
	for (int i=0;i<n;i++)queue3[i].queue3PriorityLevel = 1;

	//Create processes for queue 1
	queue1[0].burstTime = 10;
	queue1[1].burstTime = 5;
	queue1[2].burstTime = 7;
	queue1[3].burstTime = 20;
	queue1[4].burstTime = 17;
	queue1[5].burstTime = 9;
	queue1[6].burstTime = 3;
	queue1[7].burstTime = 11;
	queue1[8].burstTime = 15;
	queue1[9].burstTime = 1;

	//Create processes for queue 2
	queue2[0].burstTime = 10;
	queue2[1].burstTime = 5;
	queue2[2].burstTime = 7;
	queue2[3].burstTime = 20;
	queue2[4].burstTime = 17;
	queue2[5].burstTime = 9;
	queue2[6].burstTime = 3;
	queue2[7].burstTime = 11;
	queue2[8].burstTime = 15;
	queue2[9].burstTime = 1;

	//Create processes for queue 3
	queue3[0].burstTime = 10; 
	queue3[1].burstTime = 5; 
	queue3[2].burstTime = 7;  
	queue3[3].burstTime = 20;
	queue3[4].burstTime = 17; 
	queue3[5].burstTime = 9; 
	queue3[6].burstTime = 3;   
	queue3[7].burstTime = 11; 
	queue3[8].burstTime = 15;
	queue3[9].burstTime = 1; 

	//Execute the top-most priority queue which is queue 2 at priority level 3
	//Round Robin with time quantum 5

	printf("---------Now executing queue 2 with Round Robin---------\n");
    fprintf(filePointer,"---------Now executing queue 2 with Round Robin---------\n");

	//initialize remaining time
	for(int i=0; i<n; i++){
		queue2[i].remainingTime = queue2[i].burstTime;
	}

	//initialize arrival time flags
	for (int i=0; i<n; i++){
		queue2[i].flag = 0;
	}
	
	int time = 0; //we start at time = 0
	int timeQuantum = 5; 
	int	thisTurnaroundTime = 0;
	int processesRemaining = n;
	for (int i = 0; processesRemaining > 0; i++){
		if (queue2[i].remainingTime <= timeQuantum && queue2[i].remainingTime > 0){ //process is less than time quantum
			//set arrival time flag
			if (queue2[i].flag == 0){
				queue2[i].arrivalTime = time;
				printf("Order of processes: Starting to execute process number %d at time %d seconds \n", i+1,time);
			    fprintf(filePointer,"Order of processes: Starting to execute process number %d at time %d seconds \n", i+1,time);
				queue2[i].flag = 1;
			}
			//process will be completed in this time quantum
			queue2[i].waitTime = time; //assign wait time to current time
			time += queue2[i].remainingTime; //increase time
			queue2[i].remainingTime = 0; //complete job
			processesRemaining--;

			thisTurnaroundTime = time - queue2[i].arrivalTime;
			printf("   Finished executing process number %d with a turnaround time of %d seconds \n",i+1,thisTurnaroundTime);
		    fprintf(filePointer,"   Finished executing process number %d with a turnaround time of %d seconds \n",i+1,thisTurnaroundTime);
		}

		else if (queue2[i].remainingTime > 0){
			if (queue2[i].flag == 0){
				queue2[i].arrivalTime = time;
				printf("Order of processes: Starting to execute process number %d at time %d seconds \n", i+1,time);
			    fprintf(filePointer,"Order of processes: Starting to execute process number %d at time %d seconds \n", i+1,time);
				queue2[i].flag = 1;
			}
			queue2[i].remainingTime -= timeQuantum;
			time += timeQuantum;
		}
		if (i==n-1){i=-1;} //reset counter
	}


	printf("\n\n---------Now executing queue 1 with FCFS---------\n");
	fprintf(filePointer,"\n\n---------Now executing queue 1 with FCFS---------\n");

	//Execute the second-most-top priority queue which is queue 1 at priority level 2
	//First Come First Serve

	//calculate total time needed to execute
	for (int i=0; i<n; i++){
		time += queue1[i].burstTime;
	}

	//individual waiting time
	queue1[0].waitTime = 0; //wait time for first process is 0
	printf("Wait time for process %d is %d seconds \n", 1, queue1[0].waitTime);
	fprintf(filePointer,"Wait time for process %d is %d seconds \n", 1, queue1[0].waitTime);
	for (int i=1; i<n; i++){
		queue1[i].waitTime = 0;
		for (int j=0; j<i; j++){
			queue1[i].waitTime += queue1[j].burstTime;
		}
		printf("Wait time for process %d is %d seconds \n", i+1, queue1[i].waitTime);
		fprintf(filePointer,"Wait time for process %d is %d seconds \n", i+1, queue1[i].waitTime);
	}

	//average waiting time
	int averageWaitingTime = 0;
	for (int i=0; i<n; i++){
		averageWaitingTime += queue1[i].waitTime;
	}
	averageWaitingTime /= n;
	printf("Average waiting time is %d seconds\n ", averageWaitingTime);
	fprintf(filePointer,"Average waiting time is %d seconds\n ", averageWaitingTime);

	averageWaitingTime = 0;
	printf("\n\n---------Now executing queue 3 with SJF---------\n");
	fprintf(filePointer,"\n\n---------Now executing queue 3 with SJF---------\n");

	//Execute lowest priotity queue which is queue 3 at priority 1
	//Shortest Job First
	//Assign ids
	for (int i=0; i<n; i++){
		queue3[i].id = i+1;
	}

	//Sort burst times 
	int minIndex;
	int tempBurst = 0;
	int tempid = 0;
	int k;

	//BUBBLE SORT
	for (int x = 0; x<n; x++){
		for (int z = 0; z<n-1; z++){
			if (queue3[z].burstTime > queue3[z+1].burstTime){
				tempBurst = queue3[z+1].burstTime;
				tempid = queue3[z+1].id;
				queue3[z+1].burstTime = queue3[z].burstTime;
				queue3[z+1].id = queue3[z].id;
				queue3[z].burstTime = tempBurst;
				queue3[z].id = tempid;
			}
		}
	}

	queue3[0].waitTime = 0; //wait time for first process is 0 

	//List order of processes executed
	int thisID = 0;
	for (int i=0; i<n; i++){
		time += queue3[i].burstTime;
		printf("Order of processes: Process number %d to be executed is process %d with burst time %d seconds \n",i+1,queue3[i].id, queue3[i].burstTime);
		fprintf(filePointer,"Order of processes: Process number %d to be executed is process %d with burst time %d seconds \n",i+1,queue3[i].id, queue3[i].burstTime);
	}

	int j;
	for (int i=0; i<n; i++){
		queue3[i].waitTime = 0;
		for (j=0; j<i; j++){
			queue3[i].waitTime += queue3[j].burstTime;
		}
		printf("Waiting Time for process %d is %d seconds \n",i+1, queue3[i].waitTime);
		fprintf(filePointer,"Waiting Time for process %d is %d seconds \n",i+1, queue3[i].waitTime);
	}

	//Calculate average waiting time
	for (int i=0; i<n; i++){
		averageWaitingTime += queue3[i].waitTime;
	}
	averageWaitingTime /= n;
	printf("Average waiting time is %d seconds\n", averageWaitingTime);
	fprintf(filePointer,"Average waiting time is %d seconds\n", averageWaitingTime);


	printf("\n\n---------Total Time---------\n");
	fprintf(filePointer,"\n\n---------Total Time---------\n");
	printf("\nTotal time to execute all 3 queues is %d seconds\n",time);
	fprintf(filePointer,"\nTotal time to execute all 3 queues is %d seconds\n",time);

    fclose(filePointer);

	return 0;
}