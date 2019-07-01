#include "categoria.h"
#include "pizza.h"
#include "pizzaenc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _XOPEN_SOURCE 500

#include<unistd.h>

void imprime_cat(TCat* cat){
    printf("%s prim %d, ult %d\n", cat->nome, cat->prim_pizza, cat->ult_pizza);
}

// Cira TCat com nome passado e prim_pizza = -1
TCat* cria_cat(char* nome){
    TCat* novo = (TCat*) malloc(sizeof(TCat));
    strcpy(novo->nome, nome);
    novo->prim_pizza = -1;
    novo->ult_pizza = -1;
    return novo;
}

// Busca a cadeia de pizzas no arquivo a partir da posição do cursor
TLEP* busca_pizzas(TCat* cat, FILE* in){
    //TODO
    fseek(in, cat->prim_pizza, SEEK_SET);
    TPizza* tmp_pizza = (TPizza*) malloc(sizeof(TPizza));
    while(0 < fread(tmp_pizza, sizeof(TPizza), 1, in)){
        if(tmp_pizza->cat_prox == -1) break;
    }
    return NULL;
}

// Busca TCat no arquivo a partir da posição do cursor
TCat* busca_cat(FILE* in){
    TCat* cat = (TCat*) malloc(sizeof(TCat));
    if(0 < fread(cat, sizeof(TCat), 1, in)) return cat;
    return NULL;
}

// Busca TCat no arquivo pelo nome (leitura linear)
TCat* busca_cat_por_nome(FILE* in, char* nome){
    TCat *cat = (TCat *) malloc(sizeof(TCat));
    rewind(in);
    puts("Buscando cat...");
    //0 >= fread(&p->cod, sizeof(int), 1, in)
	while(0 < fread(cat, sizeof(TCat), 1, in)) {
        // printf("%s == %s\n", cat->nome, nome);
		if(strcmp(cat->nome, nome) == 0){
            printf("Returning ");
            imprime_cat(cat);
            printf("at %lu\n", ftell(in)-sizeof(TCat));
            return cat;
        }
	}
    free(cat);
    puts("Return NULL.");
    return NULL;
}

// salva TCat no fim do arquivo e retorna a posicao na qual foi salvo
int salva_cat(FILE* out, TCat* cat){
    fseek(out, 0L, SEEK_END);
    int pos = ftell(out);
	fwrite(cat, sizeof(TCat), 1, out);
    return pos;
}

// atualiza TCat no local do cursor (grava por cima da posição)
void atualiza_cat(FILE* out, TCat* cat){
    fwrite(cat, sizeof(TCat), 1, out);
}

// libera TCat
void libera_cat(TCat* cat){
    free(cat);
}
