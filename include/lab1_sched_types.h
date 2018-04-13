/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id :32164640 / 32162045 / 32161391 
*	    Student name : 최수빈 / 백예은 / 노유진
*
*   lab1_sched_types.h :
*       - lab1 header file.
*       - must contains scueduler algorithm function's declations.
*
*/

#ifndef _LAB1_HEADER_H
#define _LAB1_HEADER_H

//상수들
#define job_num 5  //수행할 job 개수
#define size 20    //실행해 보일 시간 최대 20초
#define tixSize 100  //티켓 개수
#define TS 4       //RR timeslice 는 4초


//구조체
typedef struct{    //program 구조체
	int arrivalT; //도착시간
	int serviceT;  //서비스시간
	int performT; // 앞서 수행한 시간
	int priority;  //lottery 우선순위
	int key;
}Program;


//함수들
int push(int data);
int pop();
int pop2(int index);
void FCFS(Program* process);
void SJF(Program* process);
void RR(Program* process);
void MLFQ(Program* process);
void lottery(Program* process);
void Show(Program *process);


#endif /* LAB1_HEADER_H*/



