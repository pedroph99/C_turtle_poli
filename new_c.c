#include <ncurses.h>
#include <math.h> 
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

	//BBOX Method.

	bbox(main_window, main_window_rows, cols);
	bbox(command_window, 3, cols);
	//Creates the main charater
	mvwaddch(main_window, floor((main_window_rows-1)/2), floor((cols-1)/2), '@');
	//Creates the 'command line' string
	create_string(command_window, "COMANDO: ", 9);
	//Refresh both windows
	wrefresh(main_window);
	wrefresh(command_window);
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
	return 0;
}