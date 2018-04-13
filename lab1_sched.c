/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32164640/ 32162045/ 32161391
*	    Student name : 최수빈/ 백예은/ 노유진 
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

int sec = 0;   //시간 변수
int i, j;      //for문 사용시 쓰는 변수
int queue[size] = { 0 };
int push(int data);
int pop();
int pop2(int index);  //원하는 queue[index] data pop
int front = 0;
int rear = 0;
int scheduling[job_num][size] = { 0 };
char job[5] = { 'A','B','C','D','E' };   //job이름

int push(int data) {

	if ((rear + 1) % size == front) {

		return -1;

	}

	queue[rear] = data;

	rear = ++rear % size;

	return data;

}

int pop() {        //front data pop

	int data;

	if (front == rear) return -1;

	data = queue[front];

	front = ++front % size;

	return data;

}

int pop2(int index) {  //원하는 index의 data pop

	int data;

 

	if (front == rear) return -1;

	data = queue[index];// 인자로 받은 index에 있는 data 구하기

 

	for (i = index; front <= i - 1; i--) {  //큐당기기

		queue[i] = queue[i - 1];

	}

	front = ++front % size;

	return data;

}



 

//FCFS

void FCFS(Program* process) {

	int RP = -1;   // Running Process 초기상태

	for (sec = 0; sec < size; sec++) {

		for (j = 0; j < job_num; j++) {

			if (process[j].arrivalT == sec) {

				push(j);   // level 0인 큐에 삽입

			}

		}

		// 도착한 프로세스 확인

 

		if (RP == -1) RP = pop(); // 첫 프로그램을 큐에서 pop

								  // 큐가 비었을 경우 RP=-1값

		if (process[RP].performT < process[RP].serviceT) {

			// 실행중인 프로세스가 있을 때

			scheduling[RP][sec] = 1;

			process[RP].performT++;

		}

		else {

			// 실행중인 프로세스가 없을 때

			RP = pop();

			if (RP != -1) {

				process[RP].performT++;

				scheduling[RP][sec] = 1;

			}

		}

	}

}

void SJF(Program *process) {

 

	int RP = -1;   // running process 큐에서 pop되어 run상태인 process

	int SJ;   //shortest job

 

	for (sec = 0; sec < size; sec++) {

		for (j = 0; j < job_num; j++) {

			if (process[j].arrivalT == sec)

				push(j);  // 레벨0의 큐에 삽입

		}

 

		if (RP == -1 || process[RP].performT == process[RP].serviceT) {

			RP = pop();

			if (RP >= 0) {  //ready중인 process가 있을 때

				SJ = process[RP].serviceT;

				push(RP);

 

				for (i = front; i < rear; i++) {  //큐 내의 프로세스들 서비스시간 비교

					if (process[queue[i]].serviceT <= SJ) { //서비스시간 제일 짧은 것 구하기

						RP = pop2(i);

						SJ = process[RP].serviceT;

					}

				}

			}

		}

		// 수행중인 프로세스 있을 때

		if (RP >= 0) {

			scheduling[RP][sec] = 1;

			process[RP].performT++;

		}

	}

}

 

void RR(Program *process) {

 

	int RP = -1;   // running process 큐에서 pop되어 run상태인 process

	int TC = 0;     // time check, timeslice만큼 지났는지 체크하는 변수

 

	for (sec = 0; sec < size; sec++) {

		for (j = 0; j < job_num; j++) {

			if (process[j].arrivalT == sec)

				push(j);  // 레벨0의 큐에 삽입

		}

 

		if (RP == -1) RP = pop(); //첫 프로그램을 큐에서 pop

		else if (process[RP].performT == process[RP].serviceT) {  // 수행시간과 서비스 시간 같은지 확인

 

			RP = pop();            // push하지 않고, 새 job pop 하기

			TC = 0;

		}

		else if (TC == TS) { //시간이 timeslice만큼 지나면

			push(RP);              // 수행중이던 RP 큐에 push 하기

			RP = pop();            // 새 job pop 하기, ready중이던 process없다면 이전것이 pop된다

			TC = 0;

		}

 

		// 수행 중인 프로세스가 있을 때

		if (RP >= 0) {

			scheduling[RP][sec] = 1;

			process[RP].performT++;

			TC++;

		}

	}

}

 

void MLFQ(Program *process) {

	Program p[job_num];//Process구조체에 있는 정보들을 변수에 넣음

	Program *q[job_num];//남은 srvtime을 넣음

	Program *que1[size];

	Program *que2[size];

	Program *que3[size];

	int sum = 0;

	sec = 0;

 

	int count1 = 0;//que1에서 1초씩 뽑아내는 변수

	int count2 = 0;

	int count3 = 0;

	int timeslice1 = 0;//que1에서의 timeslice

	int timeslice2 = 0;

	int timeslice3 = 0;

	int q1_t = -1;//que1의 index

	int q2_t = -1;

	int q3_t = -1;

	int num1 = 0;//que1에서의 srvtime-timeslice

	int num2 = 0;

	int num3 = 0;

 

	for (int i = 0; i<job_num; i++) {//Program구조체에 있는 process정보들을 p에 넣음

		p[i] = process[i];

		q[i] = NULL;

		sum += p[i].serviceT;

	}

	for (int i = 0; i<size; i++) {

		que1[i] = NULL;

		que2[i] = NULL;

		que3[i] = NULL;

	}

 

 

 

	printf("timeslice1?");

	scanf("%d", &timeslice1);

	printf("timeslice2?");

	scanf("%d", &timeslice2);

	printf("timeslice3?");

	scanf("%d", &timeslice3);

 

	for (int t = 0; sec<sum; t++) {//sec가 sum이 될때까지 돌게 함

 

		int same = 0;//동시에 들어오는 job check

 

		for (int v = t; v <= sec; v++) {

			for (int k = 0; k<job_num; k++) {//5번의 process를 돌려서 같은도착시간을 갖고 있는 job을 찾음

				if (v == p[k].arrivalT) {//v와 arvtime이 같은 job을 que1에 삽입

					que1[++q1_t] = &p[k];

					same++;

				}

			}

		}

		if (sec - t != 0) {//t와 sec가 차이가 나는것을 방지

			for (int v = 0; v< (sec - t); v++)

				t++;

		}

 

		while (1) {//queue이동, 2번째부터 들어올수 있음 

			if (same == 0 && que2[0] == NULL && que3[0] == NULL) {//모두 빈큐일때 다시 첫큐로 감

				if (q[0]) {

					que1[++q1_t] = q[0];

					q[0] = NULL;

					break;

				}

				break;

			}

			if (q[0]) {

				que2[++q2_t] = q[0];

				q[0] = NULL;

				break;

			}

			if (q[1]) {

				que3[++q3_t] = q[1];

				q[1] = NULL;

				break;

			}

			if (q[2]) {

				que3[++q3_t] = q[2];

				q[2] = NULL;

				break;

			}

			break;

		}

		while (1) {//job이 timeslice만큼 수행

 

			if (que1[count1]) {

				num1 = que1[count1]->serviceT;

				if (num1 - timeslice1 > 0) {//수행시간이 timeslice보다 클 경우

					for (int m = 0; m<timeslice1; m++) {

						scheduling[que1[count1]->key][sec] = 1;

						sec++;//timeslice만큼 수행

					}

					num1 = num1 - timeslice1;

					que1[count1]->serviceT = num1;

					q[0] = que1[count1];//남은 수행시간을 q에 넣음

				}

				else {

					for (int m = 0; m<num1; m++) {

						scheduling[que1[count1]->key][sec] = 1;

						sec++;

					}

				}

				count1++;//수행됐으므로 다음 index에 넣기 위해 더함

				break;

			}//que1

 

			if (que2[count2]) {

				num2 = que2[count2]->serviceT;

				if (num2 - timeslice2 > 0) {

					for (int m = 0; m<timeslice2; m++) {

						scheduling[que2[count2]->key][sec] = 1;

						sec++;//timeslice만큼 수행

					}

					num2 = num2 - timeslice2;

					que2[count2]->serviceT = num2;

					q[1] = que2[count2];

				}

				else {

					for (int m = 0; m<num2; m++) {

						scheduling[que2[count2]->key][sec] = 1;

						sec++;

					}

				}

				count2++;

				break;

			}//que2

 

			if (que3[count3]) {

				num3 = que3[count3]->serviceT;

				if (num3 - timeslice3 > 0) {

					for (int m = 0; m<timeslice3; m++) {

						scheduling[que3[count3]->key][sec] = 1;

						sec++;

					}

					num3 = num3 - timeslice3;

					que3[count3]->serviceT = num3;

					q[2] = que3[count3];

				}

				else {

					for (int m = 0; m<num3; m++) {

						scheduling[que3[count3]->key][sec] = 1;

						sec++;

					}

				}

				count3++;

				break;

			}//que3

			break;

		}//while(1)

 

	}//for(t)

}

 

//lottery

void lottery(Program* process) {

	int RP = -1;

	int winner;

	int tix[job_num];         // 티켓

	int sum = 0;         // priority의 총합

 

	for (i = 0; i < job_num; i++) {

		sum += process[i].priority;

	}

	// priority의 sum구하기

	for (i = 0; i < job_num; i++) {

		tix[i] = process[i].priority*tixSize / sum;

		if (i > 0) tix[i] += tix[i - 1];

	}

	// tix할당

	for (sec = 0; sec < size; sec++) {

		// time 반복

		for (i = 0; i < job_num; i++) {

			if (process[i].arrivalT == sec)

				push(i);

			// 도착하는대로 push

		}

 

		while (1) {

			winner = rand() % tixSize;    // 0부터 tixSize-1까지 범위의 난수생성

			for (i = 0; i <job_num; i++) {

				if (winner < tix[i]) {   // winner의 범위 지정

					RP = pop();

					if (process[RP].serviceT != process[RP].performT) push(RP);   // 수행시간과 서비스시간이 다를 때 push

					break;   // for문 탈출

				}

			}

			// 뽑힌 티켓을 가진 프로세스=RP

			if ((RP != -1) && (process[RP].serviceT != process[RP].performT)) break;

			//

		}

		scheduling[RP][sec] = 1;

		process[RP].performT++;

	}

}

void Show(Program *process) {

	for (i = 0; i < job_num; i++) {

		printf("%c ", job[i]);

 

		for (j = 0; j < size; j++) {

			if (scheduling[i][j]) {

				printf("■");

				scheduling[i][j] = 0; //scheduling 초기화

			}

			else printf("□");

		}

		printf("\n");

		process[i].performT = 0;  //수행한 시간 초기화

	}

	printf("\n");

}
