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
    char rosa_dos_ventos[5][13] = {"      N      ",
                                   "  NO /|\\ NE  ",
                                   " O <--+--> L ",
                                   "  SO \\|/ SE  ",
                                   "      S      "};
    char instruction1[8][60] = {"Utilize as setas para se movimentar",
                                 "                                   ",
                                 "Pressione \"q\" a qualquer momento para sair",
                                 "                                            ",
                                 "                                            ",
                                 "Pressione \"d\" para que a tartaruga ande SEM desenhar.",
                                 "Para que ela volte a desenhar, só é preciso pressionar ",
                                 " \"d\" novamente.                                      "};

    char instruction2[6][60] = {"Ao pressionar \"Caps Lock\", você podera digitar   ",
                                "uma direção e a quantidade de casas que a tartaruga",
                                "deve andar."                                        ,
                                "                                                   ",
                                "O comando das direções deve seguir as direções     ",
                                "presentes na Rosa dos Ventos a seguir:              "};

     for(int i = 0; i< 6; i++){
        mvprintw((y/3)+i, (x-sizeof(instruction1[i]))/2, instruction1[i]);
     }
}
