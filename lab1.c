#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c){
    return c == ' ' || c == '\t';
 
}

/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space).
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c){
    return c != ' ' || c == '\t';

}

/* Returns a pointer to the first character of the next
   space-separated word*/ 
char *word_start(char* str){
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

// counts the number of words or tokens
int count_tokens(char* str){
    int counter = 0;
	
    while(*str != '\0'){ 
        if (delim_character(*str)){ // counts up if the given string passes the delim_character method with true
            counter++;
        }
		str++;
    }
    counter++;
    return counter;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char *copy_str(char *inStr, short len){
    char* copy = (char*) malloc(len * sizeof(char)); //new vector to copy the tokens into
	
    for (int i = 0; i < len; i++) {//loop to copy the given inStr (startWord) into the new copy array
        copy[i] = *inStr;
        inStr++;
    }

    return copy;

}

char** tokenize(char* str) {
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

void print_all_tokens(char** tokens){ // just printing through pointers
	int i = 0;
	char **temp = tokens; // temporary token location
	while(*temp != NULL){
		printf("\nTokens[%d]: %s",i++,*temp);
		temp++;
	}
}

int main()
{
    char* str = (char*) malloc(1000 * sizeof(char)); 
	printf("Please enter string to tokenize: \n");
	fgets(str, 1000, stdin);// scan into str max size 1000
    print_all_tokens(tokenize(str));
	return 0;
}
