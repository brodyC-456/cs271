#include <symtable.h>

#define SYMBOL_TABLE_SIZE 1000

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

    int hash(char *str)
    {
        unsigned long hash = 5381;
        int c;
        while((c = *str++)){
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		}
        return hash %= SYMBOL_TABLE_SIZE;
    }
	
	void symtable_insert(char* key, hack_addr addr)
	{
		struct Symbol* newSymbol = (struct Symbol*) malloc(sizeof(struct Symbol));
		newSymbol-> addr = addr;
		newSymbol-> name = strdup(key);
		//get the hash 
		int index = hash(key);
		//move in array until an empty or deleted cell
		while(hashArray[index] != NULL && hashArray[index]->name != NULL) {
		//go to next cell
		++index;
		//wrap around the table
		index %= SYMBOL_TABLE_SIZE;
		}
		hashArray[index] = newSymbol;
	}
	
	struct Symbol *symtable_find(char * key){
		for(int i = 0; i < sizeof(hashArray); i++){
			if(strcmp(key,hashArray[i]->name)){
				return hashArray[i];
			}
		}
		return NULL;
	}
	
	
	void symtable_display_table(){
		int i = 0;
		for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
			if(hashArray[i] != NULL){
				printf(" (%s,%d)",hashArray[i]->name,hashArray[i]->addr);
			}
			else{
				printf(" ~~ ");
			}
		}
		printf("\n");
	}
	
	
   void symtable_print_labels() {
		int i = 0;    
		for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
			if(hashArray[i] != NULL){
				printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
			}
		}
	} 
	