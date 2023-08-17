#ifndef UTILS_H
    #define UTILS_H
        void create_string (WINDOW * window, char * string, int size_string, int col_start);
        void remove_char(WINDOW* win,  struct COMMAND_CHAR* ponteiro);
        int tamanho_lista(WINDOW* win,  struct COMMAND_CHAR* ponteiro);
        void catch_characters(char* digited_chars, struct COMMAND_CHAR* ponteiro);
#endif
