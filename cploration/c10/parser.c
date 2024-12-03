/****************************************
 * C-ploration 10 for CS 271
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
	instruction instr;
	char line[MAX_LINE_LENGTH] = {0};
	char label[MAX_LABEL_LENGTH];
	//char inst_type = 'D';
	unsigned int line_num = 0;
	unsigned int instruction_num = 0;
	add_predefined_symbols();
	
	while (fgets(line, sizeof(line), file)){	
	
		line_num++;
		//inst_type = 'D';
		strip(line);
		
		if(!*line){
			continue;
		}
		
		if(is_label(line)){
			//inst_type = 'L';
			strcpy(line, extract_label(line, label));
			
			if(isalpha(label[0]) == 0){
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			}
			else if(symtable_find(label) != NULL){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			}
			symtable_insert(label, instruction_num);
			continue;
		}
		
		if(is_Atype(line)){
			if (!parse_A_instruction(line, &instr.instr.a)){
				exit_program(EXIT_INVALID_A_INSTR, line_num, line);
			}
			instr.instruction_type = AType;
			//inst_type = 'A';
		}
		if(is_CType(line)){
			//inst_type = 'C';
		}
		
		
		//printf("%u: %c  %s\n", instruction_num, inst_type, line);
		instruction_num++;
		if(instruction_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
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

void add_predefined_symbols(){
	for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
		struct predefined_symbol sym = predefined_symbols[i];
		symtable_insert(sym.name, sym.address);
	}
}

bool parse_A_instruction(const char *line, a_instruction *instr){
    char* s = malloc(strlen(line)*sizeof(char));
    strcpy(s, line+1);
    for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
        if(strcmp(s, predefined_symbols[i].name) == 0){
            instr->is_addr = true;
            instr-> type.address = predefined_symbols[i].address;
            free(s);
            return true;
        }
    }

    char* s_end = NULL;
    long result = strtol(s, &s_end,10);

    if(s == s_end){
        instr->is_addr = false;
        instr->type.label = malloc(strlen(s)*sizeof(char) + 1);
        strcpy(instr->type.label, s);
    } else if(*s_end != 0){
        free(s);
        return false;
    } else{
        instr->is_addr = true;
        instr->type.address = result;
    }
    
    free(s);
    return true;
}

void parse_C_instruction(char *line, c_instruction *instr){
	
	char* token;
	char* jump;
	char* dest;
	char* comp;
	
	// Creating strings for every segment
	token = strtok(line, ";");
	jump = strtok(NULL, ";");
	dest = strtok(token, "=");
	comp = strtok(NULL, "=");
	
	if(comp == NULL){
		comp = dest;
		dest = NULL;
	}
	
	instr-> jump = jump ? str_to_jumpid(jump) : JMP_NULL;
	instr-> dest = dest ? str_to_destid(dest) : DEST_NULL;
	instr-> comp = str_to_compid(comp, &a);
}




