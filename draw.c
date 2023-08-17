#include <ncurses.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<unistd.h>
#include "position.h"

void imprime(WINDOW* win,  struct COMMAND_CHAR* ponteiro, char botao_pressionado){
	int position = 0;
	struct COMMAND_CHAR** current_pos = &ponteiro;
	while(1){
		if((*current_pos)->next == NULL){
			(*current_pos)->pressed_char = botao_pressionado;
			(*current_pos)->next = malloc(sizeof(struct COMMAND_CHAR));
			(*current_pos)->next->next = NULL;
			(*current_pos)->next->pressed_char = NULL;
			mvwaddch(win, 1 , 12+position, (*current_pos)->pressed_char);
			break;
		}
		else{
			mvwaddch(win, 1 , 12+position, (*current_pos)->pressed_char);
			current_pos = &((*current_pos)->next);
			position++;
		}
	}

}

void imprime_sem_botao(WINDOW* win,  struct COMMAND_CHAR* ponteiro){
	int position = 0;
	struct COMMAND_CHAR** current_pos = &ponteiro;
	while(1){
		if((*current_pos)->next == NULL){
			if( ((*current_pos)->pressed_char ) != NULL){
			mvwaddch(win, 1 , 12+position, (*current_pos)->pressed_char);}
			break;
		}
		else{
			mvwaddch(win, 1 , 12+position, (*current_pos)->pressed_char);
			current_pos = &((*current_pos)->next);
			position++;
		}
	}
}
