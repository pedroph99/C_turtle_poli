#include <ncurses.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<unistd.h>
#include "menu.h"
#include "quit.h"


void create_string (WINDOW * window, char * string, int size_string, int col_start){
	for(int x = 0; x<size_string; x++){
		mvwaddch(window, 1 , col_start+x, string[x]);
	}
}
//Cria um struct para ser armazenado as posições. Utilizando a estrutura de dados lista ligada.
struct POSITION
    {
		int row_position;
		int col_position;
		struct POSITION* next;
};
struct COMMAND_CHAR{
	char pressed_char;
	struct COMMAND_CHAR* next;
};

void cria_posicao(WINDOW * win, int row_pos, int col_pos, struct POSITION* ponteiro){
	struct POSITION** current_pos = &ponteiro;
	while(1){
		if((*current_pos)->next == NULL){
			(*current_pos)->row_position = row_pos;
			(*current_pos)->col_position = col_pos;
			(*current_pos)->next = malloc(sizeof(struct POSITION));
			break;
		}
		else{
			// it avoids the unecessary use of memory;
			if((*current_pos)->row_position == row_pos && (*current_pos)->col_position == col_pos){
				break;
			}
			current_pos = &((*current_pos)->next);
		}
	}
}


void imprime_posicoes(WINDOW * win, int row_pos, int col_pos, struct POSITION* ponteiro){

	struct POSITION** current_pos = &ponteiro;
	while(1){
		if((*current_pos)->next == NULL){
			break;
		}
		else{
			// it avoids the unecessary use of memory;
			mvwaddch(win, (*current_pos)->row_position, (*current_pos)->col_position, '*');
			current_pos = &((*current_pos)->next);
		}
	}

}

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


void regex_input( char * input_char, char* result_char, int* pointer,   int size, int* check){
	if(size >= 3){
		if (input_char[0] == 'n' || input_char[0] == 's' || input_char[0] == 'o' || input_char[0] == 'e' ){
			if(input_char[1] == 'e' || input_char[1] == 'o' || input_char[1] == ' '){
				if (input_char[0] == 'n'){

					if (input_char[1] == 'e'){
						if (input_char[2] == ' '){
							char  second_part[size-3];

							for(int i =3; i<size; i++){
								if ( ((int) input_char[i] >= 48) &&  (int) input_char[i] <= 57){
									second_part[i-3] = (int) input_char[i];
									strcpy(result_char, "ne");
								}
								else{
									*check = 1;
								}

							}

							int second_part_transform = atoi(second_part);
							*pointer = second_part_transform;
						}

						else{
							*check = 1;
						}
					}



					else if (input_char[1] == 'o'){
						if (input_char[2] == ' '){
							char  second_part[size-3];

							for(int i =3; i<size; i++){
								if ( ((int) input_char[i] >= 48) &&  (int) input_char[i] <= 57){
									second_part[i-3] = (int) input_char[i];
									strcpy(result_char, "no");
								}
								else{
									*check = 1;
								}

							}

							int second_part_transform = atoi(second_part);
							*pointer = second_part_transform;
						}

						else{
							*check = 1;
						}
					}

					else if(input_char[1] == ' '){
						char  second_part[size-2];

							for(int i =2; i<size; i++){
								if ( ((int) input_char[i] >= 48) &&  (int) input_char[i] <= 57){
									second_part[i-2] = (int) input_char[i];
									strcpy(result_char, "n");
								}
								else{
									*check = 1;
								}

							}
							int second_part_transform = atoi(second_part);
							*pointer = second_part_transform;
					}

			}
				else if(input_char[0] == 's'){



					if (input_char[1] == 'e'){
						if (input_char[2] == ' '){
							char  second_part[size-3];

							for(int i =3; i<size; i++){
								if ( ((int) input_char[i] >= 48) &&  (int) input_char[i] <= 57){
									second_part[i-3] = (int) input_char[i];
									strcpy(result_char, "se");
								}
								else{
									*check = 1;
								}

							}
							int second_part_transform = atoi(second_part);
							*pointer = second_part_transform;
						}

						else{
							*check = 1;
						}
					}

					else if (input_char[1] == 'o'){
						if (input_char[2] == ' '){
							char  second_part[size-3];

							for(int i =3; i<size; i++){
								if ( ((int) input_char[i] >= 48) &&  (int) input_char[i] <= 57){
									second_part[i-3] = (int) input_char[i];
									strcpy(result_char, "so");
								}
								else{
									*check = 1;
								}

							}
							int second_part_transform = atoi(second_part);
							*pointer = second_part_transform;
						}

						else{
							*check = 1;
						}
					}


					else if(input_char[1] == ' '){
						char  second_part[size-2];

							for(int i =2; i<size; i++){
								if ( ((int) input_char[i] >= 48) &&  (int) input_char[i] <= 57){
									second_part[i-2] = (int) input_char[i];
									strcpy(result_char, "s");
								}
								else{
									*check = 1;
								}

							}
							int second_part_transform = atoi(second_part);
							*pointer = second_part_transform;
					}
				}

				else if(input_char[0] == 'o'){
					if(input_char[1] == ' '){
						char  second_part[size-2];

							for(int i =2; i<size; i++){
								if ( ((int) input_char[i] >= 48) &&  (int) input_char[i] <= 57){
									second_part[i-2] = (int) input_char[i];
									strcpy(result_char, "o");
								}
								else{
									*check = 1;
								}

							}
							int second_part_transform = atoi(second_part);
							*pointer = second_part_transform;
					}
					else{
						*check = 1;
					}
				}
				else if(input_char[0] == 'e'){
					if(input_char[1] == ' '){
						char  second_part[size-2];

							for(int i =2; i<size; i++){
								if ( ((int) input_char[i] >= 48) &&  (int) input_char[i] <= 57){
									second_part[i-2] = (int) input_char[i];
									strcpy(result_char, "e");
								}
								else{
									*check = 1;
								}

							}
							int second_part_transform = atoi(second_part);
							*pointer = second_part_transform;
					}
					else{
						*check = 1;
					}
				}
			else{
				*check = 1;
			}
		}
		else{
			*check = 1;
		}
	}
}


}

void check_pos(int rows, int cols, int *pos_row, int* pos_col){
	if(*pos_row >= (rows-1)){
		*pos_row = 1;
	}

	else if(*pos_row < 1){
		*pos_row = rows-2;
	}

	if(*pos_col >= (cols-1)){
		*pos_col = 1;
	}

	else if(*pos_col < 1){
		*pos_col = cols-2;
	}
}


int main(void){

    menuManager();

	initscr();			/* Start curses mode 		  */
	int rows, cols;
	int drawing = 1;
	//Get the max_size of the stdscr
    getmaxyx(stdscr, rows, cols);
	int main_window_rows = rows -4;
	// Create a object called WINDOW.
	WINDOW * main_window = newwin(main_window_rows, cols, 0, 0);
	WINDOW * command_window = newwin(3, cols, main_window_rows, 0);
	// Its necessary to refresh the stdcr to actually see the new window.
	refresh();

	//create_positions
	int row_pos = floor(+main_window_rows-1)/2;
	int * row_pos_ponteiro = &row_pos;
	int col_pos = floor((cols-1)/2);
	int * col_pos_ponteiro = &col_pos;
	struct POSITION positions;
	positions.next = NULL;
	struct POSITION* ponteiro = &positions;

	//create the structure of the command line
	struct COMMAND_CHAR characters;
	characters.pressed_char =NULL;
	characters.next = NULL;
	struct COMMAND_CHAR* ponteiro_2 = &characters;

	while(1){
		delwin(main_window);
		delwin(command_window);

		WINDOW * command_window = newwin(3, cols, main_window_rows, 0);
		WINDOW * main_window = newwin(main_window_rows, cols, 0, 0);
		bbox(main_window, main_window_rows, cols);
		bbox(command_window, 3, cols);

		//Creates the 'command line' string
		create_string(command_window, "COMANDO: ", 9, 3);
		if(drawing == 1){
			create_string(command_window, "DRAWING: ", 9, cols-13);
		}
		else{
			create_string(command_window, "DRAWING*: ", 9, cols-13);
		}
		//Enables special keys
		keypad(main_window, TRUE);
		check_pos(main_window_rows, cols, row_pos_ponteiro, col_pos_ponteiro);
		//Fills the already occupied positions
		if(drawing == 1){
			cria_posicao(main_window, row_pos, col_pos, ponteiro);
		}
        imprime_posicoes(main_window, row_pos, col_pos, ponteiro);
		imprime_sem_botao(command_window, ponteiro_2);
		//Creates the main charater
		mvwaddch(main_window, row_pos, col_pos, '@');
		//Refresh both windows
		wrefresh(main_window);
		wrefresh(command_window);
		char pressed_key = getch();			/* Get the pressed key */

        if(pressed_key == 'q'){
            sair();
        }

		if(pressed_key == 68){
			col_pos--;
		}
		else if(pressed_key == 65 || pressed_key == 87){
			row_pos--;
		}
		else if(pressed_key == 67){
			col_pos++;
		}
		else if(pressed_key == 66){
			row_pos++;
		}

		else if((pressed_key>=48 && pressed_key <=57) || pressed_key == 32){
				char current_char = (char) pressed_key;
				imprime(command_window, ponteiro_2, current_char);
			}
			else if(pressed_key>=97 && pressed_key <=122){
				char current_char = (char) pressed_key;
				imprime(command_window, ponteiro_2, current_char);
			}

			else if(pressed_key == 127){
				if (!(characters.pressed_char == NULL  && characters.next == NULL))
					remove_char(command_window, ponteiro_2);
			}
			else if(pressed_key == 78){
					if(drawing == 1){
						drawing = 0;
					}
					else{
						drawing = 1;
					}
			}

			else if(pressed_key == 10){
				int size = tamanho_lista(command_window, ponteiro_2);
				char * chars_digitados = malloc(size*sizeof(char));
				catch_characters(chars_digitados, ponteiro_2);
				char teste_input[3];
				int segundo_valor;
				int * teste_int = &segundo_valor;
				int checker = 0;
				int * checker_pointer = &checker;
				regex_input(chars_digitados,teste_input, teste_int,  size, checker_pointer);
				if (checker == 0 ){
					if (strcmp(teste_input, "ne") == 0){
						for(int i =0; i<segundo_valor; i++){
							mvwaddch(main_window, row_pos, col_pos, ' ');
							row_pos--;
							col_pos++;
							sleep(1);
							check_pos(main_window_rows, cols, row_pos_ponteiro, col_pos_ponteiro);
                            if(drawing == 1){
										cria_posicao(main_window, row_pos, col_pos, ponteiro);
                            }
							imprime_posicoes(main_window, row_pos, col_pos, ponteiro);
							mvwaddch(main_window, row_pos, col_pos, '@');
							if(drawing == 0){
								wrefresh(main_window);
								usleep(1000*12);
								mvwaddch(main_window, row_pos, col_pos, ' ');
								;}
							wrefresh(main_window);

						}


					}
					else if (strcmp(teste_input, "no") == 0){
						for(int i =0; i<segundo_valor; i++){

							mvwaddch(main_window, row_pos, col_pos, ' ');
							row_pos--;
							col_pos--;
							sleep(1);
							check_pos(main_window_rows, cols, row_pos_ponteiro, col_pos_ponteiro);
							if(drawing == 1){
										cria_posicao(main_window, row_pos, col_pos, ponteiro);

											}
							imprime_posicoes(main_window, row_pos, col_pos, ponteiro);
							mvwaddch(main_window, row_pos, col_pos, '@');
							if(drawing == 0){
								wrefresh(main_window);
								usleep(1000*12);
								mvwaddch(main_window, row_pos, col_pos, ' ');
								;}
							wrefresh(main_window);

						}
				}


					else if (strcmp(teste_input, "n") == 0){
						for(int i =0; i<segundo_valor; i++){
							mvwaddch(main_window, row_pos, col_pos, ' ');
							row_pos--;
							sleep(1);
                            check_pos(main_window_rows, cols, row_pos_ponteiro, col_pos_ponteiro);
                            if(drawing == 1){
                                cria_posicao(main_window, row_pos, col_pos, ponteiro);
                            }
                            imprime_posicoes(main_window, row_pos, col_pos, ponteiro);
							mvwaddch(main_window, row_pos, col_pos, '@');
							if(drawing == 0){
								wrefresh(main_window);
								usleep(1000*12);
								mvwaddch(main_window, row_pos, col_pos, ' ');
								;}
							wrefresh(main_window);
						}
					}
                    else if (strcmp(teste_input, "s") == 0){
						for(int i =0; i<segundo_valor; i++){
							mvwaddch(main_window, row_pos, col_pos, ' ');
							row_pos++;
							sleep(1);
							check_pos(main_window_rows, cols, row_pos_ponteiro, col_pos_ponteiro);
							if(drawing == 1){
                                cria_posicao(main_window, row_pos, col_pos, ponteiro);
                            }
                            imprime_posicoes(main_window, row_pos, col_pos, ponteiro);
							mvwaddch(main_window, row_pos, col_pos, '@');
							if(drawing == 0){
								wrefresh(main_window);
								usleep(1000*12);
								mvwaddch(main_window, row_pos, col_pos, ' ');
								;}
							wrefresh(main_window);

						}
					}

					else if (strcmp(teste_input, "so") == 0){
						for(int i =0; i<segundo_valor; i++){
							mvwaddch(main_window, row_pos, col_pos, ' ');
							row_pos++;
							col_pos--;
							sleep(1);
							check_pos(main_window_rows, cols, row_pos_ponteiro, col_pos_ponteiro);
                            if(drawing == 1){
										cria_posicao(main_window, row_pos, col_pos, ponteiro);

											}
                            imprime_posicoes(main_window, row_pos, col_pos, ponteiro);
							mvwaddch(main_window, row_pos, col_pos, '@');
							if(drawing == 0){
								wrefresh(main_window);
								usleep(1000*12);
								mvwaddch(main_window, row_pos, col_pos, ' ');
								;}
							wrefresh(main_window);
						}
					}
					else if (strcmp(teste_input, "se") == 0){
						for(int i =0; i<segundo_valor; i++){
							mvwaddch(main_window, row_pos, col_pos, ' ');
							row_pos++;
							col_pos++;
							sleep(1);
							check_pos(main_window_rows, cols, row_pos_ponteiro, col_pos_ponteiro);
                            if(drawing == 1){
										cria_posicao(main_window, row_pos, col_pos, ponteiro);
                            }
							imprime_posicoes(main_window, row_pos, col_pos, ponteiro);
							mvwaddch(main_window, row_pos, col_pos, '@');
							if(drawing == 0){
								wrefresh(main_window);
								usleep(1000*12);
								mvwaddch(main_window, row_pos, col_pos, ' ');
								;}
							wrefresh(main_window);

						}
					}


					else if (strcmp(teste_input, "o") == 0){
						for(int i =0; i<segundo_valor; i++){
							mvwaddch(main_window, row_pos, col_pos, ' ');
							col_pos--;
							sleep(1);
							check_pos(main_window_rows, cols, row_pos_ponteiro, col_pos_ponteiro);
                            if(drawing == 1){
										cria_posicao(main_window, row_pos, col_pos, ponteiro);

											}
							imprime_posicoes(main_window, row_pos, col_pos, ponteiro);
							mvwaddch(main_window, row_pos, col_pos, '@');
							if(drawing == 0){
								wrefresh(main_window);
								usleep(1000*12);
								mvwaddch(main_window, row_pos, col_pos, ' ');
								;}
							wrefresh(main_window);

						}
					}

					else if (strcmp(teste_input, "e") == 0){
						for(int i =0; i<segundo_valor; i++){
							mvwaddch(main_window, row_pos, col_pos, ' ');
							col_pos++;
							sleep(1);
							check_pos(main_window_rows, cols, row_pos_ponteiro, col_pos_ponteiro);
                            if(drawing == 1){
                                cria_posicao(main_window, row_pos, col_pos, ponteiro);
                            }
                            imprime_posicoes(main_window, row_pos, col_pos, ponteiro);
							mvwaddch(main_window, row_pos, col_pos, '@');
							if(drawing == 0){
								wrefresh(main_window);
								usleep(1000*12);
								mvwaddch(main_window, row_pos, col_pos, ' ');
								;}
							wrefresh(main_window);

						}
                    }
				}
			}
    }
	endwin();			/* End curses mode		  */
	return 0;
}
