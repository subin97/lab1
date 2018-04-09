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
#define size 20
#define tixSize 100

int job[3]={0.5,0.2,0.3};   // 각 job이 가진 확률값
int tix[3];                 // 티켓(총 100개)
int random;                 // 수행해야할 프로세스

int i, j;
int queue[5][size];
int isEmpty();
int push(int data);
int pop();
int front = 0;
int rear = 0;
int level;  //큐의 level
char job[5]={'A','B','C','D','E'};
   
/*
 * you need to implement FCFS, RR, SPN, SRT, HRRN, MLFQ scheduler. 
 */

// 큐에서 해당 index를 매개변수로 받아와서 pop하는 함수
// 
int push(int level, int data) {
    if ((rear + 1) % size == front) {
        return -1;
    }
    queue[level][rear] = data;
    rear = ++rear % size;
    return data;
}
int pop(int level) {
    int data;
    if (front == rear) return -1;
    data = queue[level][front];
    front = ++front % size;
    return data;
}
int isEmpty() {
    if (front == rear)
        return 1;
    return 0;
}

void FCFS() {
    int process[5][2];  // 프로세스의 도착시간과 서비스시간
    int scheduling[5][20] = {0};    // 스케줄링 - 5개의 프로세스, 20 time 스케줄링
    int a;
    for (i = 0;i < 20;i++) {
        for (j = 0;j < 5;j++) {
            if (process[j][0] == i) {
                push(0,j);  // 레벨0의 큐에 삽입
            }
        }
        // 도착한 프로세스 확인

        if (!isEmpty()) {
            // 큐가 비어있지 않고 실행중인 프로세스가 없을 때 pop
            ///// 조건추가하기!!
            a=pop(0);
            scheduling[a][i] = 1;
        }
        
    }
}
// 중요도(확률)값 입력 따로 받기
int lottery(int job[]){
    int sum;
    for(i=0;job[i];i++){
        sum+=job[i];
        tix[i]=job[i]/sum*tixSize;
        if(i>0)
            tix[i]+=tix[i-1];
    }
    while(/*시간*/){
        srand(time(NULL));
        random = rand() % tixSize;    // 0부터 tixSize-1까지 범위의 난수생성
        for(i=0;i<3;i++){
            if (random<=tix[i]){
                push(0,i);  // 스케줄링할 job을 ready queue에 push
                break;
                // job이 하나가 종료되면 나머지만 실행하게 하기
            }
        }
    }
    //return random;
}

