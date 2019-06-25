#include "arvbm.h"
#include <stdio.h>
#include <stdlib.h>
#include "pizza.h"
#include "constant.h"

TABM *cria_arvore(int t){
  TABM* novo = (TABM*)malloc(sizeof(TABM));
  novo->nchaves = 0;
  novo->chave =(int*)malloc(sizeof(int)*((t*2)-1));
  novo->folha = true;
  novo->filho = (TABM**)malloc(sizeof(TABM*)*t*2);
  novo->prox = NULL;
  novo->pizza = NULL;
  int i;
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
  return novo;
}


TABM *inicializa_arvore(void){
  return NULL;
}

void libera_arvore(TABM *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) libera_arvore(a->filho[i]);
    }
    free(a->chave);
    free(a);
  }
}

TABM *busca_pizza(TABM *a, int cod){
  if (!a) return NULL;
  int i = 0;
  while ((i < a->nchaves) && (cod > a->chave[i])) i++;
  if ((i < a->nchaves) && (a->folha) && (cod == a->chave[i])) return a;
  if (a-> folha) return NULL;
  if (a->chave[i] == cod) i++;
  return busca_pizza(a->filho[i], cod);
}

void imprime_arvore(TABM *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      imprime_arvore(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%d\n", a->chave[i]);
    }
    imprime_arvore(a->filho[i],andar+1);
  }
}

TABM *divisao(TABM *x, int i, TABM* y, int t){
  TABM *z = cria_arvore(t);
  z->folha = y->folha;
  int j;
  if(!y->folha){
    z->nchaves = t-1;
    for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  else {
    z->nchaves = t; //z possuir� uma chave a mais que y se for folha
    for(j=0;j < t;j++) z->chave[j] = y->chave[j+t-1];//Caso em que y � folha, temos q passar a info para o n� da direita
    y->prox = z;
  }
  y->nchaves = t-1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
  x->chave[i-1] = y->chave[t-1];
  x->nchaves++;
  return x;
}


TABM *insere_nao_completo(TABM *x, int mat, int t){
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (mat < x->chave[i])){
      x->chave[i+1] = x->chave[i];
      i--;
    }
    x->chave[i+1] = mat;
    x->nchaves++;
    return x;
  }
  while((i>=0) && (mat < x->chave[i])) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){
    x = divisao(x, (i+1), x->filho[i], t);
    if(mat > x->chave[i]) i++;
  }
  x->filho[i] = insere_nao_completo(x->filho[i], mat, t);
  return x;
}

TABM *insere_pizza(TABM *arvbm, TPizza* pizza, int t){
  if(busca_pizza(arvbm, pizza->cod)) return arvbm;
  if(!arvbm){
    arvbm=cria_arvore(t);
    arvbm->chave[0] = pizza->cod;
    arvbm->nchaves=1;
    return arvbm;
  }
  if(arvbm->nchaves == (2*t)-1){
    TABM *S = cria_arvore(t);
    S->nchaves=0;
    S->folha = false;
    S->filho[0] = arvbm;
    S = divisao(S,1,arvbm,t);
    S = insere_nao_completo(S, pizza->cod, t);
    return S;
  }
  arvbm = insere_nao_completo(arvbm, pizza->cod, t);
  return arvbm;
}
