/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32164640/ 32162045/ 32161391
*	    Student name: 최수빈/ 백예은/ 노유진
*
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm test code.
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

/*
 * you need to implement scheduler simlator test code.
 *
 */


#define job_num 5
#define size 20
#define tixSize 100
#define TS 4 //RR timeslice 는 4초

int main(int argc, char *argv[]){
   
	int num = 0; //  메뉴 선택 변수

 

	int mlfq[job_num][size];

	Program process[job_num];

 

	for (int i = 0; i < job_num; i++) {   //도착시간과 서비스시간 입력받으며, MLFQ와 동기화

		scanf("%d", &process[i].arrivalT);

		scanf("%d", &process[i].serviceT);

		scanf("%d", &process[i].priority);

		process[i].performT = 0;

		process[i].key = i;

 

		for (int j = 0; j < 20; j++) { //MLFQ용 scheduling 초기화

			mlfq[i][j] = 0;

		}

	}

 

 

	while (1) {

 

		printf("1.FCFS 2.SJF 3.RR 4.MLFQ 5.Lottery (그 외 종료) ");

		scanf("%d", &num);

 

		switch (num)

		{

		case 1: FCFS(process);

			Show(process);

			break;

		case 2: SJF(process);

			Show(process);

			break;

		case 3: RR(process);

			Show(process);

			break;

		case 4: MLFQ(process, mlfq);

			break;

		case 5: lottery(process);

			Show(process);

			break;

		default:

			return 0;

		}

	}

}

