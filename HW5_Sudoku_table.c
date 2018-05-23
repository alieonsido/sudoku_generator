#include "HW5_Sudoku_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>

extern int sukudu_table[10][10];
extern int DIFFICULTY;
int zero_counter = 0;

int zero_checker(uint8_t block_startposition_row,
				uint8_t block_endposition_row,
				uint8_t block_startposition_column,
				uint8_t block_endposition_column)
{
	int difficulty=0;
	uint8_t zeroflag = 0;
	switch(DIFFICULTY)
	{
		case 1:
			difficulty=3;
			break;
		case 2:
			difficulty=5;
			break;
		case 3:
			difficulty=7;
			break;

	}
	uint8_t local_table[10][10]={}; //don't forget our arrary begin from 1.
	for (int i = block_startposition_row; i < block_endposition_row; i++)
	{
		for (int j = block_startposition_column; j < block_endposition_column; j++)
		{
			if(sukudu_table[i][j]==0)
			{
				zeroflag++;
				zero_counter++;
			}
		}
	}
	if (zero_counter <=65) 
	//maybe too many information, 
	//this will let question be invaild.
	{
		for (int i = 0; i < difficulty*10; i++)
		{
			sukudu_table[block_startposition_row][random_int_1_9()]=0;
		}
		printf("Re-random\n");
		return 1;
	}
	if(zeroflag>=8)
		return 0;
}

void* zero_check(void* block_number)
{
	int number = (int)block_number;
	switch(number)
	{
		case 1:
		{
			pthread_exit((void*)zero_checker(1,4,1,4));
		}
		case 2:
		{
			pthread_exit((void*)zero_checker(4,7,1,4));
		}
		case 3:
		{
			pthread_exit((void*)zero_checker(7,10,1,4)); 
		}
		case 4:
		{
			pthread_exit((void*)zero_checker(1,4,4,7)); 
		}
		case 5:
		{
			pthread_exit((void*)zero_checker(4,7,4,7)); 
		}
		case 6:
		{
			pthread_exit((void*)zero_checker(7,10,4,7)); 
		}
		case 7:
		{
			pthread_exit((void*)zero_checker(1,4,7,10)); 
		}
		case 8:
		{
			pthread_exit((void*)zero_checker(4,7,7,10)); 
		}
		case 9:
		{
			pthread_exit((void*)zero_checker(7,10,7,10)); 
		}
	}
}

void table_cleaner_block(uint8_t block_startposition_row,
						 uint8_t block_endposition_row,
						 uint8_t block_startposition_column,
						 uint8_t block_endposition_column)
{
	uint8_t local_table[10][10]={}; //don't forget our arrary begin from 1.
	for (int i = block_startposition_row; i < block_endposition_row; i++)
			{
				for (int j = block_startposition_column; j < block_endposition_column; j++)
				{
					local_table[i][j]=sukudu_table[i][j];
				}
			}
			for(uint8_t fixposition_row=block_startposition_row; fixposition_row<block_endposition_row;fixposition_row++)
			{
				for (uint8_t fixposition_column = block_startposition_column; fixposition_column < block_endposition_column; fixposition_column++)
				{
					for (int i = block_startposition_row; i < block_endposition_row; i++)
					{
						for (int j = block_startposition_column; j < block_endposition_column; j++)
						{
							if(fixposition_row==i && fixposition_column==j)
								continue;
							if(local_table[i][j]==sukudu_table[fixposition_row][fixposition_column])
								sukudu_table[i][j]=0;
						}
					}
				}
				
			}
}


void* table_checker_block(void* block_number)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
	uint8_t number=(uint8_t)block_number;
	
	
	switch(number)
	{
		case 1:
		{
			table_cleaner_block(1,4,1,4);
			break;
		}
		case 2:
		{
			table_cleaner_block(4,7,1,4);
			break;
		}
		case 3:
		{
			table_cleaner_block(7,10,1,4);
			break;
		}
		case 4:
		{
			table_cleaner_block(1,4,4,7);
			break;
		}
		case 5:
		{
			table_cleaner_block(4,7,4,7);
			break;
		}
		case 6:
		{
			table_cleaner_block(7,10,4,7);
			break;
		}
		case 7:
		{
			table_cleaner_block(1,4,7,10);
			break;
		}
		case 8:
		{
			table_cleaner_block(4,7,7,10);
			break;
		}
		case 9:
		{
			table_cleaner_block(7,10,7,10);
			break;
		}
	}

}

void* table_checker_column(void* column_number)
{

	// for row_threadid[9], column_number means row position.
	// so that column_threadid[9], column_number means column position.

	// if I don't mind errorspace.

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);

	uint8_t number=(uint8_t)column_number;
	//fix upper left block.
	uint8_t local_table[10]={};

	for (int i = 1; i < 10; i++)
	{
		local_table[i]=sukudu_table[i][number];
	}

	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			if(i!=j) 
			{
				if(sukudu_table[i][number]==local_table[j])
				sukudu_table[i][number]=0;
			}
			
		}
	}
	

}



void* table_filler(void* row_number) // fill all and clean.
{
	uint8_t generator_number;
	uint8_t numbertable[10] = {0,1,0,0,0,0,0,0,0,0};
	int number = (int)row_number;

	random_table_norepeat(numbertable); //finish for random table.
	//row first
	for (int j=1; j<10; j++)
	{
		sukudu_table[number][j] = numbertable[j];
	}

	random_table_norepeat(numbertable); // reset to born.
	

}



void table_printer()
{
	//print by stdout.

	printf("--------------------------------\n");//print Line and wrap.
	
	for (int i = 1; i < 4; i++)
	{
		printf("|");
		for (int j = 1; j < 4; j++)
		{
			printf(" %d ",sukudu_table[i][j]);
		}
		printf("|");
		for (int j = 4; j < 7; j++)
		{
			printf(" %d ",sukudu_table[i][j]);
		}
		printf("|");
		for (int j = 7; j < 10; j++)
		{
			printf(" %d ",sukudu_table[i][j]);
		}
		printf("|\n");
		printf("--------------------------------\n");
	}
	printf("--------------------------------\n");
	for (int i = 4; i < 7; i++)
	{
		printf("|");
		for (int j = 1; j < 4; j++)
		{
			printf(" %d ",sukudu_table[i][j]);
		}
		printf("|");
		for (int j = 4; j < 7; j++)
		{
			printf(" %d ",sukudu_table[i][j]);
		}
		printf("|");
		for (int j = 7; j < 10; j++)
		{
			printf(" %d ",sukudu_table[i][j]);
		}
		printf("|\n");
		printf("--------------------------------\n");
	}
	printf("--------------------------------\n");
	for (int i = 7; i < 10; i++)
	{
		printf("|");
		for (int j = 1; j < 4; j++)
		{
			printf(" %d ",sukudu_table[i][j]);
		}
		printf("|");
		for (int j = 4; j < 7; j++)
		{
			printf(" %d ",sukudu_table[i][j]);
		}
		printf("|");
		for (int j = 7; j < 10; j++)
		{
			printf(" %d ",sukudu_table[i][j]);
		}
		printf("|\n");
		printf("--------------------------------\n");
	}

}

void random_table_norepeat(uint8_t* numbertable)
{
	for (int i = 1; i < 10; i++)
	{
		numbertable[i] = random_int_1_9(); 
		for (int j = 0; j < i; j++) 
		{
			if(numbertable[j]!=numbertable[i])
			{
				//do nothing
			}
			else
			{
				i--; //because of the number is repeated.
				//reset to born random value.
				break;
			}
		}
	}
}

uint8_t random_int_1_9()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return ( ( ( ((rand()^(tv.tv_usec)*1000000))%10 )+1 )%10 ); //get from 1 to 9.
}


void signalhandler_fill()
{
	printf("Warning:I have fill error");
	while(1)
	{

	}
}

void signalhandler_check()
{
	printf("Warning:I have check error");
	while(1)
	{

	}
}