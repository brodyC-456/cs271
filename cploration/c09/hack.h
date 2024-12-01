#ifndef __HACK_H__
#define __HACK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#define NUM_PREDEFINED_SYMBOLS 23

typedef enum symbol_id {
	R0 = 0,
	R1 = 1,
	R2 = 2,
	R3 = 3,
	R4 = 4,
	R5 = 5,
	R6 = 6,
	R7 = 7,
	R8 = 8,
	R9 = 9,
	R10 = 10,
	R11 = 11,
	R12 = 12,
	R13 = 13,
	R14 = 14,
	R15 = 15,
	SCREEN = 16384,
	KBD = 24576,
	SP = 0,
	LCL = 1,
	ARG = 2,
	THIS = 3,
	THAT = 4,
}symbol_id;

typedef struct predefined_symbol{
	char name[10000];
	int16_t address;
}predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
    {"R0", R0}, 
    {"R1", R1}, 
    {"R2", R2}, 
    {"R3", R3}, 
    {"R4", R4}, 
    {"R5", R5}, 
    {"R6", R6}, 
    {"R7", R7}, 
    {"R8", R8}, 
    {"R9", R9}, 
    {"R10", R10}, 
    {"R11", R11}, 
    {"R12", R12}, 
    {"R13", R13}, 
    {"R14", R14}, 
    {"R15", R15}, 
    {"SCREEN", SCREEN}, 
    {"KBD", KBD}, 
    {"SP", SP}, 
    {"LCL", LCL}, 
    {"ARG", ARG},
    {"THIS", THIS}, 
    {"THAT", THAT},
};

#endif