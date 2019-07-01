#ifndef PIZZA_HEADER
#define PIZZA_HEADER

#include <stdio.h>

typedef struct pizza {
	int cod, status, cat_ant, cat_prox, cat;
	char nome[50];
	char categoria[20];
	float preco;
} TPizza;

// Imprime pizza
void imprime_pizza(TPizza *p);

// Cria pizza
TPizza *cria_pizza(int cod, char *nome, char *categoria, float preco);

// Salva pizza no arquivo out, na posicao atual do cursor
void salva_pizza(TPizza *p, FILE *out);

// Salva pizza no final do arquivo out
int dump_pizza(TPizza *pizza, char* pizzaout_filename, char* catFile_filename);

// Atualiza a pizza no local do cursor no arquivo (grava por cima)
void atualiza_pizza(FILE* out, TPizza* pizza);

// Le uma pizza do arquivo in na posicao atual do cursor
// Retorna um ponteiro para pizza lida do arquivo
TPizza *le_pizza(FILE *in);

// Le uma pizza do arquivo in na posicao atual do cursor
// Retorna um ponteiro para pizza lida do arquivo (usar somente para o arquivo
// da arvore gerada).
TPizza *le_arvb_pizza(FILE *in);

// Compara duas pizzas
// Retorna 1 se os valores dos atributos de ambos forem iguais
// e 0 caso contrario
int cmp_pizza(TPizza *p1, TPizza *p2);

// Retorna tamanho do registro que representa a pizza em bytes
int tamanho_pizza_bytes();
#endif
