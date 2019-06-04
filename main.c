#include <stdio.h>
#include <stdlib.h>
#include "pizza.h"
#include "pizzaenc.h"

int main(int argc, char **argv){
    // argv 1 = ramification factor
    // argv 2 = filename
    if(argc < 3) printf("Missing parameters!");
    printf("%s\n", argv[2]);
    FILE* file = fopen(argv[2], "rb");
    if(!file) exit(1);

    TLEP* tlep = cria_tlep();

    int initf = ftell(file), endf;
    fseek(file, 0L, SEEK_END);
    endf = ftell(file);
    rewind(file);
    while(1){
        TPizza* tmp_pizza = le_pizza(file);
        if(!tmp_pizza) break;
        tlep = insere_fim_tlep(tlep, tmp_pizza);
        imprime_pizza(tmp_pizza);
    }
    puts("Here!");
    imprime_tlep(tlep);
    libera_tlep(tlep);

    return 0;
}
