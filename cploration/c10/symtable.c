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
	
void symtable_insert(char* key, hack_addr address){
    struct Symbol* new_Symbol = (struct Symbol*)malloc(sizeof(struct Symbol));
    if(new_Symbol == NULL){
        puts("failure to allocate symbol");
    }
    //we use the key, and store the address at the key's hashed index
    int index = hash(key);
    new_Symbol->name = strdup(key);
    new_Symbol->addr = address;
    while(hashArray[index] != NULL && hashArray[index]->name != NULL){
       ++index;
       index %= SYMBOL_TABLE_SIZE; 
    }
    hashArray[index] = new_Symbol;
}
	
	struct Symbol *symtable_find(char * key){
		int index = hash(key);
		for(int i = 0; i < SYMBOL_TABLE_SIZE; i++){
			int probe = (index + i)%SYMBOL_TABLE_SIZE;
			if(hashArray[probe] != NULL && strcmp(key,hashArray[probe]->name) == 0){
				return hashArray[probe];
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
		for(int i = 0; i<SYMBOL_TABLE_SIZE; i++) {
			if(hashArray[i] != NULL){
				printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
			}
		}
	} 
	
	
	