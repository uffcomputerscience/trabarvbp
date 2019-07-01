#ifndef ARVBMMS_HEADER
#define ARVBMMS_HEADER
#include "pizza.h"

typedef struct arvbmms{
    int nchaves, folha, *chave, *pizza_pos;
    int *filho, prox;
}TABMMS;

// Libera nodo alocado
void libera_nodo(TABMMS* nodo);

// Cria nodo da arvore b+
TABMMS* cria_arvore_bmms(int t);

//Calcula o tamanho do nodo em bytes (para escrita e leitura)
int tamanho_abmms_bytes(int t);

// Salva nodo na posição do cursor (pode ser usado para update)
int salva_nodo(FILE* out, TABMMS* nodo, int t);

// le nodo na posição do cursor
TABMMS* le_nodo(FILE* in, int t);

// Busca pizza pelo id
// retorna pos da pizza no arqv de dados
int busca_pizza_end(FILE* arvbmm, int cod, int t);

// Busca pizza dada o pizza->cod dela
// retorna NULL caso nada seja encontrado
TPizza* busca_pizza(char* arvbmsin_filename, char* pizzain_filename, int cod,int t);

// Retorna o endereço do fim do arquivo passado
// função auxiliar
int end_fim_do_arqv(FILE* f);

// Insere a pizza no arquivo e retorna a posicao dele no arquivo de chaves
// Ou atualiza a pizza
int insere_pizza(char* arvbmsout_filename, char* pizzaout_filename, char* catFile_filename, TPizza* pizza, int t);

// imprime a arvore de lado
void imprime_arvore(char* arv_filename, int t, int andar, int nodo_pos);

// Este método seta o nchaves do nodo encontrado no local do cursor para 0
void apaga_nodo(FILE* arvbmms, int t);

int dump_pizza(TPizza *pizza, char* pizzaout_filename, char* catFile_filename, char* arvbmms_filename,int t);

#endif
