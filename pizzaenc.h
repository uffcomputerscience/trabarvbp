#ifndef PIZZA_ENC_HEADER
#define PIZZA_ENC_HEADER
#include "pizza.h"

typedef struct t_listap{
    TPizza* pizza;
    struct t_listap *prox_pizza;
}TLEP;

TLEP* cria_tlep();
TLEP* insere_init_tlep(TLEP* tlep, TPizza* pizza);
TLEP* insere_fim_tlep(TLEP* tlep, TPizza* pizza);
void imprime_tlep(TLEP* tlep);
void libera_tlep(TLEP* tlep);

#endif
