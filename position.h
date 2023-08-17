#ifndef POSITION_H
    #define POSITION_H
//Cria um struct para ser armazenado as posições. Utilizando a estrutura de dados lista ligada.
        struct POSITION{
		    int row_position;
		    int col_position;
		    struct POSITION* next;
        };
        struct COMMAND_CHAR{
            char pressed_char;
	        struct COMMAND_CHAR* next;
        };
        void cria_posicao(WINDOW * win, int row_pos, int col_pos, struct POSITION* ponteiro);
        void imprime_posicoes(WINDOW * win, int row_pos, int col_pos, struct POSITION* ponteiro);
#endif
