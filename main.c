#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pizza.h"
#include "pizzaenc.h"
#include "arvbm.h"
#include "categoria.h"

#define EXTENSION "trabson"

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

    // TABM* arvb = inicializa_arvore();
    // char *p;
    // long t = strtol(argv[1], &p, 10);

    char dumFileName[20] = "dump_file.";
    strcat(dumFileName, EXTENSION);
    fclose(fopen(dumFileName, "w"));

    FILE* dumpFile = fopen(dumFileName, "rb+");
    if(!dumpFile) exit(1);

    char catFileName[20] = "cat_file.";
    strcat(catFileName, EXTENSION);
    fclose(fopen(catFileName, "w"));

    FILE* catFile = fopen(catFileName, "rb+");
    if(!catFile) exit(1);

    while(1){
        TPizza* tmp_pizza = le_pizza(file);
        if(!tmp_pizza) break;
        // tlep = insere_fim_tlep(tlep, tmp_pizza);
        // dump_pizza(TPizza *pizza, FILE *out, FILE* catFile)
        dump_pizza(tmp_pizza, dumpFile, catFile);
        // arvb = insere_pizza(arvb, tmp_pizza, t);
        // imprime_pizza(tmp_pizza);
    }

    puts("Primeira Arvore!");
    // imprime_tlep(tlep);
    // libera_tlep(tlep);

    // imprime_arvore(arvb, 0);
    // libera_arvore(arvb);
    fclose(file);
    rewind(dumpFile);
    rewind(catFile);
    fclose(dumpFile);
    fclose(catFile);

    puts("Segunda Arvore!");

    dumpFile = fopen(dumFileName, "rb");
    if(!dumpFile) exit(1);

    catFile = fopen(catFileName, "rb");
    if(!catFile) exit(1);

    // arvb = inicializa_arvore();
    // while(1){
    //     TPizza* tmp_pizza = le_arvb_pizza(dumpFile);
    //     if(!tmp_pizza) break;
    //     // tlep = insere_fim_tlep(tlep, tmp_pizza);
    //     // arvb = insere_pizza(arvb, tmp_pizza, t);
    //     imprime_pizza(tmp_pizza);
    //
    // }

    puts("Lê cat");
    TCat* cat = NULL;
    while(1){
        cat = busca_cat(catFile);
        if(!cat) break;
        // tlep = insere_fim_tlep(tlep, tmp_pizza);
        // arvb = insere_pizza(arvb, tmp_pizza, t);
        imprime_cat(cat);
    }

    rewind(catFile);
    cat = busca_cat(catFile);
    TPizza* tmpp = (TPizza*) malloc(sizeof(TPizza));
    fseek(dumpFile, cat->prim_pizza, SEEK_SET);
    while(1){
        fread(tmpp, sizeof(TPizza), 1, dumpFile);
        imprime_pizza(tmpp);
        if(tmpp->cat_prox != -1) fseek(dumpFile, tmpp->cat_prox, SEEK_SET);
        else break;
    }

    puts("Segunda Arvore!");
    // imprime_arvore(arvb, 0);
    // libera_arvore(arvb);
    fclose(dumpFile);
    fclose(catFile);

    return 0;
}
