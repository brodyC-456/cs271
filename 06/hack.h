/****************************************
 * Project 6 for CS 271
 * 
 * [NAME] Brody Couture
 * [TERM] FALL 2024
 * 
 ****************************************/

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

typedef enum jump_id
{
	JMP_INVALID = -1,
	JMP_NULL,
	JMP_JGT = 1,
	JMP_JEQ= 2,
	JMP_JGE = 3,
	JMP_JLT = 4,
	JMP_JNE = 5,
	JMP_JLE = 6,
	JMP = 7,
}jump_id;

typedef enum dest_id{
	DEST_INVALID = -1,
	DEST_NULL,
	DEST_M = 1,
	DEST_D = 2,
	DEST_MD = 3,
	DEST_A = 4,
	DEST_AM = 5,
	DEST_AD = 6,
	DEST_AMD = 7,
}dest_id;

typedef enum comp_id{
	
	// When A = 0
	COMP_INVALID = -1,
	COMP_0 = 42,
	COMP_1 = 63,
	COMP_NEG_1 = 58,
	COMP_D = 12,
	COMP_A = 48,
	COMP_NOT_D = 13,
	COMP_NOT_A = 49,
	COMP_NEG_D = 15,
	COM_NEG_A = 51,
	COMP_D_PLUS_1 = 31,
	COMP_A_PLUS_1 = 55,
	COMP_D_MINUS_1 = 14,
	COMP_A_MINUS_1 = 50,
	COMP_D_PLUS_A = 2,
	COMP_D_MINUS_A = 19,
	COMP_A_MINUS_D = 7,
	COMP_D_AND_A = 0,
	COMP_D_OR_A = 21,
	
	// When A = 1
	
	COMP_M = 48,
	COMP_NOT_M = 49,
	COMP_NEG_M = 51,
	COMP_M_PLUS_1 = 55,
	COMP_M_MINUS_1 = 50,
	COMP_D_PLUS_M = 2,
	COMP_D_MINUS_M = 19,
	COMP_M_MINUS_D = 7,
	COMP_D_AND_M = 0,
	COMP_D_OR_M = 21,
}comp_id;

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

static inline jump_id str_to_jumpid(const char *s){
	
	jump_id id = JMP_INVALID;
	if (s == NULL) {
		id = JMP_NULL;
	} 
	else if (strcmp(s, "JGT") == 0){
		id = JMP_JGT;
	}
	else if (strcmp(s, "JEQ") == 0){
		id = JMP_JEQ;
	}
	else if (strcmp(s, "JGE") == 0){
		id = JMP_JGE;
	}
	else if (strcmp(s, "JLT") == 0){
		id = JMP_JLT;
	}
	else if (strcmp(s, "JNE") == 0){
		id = JMP_JNE;
	}
	else if (strcmp(s, "JLE") == 0){
		id = JMP_JLE;
	}
	else if (strcmp(s, "JMP") == 0){
		id = JMP;
	}
	return id;
}

static inline dest_id str_to_destid(const char *s){
	dest_id id = DEST_INVALID;
	if (s == NULL) {
		id = DEST_NULL;
	}
	else if (strcmp(s, "M") == 0){
		id = DEST_M;
	}
	else if (strcmp(s, "D") == 0){
		id = DEST_D;
	}
	else if (strcmp(s, "MD") == 0){
		id = DEST_MD;
	}
	else if (strcmp(s, "A") == 0){
		id = DEST_A;
	}
	else if (strcmp(s, "AM") == 0){
		id = DEST_AM;
	}
	else if (strcmp(s, "AD") == 0){
		id = DEST_AD;
	}
	else if (strcmp(s, "AMD") == 0){
		id = DEST_AMD;
	}
	return id;
}

static inline comp_id str_to_compid(const char *s, int *a){
	comp_id id = COMP_INVALID;
	*a = 0;
	if (strcmp(s, "0") == 0){
		id = COMP_0;
	}
	else if (strcmp(s, "1") == 0){
		id = COMP_1;
	}
	else if (strcmp(s, "-1") == 0){
		id = COMP_NEG_1;
	}
	else if (strcmp(s, "D") == 0){
		id = COMP_D;
	}
	else if (strcmp(s, "A") == 0){
		id = COMP_A;
	}
	else if (strcmp(s, "!D") == 0){
		id = COMP_NOT_D;
	}
	else if (strcmp(s, "!A") == 0){
		id = COMP_NOT_A;
	}
	else if (strcmp(s, "-D") == 0){
		id = COMP_NOT_D;
	}
	else if (strcmp(s, "-A") == 0){
		id = COMP_NOT_A;
	}
	else if (strcmp(s, "D+1") == 0){
		id = COMP_D_PLUS_1;
	}
	else if (strcmp(s, "A+1") == 0){
		id = COMP_A_PLUS_1;
	}
	else if (strcmp(s, "D-1") == 0){
		id = COMP_D_MINUS_1;
	}
	else if (strcmp(s, "A-1") == 0){
		id = COMP_A_MINUS_1;
	}
	else if (strcmp(s, "D+A") == 0){
		id = COMP_D_PLUS_A;
	}
	else if (strcmp(s, "D-A") == 0){
		id = COMP_D_MINUS_A;
	}
	else if (strcmp(s, "A-D") == 0){
		id = COMP_A_MINUS_D;
	}
	else if (strcmp(s, "D&A") == 0){
		id = COMP_D_AND_A;
	}
	else if (strcmp(s, "D|A") == 0){
		id = COMP_D_OR_A;
	}

	
	// A now equals 1
	
	else if(strcmp(s, "M") == 0){
		id = COMP_M;
		*a = 1;
	}
	else if(strcmp(s, "!M") == 0){
		id = COMP_NOT_M;
		*a = 1;
	}
	else if(strcmp(s, "-M") == 0){
		id = COMP_NOT_M;
		*a = 1;
	}
	else if(strcmp(s, "M+1") == 0){
		id = COMP_M_PLUS_1;
		*a = 1;
	}
	else if(strcmp(s, "M-1") == 0){
		id = COMP_M_MINUS_1;
		*a = 1;
	}
	else if(strcmp(s, "D+M") == 0){
		id = COMP_D_PLUS_M;
		*a = 1;
	}
	else if(strcmp(s, "D-M") == 0){
		id = COMP_D_MINUS_M;
		*a = 1;
	}
	else if(strcmp(s, "M-D") == 0){
		id = COMP_M_MINUS_D;
		*a = 1;
	}
	else if(strcmp(s, "D&M") == 0){
		id = COMP_D_AND_M;
		*a = 1;
	}
	else if(strcmp(s, "D|M") == 0){
		id = COMP_D_OR_M;
		*a = 1;
	}
	return id;
}


#endif