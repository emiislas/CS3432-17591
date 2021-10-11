#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char** tokens);
void print_regs();
bool equal(char str1[], char str2[]);
char** make_token(char instruction[]);

int regd; //dest
int reg1; //register 1
int reg2; //register 2
int imm;  // immediate value
int address; //current address
char* mem = "mem.txt"; 

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}


/*
This method takes in an array of tokens, each token is a segment of the current instruction,
If the token at index 0 is either ADD, ADDI, LW, or SW it will interpret the 
instruction and return true.
If it not any of the listed instructions it will only return false.*/

bool interpret(char** token){
	

	if(equal(token[0], "ADD")){ 
		regd = atoi(token[1]); 
		reg1 = atoi(token[2]);
		reg2 = atoi(token[3]); 
			
		reg[regd] = reg[reg1] + reg[reg2]; 
		
	}

	else if(equal(token[0], "ADDI")){
		regd = atoi(token[1]);
		reg1 = atoi(token[2]); 
		imm = atoi(token[3]);
			
		reg[regd] = reg[reg1] + imm; 
		
	}

	else if(equal(token[0], "LW")){
		regd = atoi(token[1]); 
		reg1 = atoi(token[2]);
		imm = atoi(token[3]); 
			
		address = reg[reg1] + imm; 
		
		int32_t read = read_address(address, mem);
		
		reg[regd] = read; 
		
	}

	else if(equal(token[0], "SW")){
		regd = atoi(token[1]); 
		reg1 = atoi(token[2]);
		imm = atoi(token[3]);
			
			
		address = reg[reg1] + imm; 
		
		write_address(reg[regd], address, mem); 
		
		
	}
	else {
		printf("Incorrect Input\n");
		return false;
	}
	return true;
}


/*This method prints the array of registers given*/
void print_regs(){
    int col_size = 10;
    for(int i = 0; i < 8; i++){
        printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
        printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
        printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
        printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
    }
}
//compare strings
bool equal(char str1[], char str2[]){
	
	int i = 0;
	while(str1[i] != '\0'){
		if(str1[i] != str2[i]){
			return false;
		}
		i++;
	}
	return true; 
}



/*
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}
*/

int main(){
	
	init_regs(); 
	print_regs();
	char input[16];
	char** tokens;
	bool term = true;
	
	while(term){
		
		printf("Input instructions (Only Caps): ");
		fgets(input, sizeof(input), stdin);
		
		tokens = tokenize(input);
		term = interpret(tokens); //main function
		
		if(term){
			print_regs();
		}
	}

	return 0;
}