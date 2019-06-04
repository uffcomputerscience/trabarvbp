#include "pizzaenc.h"
#include <stdio.h>
#include <stdlib.h>
#include "pizza.h"

TLEP* cria_tlep(){
    return NULL;
}

TLEP* insere_init_tlep(TLEP* tlep, TPizza* pizza){
    TLEP* lep = (TLEP*) malloc(sizeof(TLEP));
    lep->pizza = pizza;
    lep->prox_pizza = tlep;
    return lep;
}

TLEP* insere_fim_tlep(TLEP* tlep, TPizza* pizza){
    if(!tlep) return insere_init_tlep(tlep, pizza);
    tlep->prox_pizza = insere_fim_tlep(tlep->prox_pizza, pizza);
    return tlep;
}

void imprime_tlep(TLEP* tlep){
    while(tlep){
        imprime_pizza(tlep->pizza);
        tlep = tlep->prox_pizza;
    }
}

void libera_tlep(TLEP* tlep){
    if(tlep){
        libera_tlep(tlep->prox_pizza);
        free(tlep->pizza);
        free(tlep);
    }
}
