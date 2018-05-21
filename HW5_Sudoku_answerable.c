// A thread to check that each column contains the digits1 through 9 
// A thread to check that each row contains the digits 1 through 9 
// Nine threads to check that each of the 3×3 subgrids contains the digits 1 through 9

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
//#include <sys/shm.h>
//#include <sys/mman.h>
#include "HW5_Sudoku_table.h"
#include "HW5_Sudoku_answerer.h"

#include <fcntl.h>
#include <pthread.h>

void* sukudu_position_judge(void*);

//for debug.
void signalhandler_fill();
void signalhandler_check();

void problem_maker();
void problem_answerer(uint8_t*);



// the more space is for random speed and convenient.
// first number is row, second number is column.
int sukudu_table[10][10] = {{},{},{},{},{},{},{},{},{},{}};


int main(int argc, char const *argv[])
{
	uint8_t answercomplete=0;
	while(!answercomplete)
	{
		problem_maker();
		problem_answerer(&answercomplete);
		
	}
	
	// printf("after block check:\n");
	table_printer();
	printf("The sukudu game start!\n");

	
	return 0;
}


void problem_maker()
{
	//fill blocks.
	pthread_t nine_block_threadid[9]; // every sukudu is nine block.
	for(int i=0;i<9;i++)
	{
		pthread_create(&nine_block_threadid[i],NULL,table_filler,NULL);
	}
	for(int i=0;i<9;i++)
	{
		pthread_join(nine_block_threadid[i],NULL);
	}

	// printf("before check:\n");
	// table_printer();
	
	//check blocks:
	//at this point, the sukudu table is not true.
	//so, we need to move the space of block.
	//we juse need to check 6 spaces, 
	//because 3 spaces are fixed.


	//Warning:when check blocks, we can use-- 
	//or, RECOMMAND to use multi-threading,
	//but, when we want to WRITE something on table, 
	//we ONLY can use single-thread, or the value will wrong.
	
	
	pthread_t block_threadid[9];
	pthread_t column_threadid[9];


	for (uint8_t i = 0; i < 9; i++)
	{
		//in every row,check every column.
		//in table, the begin number is 1, not zero.
		pthread_create(&column_threadid[i],NULL,table_checker_column,(void *)(i+1));
	}

	for (int i = 0; i < 9; i++)
	{
		pthread_join(column_threadid[i],NULL);
	}

	// printf("after column check:\n");
	// table_printer();

	for (uint8_t i = 0; i < 9; i++)
	{
		//in every row,check every column.
		//in table, the begin number is 1, not zero.
		pthread_create(&block_threadid[i],NULL,table_checker_block,(void *)(i+1));
	}

	for (int i = 0; i < 9; i++)
	{
		pthread_join(block_threadid[i],NULL);
	}
}

void problem_answerer(uint8_t* answercomplete)
{
	//for player.
	pthread_t row[9];
	pthread_t column[9];
	pthread_t blocks[9];
	
	uint8_t status = 0;

	for (uint8_t i = 0; i < 9; i++)
	{
		pthread_create(&blocks[i],NULL,table_answer_columncheck,(void*)i);
	}
	for (uint8_t i = 0; i < 9; i++)
	{
		pthread_join(row[i],(void**)&status);
		if (status==1)
		{
			*answercomplete=0;
			break; // all program need to reset.
		}
		else if(status==0)
		{
			*answercomplete=1;
		}
	}
	
}
