/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32164640
*	    Student name : 최수빈 
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm function'definition.
*
*/

#include <aio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#include "lab1_sched_types.h"
#define size 20	//큐 사이즈
int i, j;
int queue[size];
int front=0;
int rear=0;
int isEmpty();
int push(int data);
int pop();

/*
 * you need to implement FCFS, RR, SPN, SRT, HRRN, MLFQ scheduler. 
 */

// queue 구현
int push(int data) {
	if ((rear + 1) % size == front) {
  	return -1;
 	}
 queue[rear] = data;
 rear = ++rear % size;
 return data;
}

int pop() {
	int data;
	if (front == rear) return -1;
data = queue[front];
front = ++front % size;
return data;
}

int isEmpty() {
if (front == rear)
 	 return 1;
return 0;
}


// FCFS
void FCFS(){
	int process[5][2];	// 프로세스의 도착시간과 서비스시간
	int scheduling[5][20];	// 스케줄링- 5개의 프로세스, 20time 스케줄링

	for(int i=0;i<20;i++){
		for(int j=0;j<5;j++){
			if(process[j][0]==i){
				push(j);// 큐에 삽입
			}
			// 도착한 프로세스 확인
			if(!isEmpty()){
				pop();// pop
			}
			else{
				//time++
			}
		}
	}
}
