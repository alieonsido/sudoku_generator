#include "HW5_Sudoku_table.h"
#include "HW5_Sudoku_answerer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>

//allocate memory space.
//sukudu_space_position *data = (sukudu_space_position*)malloc(sizeof(sukudu_space_position));

extern int sukudu_table[10][10];
int sukutu_table_bruteforce[10][10];


void* table_answer_columncheck(void* row_number)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);

	uint8_t number=(uint8_t)row_number;
	uint8_t answertable[10]={};
	uint8_t checknumber;

	//printf("begin to fill answertable\n");

	for (int i = 1; i < 10; i++)
	{
		answertable[i] = i;	
	}

	// if there are repeated number, need to clean initial.
	for (int i = 1; i < 10; i++)
	{
		for(checknumber = 1; checknumber < 10; checknumber++)
		{
			if(answertable[checknumber]==sukudu_table[number][i])
				answertable[checknumber]=0;
		}
		
	}

		pthread_exit((void*)1); //status is 1, and it's error.	
	
	pthread_exit((void*)0);

}
void* table_answer_rowcheck(void* column_number)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);

}