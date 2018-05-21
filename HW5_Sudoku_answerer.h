#ifndef _SUDOKU_ANSWER
	#define _SUDOKU_ANSWER
#endif

#include <stdint.h>

void* table_answer_columncheck(void*);
void* table_answer_rowcheck(void*);
void table_block_check();

typedef struct 
{
	uint8_t row;
	uint8_t column;

}sukudu_space_position;