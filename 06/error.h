/****************************************
 * Project 6 for CS 271
 * 
 * [NAME] Brody Couture
 * [TERM] FALL 2024
 * 
 ****************************************/

#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

enum exitcode{
    EXIT_INCORRECT_ARGUMENTS=1,
	EXIT_CANNOT_OPEN_FILE=2,
	EXIT_TOO_MANY_INSTRUCTIONS=3,
	EXIT_INVALID_LABEL=4,
	EXIT_SYMBOL_ALREADY_EXISTS=5,
	EXIT_INVALID_A_INSTR=6,
	EXIT_INVALID_C_DEST=7,
	EXIT_INVALID_C_COMP=8,
	EXIT_INVALID_C_JUMP=9,
};

void exit_program(enum exitcode code, ...);


#endif