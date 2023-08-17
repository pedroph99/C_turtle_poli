#include <ncurses.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<unistd.h>
#include "position.h"

void create_string (WINDOW * window, char * string, int size_string, int col_start){
	for(int x = 0; x<size_string; x++){
		mvwaddch(window, 1 , col_start+x, string[x]);
	}
}

//remove the last char digited
void remove_char(WINDOW* win,  struct COMMAND_CHAR* ponteiro){
	int position = 0;
	struct COMMAND_CHAR** current_pos = &ponteiro;
	while(1){
		if((*current_pos)->next->next == NULL){
			free((*current_pos)->next->next);
			(*current_pos)->next = NULL;
			(*current_pos)->pressed_char = NULL;
			break;
		}
		else{
			mvwaddch(win, 1 , 12+position, (*current_pos)->pressed_char);
			current_pos = &((*current_pos)->next);
			position++;
		}
	}
}

//function that returns the size of the linked list.
int tamanho_lista(WINDOW* win,  struct COMMAND_CHAR* ponteiro){
	int size = 1;
	struct COMMAND_CHAR** current_pos = &ponteiro;
	while(1){
		if((*current_pos)->next == NULL){
			return 0;
		}
		if((*current_pos)->next->next == NULL){
			return size;
			break;
		}
		else{
			size++;
			current_pos = &((*current_pos)->next);
		}
	}
}

// função que preenche um array alocado dinamicamente.
void catch_characters(char* digited_chars, struct COMMAND_CHAR* ponteiro){
	int size = 0;
	struct COMMAND_CHAR** current_pos = &ponteiro;
	while(1){

		if((*current_pos)->next == NULL){
			break;
		}

		if((*current_pos)->next->next == NULL){
			digited_chars[size]= (*current_pos)->pressed_char;
			break;
		}

		else{
			digited_chars[size]= (*current_pos)->pressed_char;
			size++;
			current_pos = &((*current_pos)->next);
		}
	}
}
