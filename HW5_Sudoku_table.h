#ifndef _SUDOKU_TABLE
	#define _SUDOKU_TABLE
#endif
#include <stdint.h>

//about table
void* table_filler();
void* table_checker_column(void*);
void* table_checker_block(void*);
void table_cleaner_block(
	uint8_t block_startposition_row,
	uint8_t block_endposition_row,
	uint8_t block_startposition_column,
	uint8_t block_endposition_column);
void* zero_check(void *);
int zero_checker(uint8_t block_startposition_row,
				uint8_t block_endposition_row,
				uint8_t block_startposition_column,
				uint8_t block_endposition_column);

void table_printer();

//about random.
void random_table_norepeat(uint8_t*);
uint8_t random_int_1_9();
