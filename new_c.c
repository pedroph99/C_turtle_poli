#include <ncurses.h>
#include <math.h> 
#include <stdlib.h>
//Precisa-se criar um método bbox.
void bbox( WINDOW * window, int window_rows, int window_cols){
	// Surround the window with - and |
	for(int i=0; i<window_rows; i++){
		mvwaddch(window,i,0,'|');
		mvwaddch(window,i,window_cols-1,'|');
	}
	int i = 0;
	for(i; i<window_cols; i++){
		mvwaddch(window,0,i,'-');
		mvwaddch(window,window_rows-1,i,'-');
	}
}
void create_string (WINDOW * window, char * string, int size_string){
	for(int x = 0; x<size_string; x++){
		mvwaddch(window, 1 , 3+x, string[x]);
	}
	
}

//Cria um struct para ser armazenado as posições. Utilizando a estrutura de dados lista ligada.
 struct POSITION
	{
		int row_position;
		int col_position;
		struct POSITION* next;
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
			mvwaddch(win, (*current_pos)->row_position, (*current_pos)->col_position, '*');
			current_pos = &((*current_pos)->next);
			
		}
	}

}
int main(void){	
	initscr();			/* Start curses mode 		  */
	int rows, cols;
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
	int col_pos = floor((cols-1)/2);
	struct POSITION positions;
	positions.next = NULL;
	struct POSITION* ponteiro = &positions;

	while(1){
		delwin(main_window);
		WINDOW * main_window = newwin(main_window_rows, cols, 0, 0);
		bbox(main_window, main_window_rows, cols);
		bbox(command_window, 3, cols);
		
		
		//Creates the 'command line' string
		create_string(command_window, "COMANDO: ", 9);
		//Enables special keys
		keypad(main_window, TRUE);
		
		//Fills the already occupied positions
		cria_posicao(main_window, row_pos, col_pos, ponteiro);
		//Creates the main charater
		mvwaddch(main_window, row_pos, col_pos, '@');
		//Refresh both windows
		wrefresh(main_window);
		wrefresh(command_window);
		int pressed_key = getch();			/* Get the pressed key */

		
		if(pressed_key == 68){
			col_pos--;
			
		}
		else if(pressed_key == 65){
			row_pos--;
		}
		else if(pressed_key == 67){
			col_pos++;
		}
		else if(pressed_key == 66){
			row_pos++;
		}
		
		printw("%d", pressed_key);
	}
	endwin();			/* End curses mode		  */
	return 0;
}