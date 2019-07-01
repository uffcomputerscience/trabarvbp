#include "pizza.h"
#include <string.h>
#include <stdlib.h>
#include "constant.h"
#include "categoria.h"
#include "files.h"

void imprime_pizza(TPizza *p)
{
	if(p) printf("%d, %s (%s), R$ %.2f: %d\n", p->cod, p->nome, p->categoria, p->preco, p->status);
}


TPizza *cria_pizza(int cod, char *nome, char *categoria, float preco)
{
	TPizza *p = (TPizza *) malloc(sizeof(TPizza));
	if (p) memset(p, 0, sizeof(TPizza));
	p->cod = cod;
	p->status = ALIVE;
	p->cat_ant = -1;
	p->cat_prox = -1;
	p->cat = -1;
	strcpy(p->nome, nome);
	strcpy(p->categoria, categoria);
	p->preco = preco;
	return p;
}


void salva_pizza(TPizza *p, FILE *out){
	fwrite(p, sizeof(TPizza), 1, out);
}

// Atualiza a pizza no local do cursor no arquivo (grava por cima)
void atualiza_pizza(FILE* out, TPizza* pizza){
	fwrite(pizza, sizeof(TPizza), 1, out);
}

// Ambos os arquivos devem ser abertos no formato rb+
// int dump_pizza(TPizza *pizza, char* pizzaout_filename, char* catFile_filename){
	// FILE *out = fopen(pizzaout_filename, "ab+");
	// if(!out) exit(1);
	// // fseek(out, end, SEEK_SET);
	// puts("pizza salva");
	// imprime_pizza(pizza);
	// salva_pizza(pizza, out);
	//
	// return end;
	// // puts(pizzaout_filename);
// 	FILE *out = fopen(pizzaout_filename, "ab");
// 	FILE* catFile = fopen(catFile_filename, "rb");
// 	int pizza_pos = end_fim_do_arqv(out);
//
// 	// disable buffering
// 	// setbuf(out, NULL);
// 	// setbuf(catFile, NULL);
//
// 	puts("Dumping...");
// 	//Salva a pizza
// 	// fseek(out, 0L, SEEK_END);
// 	// int pizza_pos = ftell(out);
// 	if(fwrite(pizza, sizeof(TPizza), 1, out) == 1){
// 		printf("Pizza %d salva em %d.\n", pizza->cod, pizza_pos);
// 	}else{
// 		puts("Erro ao salvar a pizza");
// 	}
//
// 	// Busca pela categoria
// 	TCat* cat = busca_cat_por_nome(catFile, pizza->categoria);
// 	int cat_pos = ftell(catFile);
// 	if(cat){
// 		// Ajustar o cursor para retornar a posição anterior ao auto incremento
// 		cat_pos -= sizeof(TCat);
// 		puts("#####");
// 		catFile = reload_file(catFile, catFile_filename, "rb+");
// 		fseek(catFile, cat_pos, SEEK_SET);
// 		TCat* tmp_cat = (TCat*) malloc(sizeof(TCat));
// 		fread(tmp_cat, sizeof(TCat), 1, catFile);
// 		imprime_cat(tmp_cat);
// 		printf("At %d\n", cat_pos);
// 		puts("#####");
// 	}
// 	if(!cat){
// 		// Caso seja categoria nova.
// 		catFile = reload_file(catFile, catFile_filename, "rb+");
//
// 		cat = cria_cat(pizza->categoria);
// 		cat->prim_pizza = pizza_pos;
// 		cat->ult_pizza = pizza_pos;
// 		salva_cat(catFile, cat);
// 		pizza->cat_ant = -1;
// 		pizza->cat_prox = -1;
// 		pizza->cat = cat_pos;
// 		printf("Cria cat at %d, ", cat_pos);
// 		imprime_cat(cat);
// 	}else{
// 		//ajusta os ponteiros da cadeia
// 		pizza->cat_ant = cat->ult_pizza;
// 		cat->ult_pizza = pizza_pos;
//
// 		//atualiza cat
// 		catFile = reload_file(catFile, catFile_filename, "rb+");
// 		fseek(catFile, cat_pos, SEEK_SET);
// 		atualiza_cat(catFile, cat);
// 		printf("Atualiza cat at %d \n", cat_pos);
// 		imprime_cat(cat);
//
// 		// atualiza o anterior da cadeia
// 		out = reload_file(out, pizzaout_filename, "rb+");
// 		fseek(out, pizza->cat_ant, SEEK_SET);
// 		TPizza* tmp_pizza = (TPizza*) malloc(sizeof(TPizza));
// 		fread(tmp_pizza, sizeof(TPizza), 1, out);
// 		tmp_pizza->cat_prox = pizza_pos;
// 		fseek(out, pizza->cat_ant, SEEK_SET);
// 		atualiza_pizza(out, tmp_pizza);
// 		printf("Atualiza tmp pizza %d at %d: ", tmp_pizza->cod, pizza->cat_ant);
// 		imprime_pizza(tmp_pizza);
// 	}
// 	out = reload_file(out, pizzaout_filename, "rb+");
// 	fseek(out, pizza_pos, SEEK_SET);
// 	atualiza_pizza(out, pizza);
// 	free(cat);
// 	fclose(out);
// 	fclose(catFile);
// 	return pizza_pos;
// }

TPizza *le_pizza(FILE *in)
{
	TPizza *p = (TPizza *) malloc(sizeof(TPizza));
	if (0 >= fread(&p->cod, sizeof(int), 1, in)) {
		free(p);
		return NULL;
	}
	fread(p->nome, sizeof(char), sizeof(p->nome), in);
	fread(p->categoria, sizeof(char), sizeof(p->categoria), in);
	fread(&p->preco, sizeof(float), 1, in);
	p->status = ALIVE;
	p->cat_ant = -1;
	p->cat_prox = -1;
	p->cat = -1;

	return p;
}

TPizza *le_arvb_pizza(FILE *in)
{
	TPizza *p = (TPizza *) malloc(sizeof(TPizza));
	if (0 >= fread(p, sizeof(TPizza), 1, in)){
		free(p);
		return NULL;
	}
	imprime_pizza(p);
	return p;
}


int cmp_pizza(TPizza *p1, TPizza *p2)
{
	if (p1 == NULL) {
		return (p2 == NULL);
	}
	if (p1->cod != p2->cod) {
		return 0;
	}
	if (strcmp(p1->nome, p2->nome) != 0) {
		return 0;
	}
	if (strcmp(p1->categoria, p2->categoria) != 0) {
		return 0;
	}
	if (p1->preco != p2->preco) {
		return 0;
	}
	if (p1->status != p2->status) {
		return 0;
	}
	return 1;
}


int tamanho_pizza_bytes()
{
	return sizeof(int) + // cod
		sizeof(char) * 50 + // nome
		sizeof(char) * 20 + // categoria
		sizeof(float)+ // preço
		sizeof(int); // status
}
