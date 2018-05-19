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

void* table_checker_block(void* block_number)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
	uint8_t number=(uint8_t)block_number;
	uint8_t local_table[10][10]={}; //don't forget our arrary begin from 1.
	
	switch(number)
	{
		case 1:
		{
			for (int i = 1; i < 4; i++)
			{
				for (int j = 1; j < 4; j++)
				{
					local_table[i][j]=sukudu_table[i][j];
				}
			}
			for(uint8_t fixposition_row=1; fixposition_row<4;fixposition_row++)
			{
				for (uint8_t fixposition_column = 1; fixposition_column < 4; fixposition_column++)
				{
					for (int i = 1; i < 4; i++)
					{
						for (int j = 1; j < 4; j++)
						{
							if(fixposition_row==i && fixposition_column==j)
								continue;
							if(local_table[i][j]==sukudu_table[fixposition_row][fixposition_column])
								sukudu_table[i][j]=0;
						}
					}
				}
				
			}
			break;
		}
		case 2:
		{
			for (int i = 4; i < 7; i++)
			{
				for (int j = 1; j < 4; j++)
				{
					local_table[i][j]=sukudu_table[i][j];
				}
			}
			for(uint8_t fixposition_row=4; fixposition_row<7;fixposition_row++)
			{
				for (uint8_t fixposition_column = 1; fixposition_column < 4; fixposition_column++)
				{
					for (int i = 4; i < 7; i++)
					{
						for (int j = 1; j < 4; j++)
						{
							if(fixposition_row==i && fixposition_column==j)
								continue;
							if(local_table[i][j]==sukudu_table[fixposition_row][fixposition_column])
								sukudu_table[i][j]=0;
						}
					}
				}
				
			}
			break;
		}
		case 3:
		{
			for (int i = 7; i < 10; i++)
			{
				for (int j = 1; j < 4; j++)
				{
					local_table[i][j]=sukudu_table[i][j];
				}
			}
			for(uint8_t fixposition_row=7; fixposition_row<10;fixposition_row++)
			{
				for (uint8_t fixposition_column = 1; fixposition_column < 4; fixposition_column++)
				{
					for (int i = 7; i < 10; i++)
					{
						for (int j = 1; j < 4; j++)
						{
							if(fixposition_row==i && fixposition_column==j)
								continue;
							if(local_table[i][j]==sukudu_table[fixposition_row][fixposition_column])
								sukudu_table[i][j]=0;
						}
					}
				}
				
			}
			break;
		}
		case 4:
		{
			for (int i = 1; i < 4; i++)
			{
				for (int j = 4; j < 7; j++)
				{
					local_table[i][j]=sukudu_table[i][j];
				}
			}
			for(uint8_t fixposition_row=1; fixposition_row<4;fixposition_row++)
			{
				for (uint8_t fixposition_column = 4; fixposition_column < 7; fixposition_column++)
				{
					for (int i = 1; i < 4; i++)
					{
						for (int j = 4; j < 7; j++)
						{
							if(fixposition_row==i && fixposition_column==j)
								continue;
							if(local_table[i][j]==sukudu_table[fixposition_row][fixposition_column])
								sukudu_table[i][j]=0;
						}
					}
				}
				
			}
			break;
		}
		case 5:
		{
			for (int i = 4; i < 7; i++)
			{
				for (int j = 4; j < 7; j++)
				{
					local_table[i][j]=sukudu_table[i][j];
				}
			}
			for(uint8_t fixposition_row=4; fixposition_row<7;fixposition_row++)
			{
				for (uint8_t fixposition_column = 4; fixposition_column < 7; fixposition_column++)
				{
					for (int i = 4; i < 7; i++)
					{
						for (int j = 4; j < 7; j++)
						{
							if(fixposition_row==i && fixposition_column==j)
								continue;
							if(local_table[i][j]==sukudu_table[fixposition_row][fixposition_column])
								sukudu_table[i][j]=0;
						}
					}
				}
				
			}
			break;
		}
		case 6:
		{
			for (int i = 7; i < 10; i++)
			{
				for (int j = 4; j < 7; j++)
				{
					local_table[i][j]=sukudu_table[i][j];
				}
			}
			for(uint8_t fixposition_row=7; fixposition_row<10;fixposition_row++)
			{
				for (uint8_t fixposition_column = 4; fixposition_column < 7; fixposition_column++)
				{
					for (int i = 7; i < 10; i++)
					{
						for (int j = 4; j < 7; j++)
						{
							if(fixposition_row==i && fixposition_column==j)
								continue;
							if(local_table[i][j]==sukudu_table[fixposition_row][fixposition_column])
								sukudu_table[i][j]=0;
						}
					}
				}
				
			}
			break;
		}
		case 7:
		{
			for (int i = 1; i < 4; i++)
			{
				for (int j = 7; j < 10; j++)
				{
					local_table[i][j]=sukudu_table[i][j];
				}
			}
			for(uint8_t fixposition_row=1; fixposition_row<4;fixposition_row++)
			{
				for (uint8_t fixposition_column = 7; fixposition_column < 10; fixposition_column++)
				{
					for (int i = 1; i < 4; i++)
					{
						for (int j = 7; j < 10; j++)
						{
							if(fixposition_row==i && fixposition_column==j)
								continue;
							if(local_table[i][j]==sukudu_table[fixposition_row][fixposition_column])
								sukudu_table[i][j]=0;
						}
					}
				}
				
			}
			break;
		}
		case 8:
		{
			for (int i = 4; i < 7; i++)
			{
				for (int j = 7; j < 10; j++)
				{
					local_table[i][j]=sukudu_table[i][j];
				}
			}
			for(uint8_t fixposition_row=4; fixposition_row<7;fixposition_row++)
			{
				for (uint8_t fixposition_column = 7; fixposition_column < 10; fixposition_column++)
				{
					for (int i = 4; i < 7; i++)
					{
						for (int j = 7; j < 10; j++)
						{
							if(fixposition_row==i && fixposition_column==j)
								continue;
							if(local_table[i][j]==sukudu_table[fixposition_row][fixposition_column])
								sukudu_table[i][j]=0;
						}
					}
				}
				
			}
			break;
		}
		case 9:
		{
			for (int i = 7; i < 10; i++)
			{
				for (int j = 7; j < 10; j++)
				{
					local_table[i][j]=sukudu_table[i][j];
				}
			}
			for(uint8_t fixposition_row=7; fixposition_row<10;fixposition_row++)
			{
				for (uint8_t fixposition_column = 7; fixposition_column < 10; fixposition_column++)
				{
					for (int i = 7; i < 10; i++)
					{
						for (int j = 7; j < 10; j++)
						{
							if(fixposition_row==i && fixposition_column==j)
								continue;
							if(local_table[i][j]==sukudu_table[fixposition_row][fixposition_column])
								sukudu_table[i][j]=0;
						}
					}
				}
				
			}
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

void* sukudu_position_judge(void* position)
{
	//lalallalalalalallalal
}

void* table_filler() // fill all and clean.
{
	uint8_t generator_number;
	uint8_t numbertable[10] = {0,1,0,0,0,0,0,0,0,0};

	random_table_norepeat(numbertable); //finish for random table.
	//row first
	for(int i=1;i<10;i++)
	{
		for (int j=1; j<10; j++)
		{
			sukudu_table[i][j] = numbertable[j];
		}

		random_table_norepeat(numbertable); // reset to born.
	}

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
				i--; //reset to born random value.
				break;
			}
		}
	}
}

uint8_t random_int_1_9()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return ( ( ( ((rand()^tv.tv_sec)^(rand()^tv.tv_sec))%10 )+1 )%10 ); //get from 1 to 9.
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