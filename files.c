#include "files.h"
#include <stdio.h>
#include <stdlib.h>

FILE* reload_file(FILE* file, char* filename, char* permission){
    fclose(file);
    file = fopen(filename, permission);
    if(!file) exit(1);
    fseek(file, 0L, SEEK_SET);
    return file;
}

// Retorna o endereço do fim do arquivo passado
// função auxiliar
int end_fim_do_arqv(FILE* f){
    int pos_anterior = ftell(f);
    fseek(f, 0L, SEEK_END);
    int end_fim = ftell(f);
    fseek(f, pos_anterior, SEEK_SET);
    return end_fim;
}
