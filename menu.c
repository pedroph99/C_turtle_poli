#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "menu.h"
#include "quit.h"

void menuManager(){
    initscr();
    int x,y;
    getmaxyx(stdscr,y,x);
    noecho();
    char entrada= ' ';
    printMenu(x, y);
    while(entrada != 's'){
        bbox(stdscr, y, x);
        entrada = getch();
        if(entrada == 'q')
            sair();
        else if(entrada == 'i'){
            clear();
            printIntructions(x, y);
        }
        else if(entrada == 'b'){
            clear();
            printMenu(x, y);
        }
    }
    clear();
    endwin();
}

void printMenu(int x, int y){
    char menu[6][110] = {" _________ ___   ___ ________  _________ ____      _________      ________          _        ____      ____ ",
                         " |__   __| | |   | | |  ____ \\ |__   __| |  |      |  _____|      |  ____ \\    ____|_|____   |  |      |  | ",
                         "    | |    | |   | | |  |__| |    | |    |  |      |  |___        |  |__|  |  /  /@ @ @   \\  |  |      |  | ",
                         "    | |    | |   | | |  ____/     | |    |  |      |  ____|       |  _____/  /_/|@ @ @ @|\\_\\ |  |      |  | ",
                         "    | |    | |___| | |  | \\ \\     | |    |  |____  |  |____       |  |          __@_@_@/__   |  |____  |  | ",
                         "    |_|     \\_____/  |__|  \\ \\    |_|    |_______| |_______|      |__|         /_/  V   \\_\\  |_______| |__| "};

    char buttons[3][15] = {"<S>tart", "<I>structions", "<Q>uit"};

    for(int i = 0; i< 6; i++){
        mvprintw((y/3)+i, (x-sizeof(menu[i]))/2, menu[i]);
    }
    for(int i = 0; i < 3;i++){
        mvprintw((y*2/3)+i, (x-sizeof(buttons[i]))/2, buttons[i]);
    }
}

void printIntructions(int x, int y){
    char backButton[8] = "<B>ack";
    char startButon[8] = "<S>tart";
    mvprintw(y*3/5, (x/2)-20, backButton);
    mvprintw(y*3/5, (x/2)+5, startButon);

    char rosa_dos_ventos[5][15] = {"      N      ",
                                   "  NO /|\\ NE  ",
                                   " O <--+--> L ",
                                   "  SO \\|/ SE  ",
                                   "      S      "};
    char instruction1[8][80] = { "Utilize as setas para se movimentar",
                                 "                                   ",
                                 "Pressione \"q\" a qualquer momento para sair",
                                 "                                            ",
                                 "                                            ",
                                 "Pressione CAPSLOCK e \"N\" para que a tartaruga ande SEM desenhar.",
                                 "Para que ela volte a desenhar, só é preciso pressionar",
                                 "CAPSLOCK e \"N\" novamente.                                      "};

    char instruction2[5][60] = {"Você podera digitar uma direção e a quantidade ",
                                "de casas que a tartaruga deve andar.",
                                "                                      ",
                                "O comando das direções deve seguir as direções",
                                "presentes na Rosa dos Ventos a seguir:"};

     for(int i = 0; i< 6; i++){
        mvprintw((y/3)+i, (x-sizeof(instruction1[i]))/3, instruction1[i]);
     }
     for(int i = 0; i< 5; i++){
        mvprintw((y/3)+i, (x-sizeof(instruction1[i]))*2/3, instruction2[i]);
     }
     for(int i = 0; i< 5; i++){
        mvprintw((y/3)+i+6, (x-sizeof(instruction1[i]))*2/3, rosa_dos_ventos[i]);
     }
}

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
