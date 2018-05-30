// A thread to check that each column contains the digits1 through 9 
// A thread to check that each row contains the digits 1 through 9 
// Nine threads to check that each of the 3×3 subgrids contains the digits 1 through 9

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/time.h>
//#include <sys/shm.h>
//#include <sys/mman.h>
#include "HW5_Sudoku_table.h"
#include "HW5_Sudoku_answerer.h"

#include <fcntl.h>
#include <pthread.h>


//for debug.
void signalhandler_fill();
void signalhandler_check();

void problem_maker();
int problem_optimizer();
void problem_answerer(uint8_t*);
int DIFFICULTY;



// the more space is for random speed and convenient.
// first number is row, second number is column.
int sukudu_table[10][10] = {{},{},{},{},{},{},{},{},{},{}};


int main(int argc, char const *argv[])
{
	uint8_t optimize_complete = 0;
	uint8_t answercomplete=0;
	printf("hello, choose your Difficulty.\n");
	printf("Easy=1 normal=2 hard=3.\n");
	scanf("%d",&DIFFICULTY);

	//time calc
	struct timeval tv_main;
	gettimeofday(&tv_main,NULL);
	double timer,usec;
	usec = ((double)tv_main.tv_usec)/1000000;
	timer = tv_main.tv_sec + usec;


	while(!optimize_complete)
	{
		problem_maker();
		optimize_complete = problem_optimizer();
		//problem_answerer(&answercomplete);
		//answercomplete=1;	
		//optimize_complete = 1;
	}
	
	// printf("after block check:\n");
	table_printer();
	printf("The sukudu game start!\n");

	//time calc
	gettimeofday(&tv_main,NULL);
	usec = ((double)tv_main.tv_usec)/1000000;
	timer = tv_main.tv_sec + usec - timer;
	printf("single-thread time waste: %lf\n",timer);

	
	
	return 0;
}

int problem_optimizer()
{
	pthread_t blocks[9];
	uint8_t status[9];
	int numbercounter[10] = {0};
	uint8_t maxvalue,minvalue,max_number,min_number;
	for (int i = 0; i < 9; i++)
	{
		pthread_create(&blocks[i],NULL,zero_check,(void*)(i+1));
	}
	for (int i = 0; i < 9; i++)
	{
		pthread_join(blocks[i],(void**)&status[i]);
		if(status[i]==0) 
		{
			for (; i < 9; i++)
				pthread_cancel(blocks[i]);
			return 0;
		}
	}

	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			switch(sukudu_table[i][j])
			{
				case 1:
					numbercounter[1]++;
					break;
				case 2:
					numbercounter[2]++;
					break;
				case 3:
					numbercounter[3]++;
					break;
				case 4:
					numbercounter[4]++;
					break;
				case 5:
					numbercounter[5]++;
					break;
				case 6:
					numbercounter[6]++;
					break;
				case 7:
					numbercounter[7]++;
					break;
				case 8:
					numbercounter[8]++;
					break;
				case 9:
					numbercounter[9]++;
					break;
			}
			
		}
	}

	for (int i = 1; i < 10; i++)
	{
		printf("the %d counter is %d\n",i,numbercounter[i]);
		if (numbercounter[i] > maxvalue)
		{
			max_number = i;
			maxvalue = numbercounter[i];	
		}
		if (numbercounter[i] < minvalue)
		{
			min_number = i;
			minvalue = numbercounter[i];
		}
	}
	printf("maxvalue= %d, minvalue = %d \n",maxvalue,minvalue);
	if (( maxvalue >=5 ||minvalue <=1)&& DIFFICULTY != 3)
	{
		return 0;
	}
	if ((maxvalue >=5 || minvalue !=0)&& DIFFICULTY == 3)
	{
		return 0;
	}
	return 1;

}

void problem_maker()
{
	//fill blocks.
	pthread_t nine_block_threadid[9]; // every sukudu is nine block.
	for(int i=0;i<9;i++)
	{
		pthread_create(&nine_block_threadid[i],NULL,table_filler,(void*)(i+1));
		pthread_join(nine_block_threadid[i],NULL);
	}

	//for multi-thread.
		// for(int i=0;i<9;i++)
		// {
		// 	pthread_join(nine_block_threadid[i],NULL);
		// }

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
		pthread_join(column_threadid[i],NULL);
	}

	//for multi thread
		// for (int i = 0; i < 9; i++)
		// {
		// 	pthread_join(column_threadid[i],NULL);
		// }

		// printf("after column check:\n");
		// table_printer();

	for (uint8_t i = 0; i < 9; i++)
	{
		//in every row,check every column.
		//in table, the begin number is 1, not zero.
		pthread_create(&block_threadid[i],NULL,table_checker_block,(void *)(i+1));
		pthread_join(block_threadid[i],NULL);
	}

	// for (int i = 0; i < 9; i++)
	// {
	// 	pthread_join(block_threadid[i],NULL);
	// }
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
