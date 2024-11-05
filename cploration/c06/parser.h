/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] Brody Couture
 * [TERM] FALL 2024
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2

/** function prototypes **/
char *strip(char *s);
void parse(FILE * file);
bool is_Atype(const char *);
bool is_label(const char *);
bool is_CType(const char *);
char *extract_label(const char *line, char* label);

typedef int16_t hack_addr;
typedef int16_t opcode;

enum instr_type{
	
	Invalid = -1;
	AType;
	CType;
	
}

typedef struct c_instruction{
	opcode a:1;
	opcode comp:6;
	opcode dest:3;
	opcode jump:3;
}

typedef struct a_instruction{
	union type{
		hack_addr address;
		char *label;
	};
	bool is_addr;
}

typedef struct instruction{
	union instr{
		a_instruction;
		c_instruction;
	}
	instr_type instruction_type;
}




