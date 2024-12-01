/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] Brody Couture
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"

int main(int argc, const char *argv[])
{		

	if (argc != 2) {
		// incorrect number of arguments
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);        
	}  
	FILE *fin = fopen( argv[1], "r" );
	if(fin == NULL){ 
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}
	
	parse(fin);
	symtable_print_labels();
	fclose(fin);
	
			
}


