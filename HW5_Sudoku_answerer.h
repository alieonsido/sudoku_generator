#ifndef _SUDOKU_ANSWER
	#define _SUDOKU_ANSWER
#endif

#include <stdint.h>

void* table_answer_columncheck(void*);
void* table_answer_rowcheck(void*);

typedef struct 
{
	uint8_t row;
	uint8_t column;

}sukudu_space_position;