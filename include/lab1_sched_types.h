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


/*
 * You need to Declare functions in  here
 */
typedef struct {
	int arrivalT;
	int serviceT;
	int performT; // 앞서 수행한 시간
	int priority;
	int key;
}Program; //MLFQ외 나머지 구조체
int push(int data);
int pop();
int pop2();
void FCFS(Program* process);
void SJF(Program* process);
void RR(Program* process);
void MLFQ(Program* process, int(*mlfq)[20]);
void lottery(Program* process);
void Show(Program *process);


#endif /* LAB1_HEADER_H*/



