/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] Brody Couture
 * [TERM] FALL 2024
 * 
 ****************************************/
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "symtable.h"
#include "error.h"
#include "hack.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

enum instr_type{
	
	Invalid = -1,
	AType,
	CType,
	
};

typedef struct c_instruction{
	opcode a:1;
	opcode comp:7;
	opcode dest:4;
	opcode jump:4;
}c_instruction;

typedef struct a_instruction{
	union{
		hack_addr address;
		char * label;	
	}type;
	bool is_addr;
} a_instruction;

typedef struct instruction{
	union{
		a_instruction a;
		c_instruction c;
	}instr;
	enum instr_type instruction_type;
} instruction;

/** function prototypes **/
char *strip(char *s);
void parse(FILE * file);
bool is_Atype(const char *);
bool is_label(const char *);
bool is_CType(const char *);
char *extract_label(const char *line, char* label);
void add_predefined_symbols();
bool parse_A_instruction(const char *line, a_instruction *instr);
void parse_C_instruction(char *line, c_instruction *instr);

#endif




