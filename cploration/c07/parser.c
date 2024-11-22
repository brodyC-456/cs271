/****************************************
 * C-ploration 7 for CS 271
 * 
 * [NAME] Brody Couture
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"

#define MAX_LINE_LENGTH  200

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	

	// your code here
	char s_new[strlen(s) + 1];
	int i = 0;
	
	for(char *s2 = s; *s2; s2++){
		
		if(*s2 == '/' && *(s2+1) == '/'){
			break;
		}
		else if(!isspace(*s2)){
			s_new[i++] = *s2;
		}
		
	}
	s_new[i] = '\0';
	strcpy(s, s_new);
	return s;
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
 
 
void parse(FILE * file){
	
	// your code here
	char line[MAX_LINE_LENGTH] = {0};
	char label[MAX_LABEL_LENGTH];
	unsigned int instruction_num = 0;
	
	//char inst_type = 'D';
	
	while (fgets(line, sizeof(line), file)){		
		//inst_type = 'D';
		strip(line);
		if(!*line){
			continue;
		}
		if(is_Atype(line)){
			//inst_type = 'A';
			instruction_num++;
		}
		if(is_CType(line)){
			//inst_type = 'C';
			instruction_num++;
		}
		if(is_label(line)){
			//inst_type = 'L';
			extract_label(line, label);
			strcpy(line, label);
			symtable_insert(line, instruction_num);
			
		}
		//printf("%c  %s\n", inst_type, line);
	}
	
}

bool is_Atype(const char *line){
	if(line[0] == '@'){
		return true;
	}
	else{
		return false;
	}
}

bool is_label(const char *line){
	int i = 0;
	while(line[i] != '\0'){
		i++;
	}
	if(line[0] == '(' && line[i - 1] == ')'){
		return true;
	}
	else{
		return false;
	}
}

bool is_CType(const char *line){
	if(!is_Atype(line) && !is_label(line)){
		return true;
	}
	else{
		return false;
	}
}

char *extract_label(const char *line, char* label){
		int i = 0;
		while(line[i] != ')' && line[i] != '\0'){
			i++;
		}
		strncpy(label, line+1, i-1);
		label[i-1] = '\0';
		return label;
}


