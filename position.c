#include <ncurses.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "position.h"

void cria_posicao(WINDOW * win, int row_pos, int col_pos, struct POSITION* ponteiro) {
    struct POSITION** current_pos = &ponteiro;
    while(1) {
        if ((*current_pos)->next == NULL) {
            (*current_pos)->row_position = row_pos;
            (*current_pos)->col_position = col_pos;
            (*current_pos)->next = malloc(sizeof(struct POSITION));
            break;
        } else {
            // it avoids the unnecessary use of memory;
            if ((*current_pos)->row_position == row_pos && (*current_pos)->col_position == col_pos) {
                break;
            }
            current_pos = &((*current_pos)->next);
        }
    }
}

void imprime_posicoes(WINDOW * win, int row_pos, int col_pos, struct POSITION* ponteiro) {
    struct POSITION** current_pos = &ponteiro;
    while (1) {
        if ((*current_pos)->next == NULL) {
            break;
        } else {
            // it avoids the unnecessary use of memory;
            mvwaddch(win, (*current_pos)->row_position, (*current_pos)->col_position, '*');
            current_pos = &((*current_pos)->next);
        }
    }
}
