// A thread to check that each column contains the digits1 through 9 
// A thread to check that each row contains the digits 1 through 9 
// Nine threads to check that each of the 3×3 subgrids contains the digits 1 through 9

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <math.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/time.h>

#include <fcntl.h>
#include <pthread.h>

void* sukudu_position_judge(void*);

//for debug.
void signalhandler_fill();
void signalhandler_check();


//about table
void* table_filler();
void* table_checker_column(void*);
void* table_checker_block(void*);
void table_printer();

//about random.
void random_table_norepeat(uint8_t*);
uint8_t random_int_1_9();

typedef struct 
{
	uint8_t row;
	uint8_t column;

}sukudu_space_position;


// the more space is for random speed and convenient.
// first number is row, second number is column.
static int sukudu_table[10][10] = {{},{},{},{},{},{},{},{},{},{}};


int main(int argc, char const *argv[])
{
	printf("The sukudu fill start!\n");
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

	// printf("after block check:\n");
	table_printer();

	printf("The sukudu game start!\n");
	printf("plz to check.");

	//for player.
	sukudu_space_position data;
	return 0;
}

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