#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pizza.h"
#include "pizzaenc.h"
// #include "arvbm.h"
#include "arvbmms.h"
#include "categoria.h"

#define EXTENSION "trabson"

void inicializa_arquivo(char* filename){
    fclose(fopen(filename, "w"));
}

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

    char *p;
    long t = strtol(argv[1], &p, 10);

    //[ INICIALIZA ARQUIVOS ]
    char arvFileName[20] = "arvbm_file.";
    strcat(arvFileName, EXTENSION);

    char dumpFileName[20] = "dump_file.";
    strcat(dumpFileName, EXTENSION);

    char catFileName[20] = "cat_file.";
    strcat(catFileName, EXTENSION);

    inicializa_arquivo(arvFileName);
    inicializa_arquivo(dumpFileName);
    inicializa_arquivo(catFileName);

    //[ FIM DE INICIALIZA ARQUIVOS ]

    // int i = 3;
    while(1){
        TPizza* tmp_pizza = le_pizza(file);
        if(!tmp_pizza) break;
        insere_pizza(arvFileName, dumpFileName, catFileName, tmp_pizza, t);
        free(tmp_pizza);
        // i--;
    }

    fclose(file);

    TPizza* p1 = cria_pizza(2, "pizza 1", "Salgada", 2.3f);
    TPizza* p2 = cria_pizza(4, "pizza 2", "Salgada", 2.28f);
    TPizza* p3 = cria_pizza(6, "pizza 3", "Especial", 2.95f);
    TPizza* p4 = cria_pizza(3, "pizza 4", "Doce", 4.95f);
    TPizza* p5 = cria_pizza(1, "pizza 5", "Doce", 4.95f);
    TPizza* p6 = cria_pizza(5, "pizza 6", "Doce", 4.95f);
    TPizza* p7 = cria_pizza(7, "pizza 7", "Doce", 4.95f);
    TPizza* p8 = cria_pizza(8, "pizza 7", "Doce", 4.95f);
    TPizza* p9 = cria_pizza(9, "pizza 7", "Doce", 4.95f);
    TPizza* p10 = cria_pizza(10, "pizza 7", "Doce", 4.95f);

    // insere_pizza(arvFileName, dumpFileName, catFileName, p1, t);
    // insere_pizza(arvFileName, dumpFileName, catFileName, p2, t);
    // insere_pizza(arvFileName, dumpFileName, catFileName, p3, t);
    // insere_pizza(arvFileName, dumpFileName, catFileName, p4, t);
    // insere_pizza(arvFileName, dumpFileName, catFileName, p5, t);
    // insere_pizza(arvFileName, dumpFileName, catFileName, p6, t);
    // insere_pizza(arvFileName, dumpFileName, catFileName, p7, t);
    // insere_pizza(arvFileName, dumpFileName, catFileName, p8, t);
    // insere_pizza(arvFileName, dumpFileName, catFileName, p9, t);
    // insere_pizza(arvFileName, dumpFileName, catFileName, p7, t);

    puts("imprime arvore: 1");
    imprime_arvore(arvFileName, t, 0, 0L);
    puts("fim da impressão");
    puts("imprime arvore: 2");

    // free(p1);
    // free(p2);
    // free(p3);
    // free(p4);

    // insere_pizza(arvFileName, dumpFileName, catFileName, p5, t);
    // arvFile = freopen(arvFileName, "rb+", arvFile);
    // insere_pizza(arvFile, dumpFile, catFile, p2, t);
    // insere_pizza(arvFile, dumpFile, catFile, p3, t);
    // rewind(arvFile);

    // puts("imprime arvore: 1");
    // imprime_arvore(arvFileName, t, 0, 0L);
    // puts("fim da impressão");
    // puts("imprime arvore: 2");
    // imprime_arvore(arvFileName, t, 0, 0L);

    // int cod;
    // scanf("%d", &cod);
    // imprime_pizza(busca_pizza(arvFileName, dumpFileName, cod, t));

    //
    // puts("Primeira Arvore!");
    // // imprime_tlep(tlep);
    // // libera_tlep(tlep);
    //
    // // imprime_arvore(arvb, 0);
    // // libera_arvore(arvb);
    // fclose(file);
    // rewind(dumpFile);
    // rewind(catFile);
    // fclose(dumpFile);
    // fclose(catFile);
    //
    // puts("Segunda Arvore!");
    //
    // dumpFile = fopen(dumFileName, "rb");
    // if(!dumpFile) exit(1);
    //
    // catFile = fopen(catFileName, "rb");
    // if(!catFile) exit(1);
    //
    // // arvb = inicializa_arvore();
    // // while(1){
    // //     TPizza* tmp_pizza = le_arvb_pizza(dumpFile);
    // //     if(!tmp_pizza) break;
    // //     // tlep = insere_fim_tlep(tlep, tmp_pizza);
    // //     // arvb = insere_pizza(arvb, tmp_pizza, t);
    // //     imprime_pizza(tmp_pizza);
    // //
    // // }
    //
    // puts("Lê cat");
    // TCat* cat = NULL;
    // while(1){
    //     cat = busca_cat(catFile);
    //     if(!cat) break;
    //     // tlep = insere_fim_tlep(tlep, tmp_pizza);
    //     // arvb = insere_pizza(arvb, tmp_pizza, t);
    //     imprime_cat(cat);
    // }
    //
    // rewind(catFile);
    // cat = busca_cat(catFile);
    // TPizza* tmpp = (TPizza*) malloc(sizeof(TPizza));
    // fseek(dumpFile, cat->prim_pizza, SEEK_SET);
    // while(1){
    //     fread(tmpp, sizeof(TPizza), 1, dumpFile);
    //     imprime_pizza(tmpp);
    //     if(tmpp->cat_prox != -1) fseek(dumpFile, tmpp->cat_prox, SEEK_SET);
    //     else break;
    // }
    //
    // puts("Segunda Arvore!");
    // // imprime_arvore(arvb, 0);
    // // libera_arvore(arvb);
    // fclose(dumpFile);
    // fclose(catFile);

    return 0;
}
