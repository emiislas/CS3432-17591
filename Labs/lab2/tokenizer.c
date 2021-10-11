#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Return true if c is a whitespace characer
   ('\t' or ' ').*/
bool delim_character(char c)
{
	return c == '\t' || c == ' ' || c == '(' || c == 'X';
}

/* Return true if c is a non-whitespace
   character */
bool non_delim_character(char c)
{
	return c != '\t' && c != ' ' && c != '(' && c != 'X';
}

char *word_start(char* str)
{
	while(delim_character(*str)){
		str++;
	}
	return str;
}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){
	while(non_delim_character(*str)){
		str++;
	}
	return str;
}

int count_tokens(char* str)
{
	int counter = 0;
	while(*str != '\0'){
		if(delim_character(*str)){
			counter++;
		}

		str++;
	}
	counter++;
	return counter;
}

char *copy_str(char *inStr, short len)
{
	char* copy = (char*) malloc(len * sizeof(char));
	for(int i = 0; i < len; i++){
		copy[i] = *inStr;
		inStr++;
	}
  
	return copy;
}

char** tokenize(char* str)
{
	int i = 0;
    int tokenAmmount = count_tokens(str); // get total number of tokens
    char** tokens = (char**) malloc(tokenAmmount * sizeof(char*)); // final token pointer with proper size
    char* startWord = word_start(str); // pointer to first word_start
    char* endWord  = end_word(startWord); // pointer to the end of the previous start word
	
    while(i<tokenAmmount){// copy tokens into new final token
        tokens[i]  = copy_str(startWord, endWord-startWord); // fill tokens with the copy 
        startWord = word_start(endWord);
        endWord  = end_word(startWord);
		i++;
    }
    return tokens;
}

void print_all_tokens(char** tokens, int limit)
{
	int i = 0;
	while(i < limit){
		printf("Tokens[%d]: %s\n", i, tokens[i]);
		i++;
	}
  
}