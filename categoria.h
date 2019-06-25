#ifndef CATEGORIA_HEADER
#define CATEGORIA_HEADER
#include "pizzaenc.h"

typedef struct categoria{
  char nome[20];
  int prim_pizza;
  int ult_pizza;
}TCat;

// Cira TCat com nome passado e prim_pizza = -1
TCat* cria_cat(char* nome);

// Busca a cadeia de pizzas no arquivo a partir da posição da cadeia dada pelo TCat
TLEP* busca_pizzas(TCat* cat, FILE* in);

// Busca TCat no arquivo a partir da posição do cursor
TCat* busca_cat(FILE* in);

// Busca TCat no arquivo pelo nome (leitura linear)
TCat* busca_cat_por_nome(FILE* in, char* nome);

// libera TCat
void libera_cat(TCat* cat);

// salva TCat no fim do arquivo e retorna a posicao na qual foi salvo
int salva_cat(FILE* out, TCat* cat);

// atualiza TCat no local do cursor (grava por cima da posição)
void atualiza_cat(FILE* out, TCat* cat);

void imprime_cat(TCat* cat);

#endif
