#ifndef ARVBM_HEADER
#define ARVBM_HEADER
#include "pizza.h"

typedef struct arvbm{
  int nchaves, folha, *chave;
  TPizza* pizza;
  struct arvbm **filho, *prox;
}TABM;

void libera_arvore(TABM *a);
TABM *cria_arvore(int t);
TABM *inicializa_arvore(void);
TABM *busca_pizza(TABM *a, int cod);
void imprime_arvore(TABM *a, int andar);
TABM *divisao(TABM *x, int i, TABM* y, int t);
TABM *insere_nao_completo(TABM *x, int mat, int t);
TABM *insere_pizza(TABM *arvbm, TPizza* pizza, int t);
#endif
