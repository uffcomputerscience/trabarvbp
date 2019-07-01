#include "arvbmms.h"
#include "constant.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "files.h"

// Cria nodo da arvore b+
TABMMS* cria_arvore_bmms(int t){
    TABMMS* novo = (TABMMS*) malloc(sizeof(TABMMS));
    if (novo) memset(novo, 0, sizeof(TABMMS));
    novo->nchaves = 0;
    novo->chave =(int*) malloc(sizeof(int)*((t*2)-1));
    novo->folha = true;
    novo->filho = (int*) malloc(sizeof(int)*t*2);
    novo->prox = -1;
    novo->pizza_pos = (int*) malloc(sizeof(int)*((t*2)-1));
    int i;
    for(i=0; i<((t*2)-1); i++) novo->chave[i] = -1;
    for(i=0; i<((t*2)-1); i++) novo->pizza_pos[i] = -1;
    for(i=0; i<(t*2); i++) novo->filho[i] = -1;
    return novo;
}

// imprime um único
void imprime_nodo(TABMMS* nodo){
    if(nodo){
        printf("    é folha: %d\n", nodo->folha);
        printf("    nchaves: %d\n", nodo->nchaves);
        printf("    chaves:");
        int i;
        for(i=0; i<nodo->nchaves; i++) printf(" %d", nodo->chave[i]);
        printf("\n    pizza_pos:");
        for(i=0; i<nodo->nchaves;i++) printf(" %d", nodo->pizza_pos[i]);
        puts("");
    }
}

// Salva nodo na posição do cursor (pode ser usado para update)
int salva_nodo(FILE* out, TABMMS* nodo, int t){
    if(nodo){
        // imprime_nodo(nodo);
        int nodo_pos = ftell(out);
        fwrite(&nodo->nchaves, sizeof(int), 1, out);
        fwrite(nodo->chave, sizeof(int), sizeof(int)*((t*2)-1), out);
        fwrite(&nodo->folha, sizeof(int), 1, out);
        fwrite(nodo->filho, sizeof(int), sizeof(int)*t*2, out);
        fwrite(&nodo->prox, sizeof(int), 1, out);
        fwrite(nodo->pizza_pos, sizeof(int), sizeof(int)*((t*2)-1), out);
        return nodo_pos;
    }
    return -1;
}

// le nodo na posição do cursor
TABMMS* le_nodo(FILE* in, int t){
    TABMMS* nodo = cria_arvore_bmms(t);
	if (0 >= fread(&nodo->nchaves, sizeof(int), 1, in)){
        puts("Erro ao ler nodo");
		// libera_nodo(nodo);
		return NULL;
	}
    fread(nodo->chave, sizeof(int), sizeof(int)*((t*2)-1), in);
    fread(&nodo->folha, sizeof(int), 1, in);
    fread(nodo->filho, sizeof(int), sizeof(int)*t*2, in);
    fread(&nodo->prox, sizeof(int), 1, in);
    fread(nodo->pizza_pos, sizeof(int), sizeof(int)*((t*2)-1), in);
	return nodo;
}

// imprime arvore de lado
void imprime_arvore(char* arv_filename, int t, int andar, int nodo_pos){
    FILE* in = fopen(arv_filename, "rb");
    if(!in){
        puts("erro ao abrir arquivo");
        exit(1);
    }
    fseek(in, nodo_pos, SEEK_SET);
    TABMMS* a = le_nodo(in, t);
    fclose(in);
    if(a && a->nchaves > 0){
        int i,j;
        for(i=0; i<=a->nchaves-1; i++){
            if(!a->folha && a->filho[i] != -1){
                imprime_arvore(arv_filename, t, andar+1, a->filho[i]);
            }
            for(j=0; j<=andar; j++) printf("   ");
            printf("%d\n", a->chave[i]);
        }
        if(!a->folha && a->filho[i] != -1){
            imprime_arvore(arv_filename, t, andar+1, a->filho[i]);
        }
        // libera_nodo(a);
    }
}

// Busca pizza pelo id
// retorna pos da pizza no arqv de dados
int busca_pizza(FILE* arvbmms, int cod, int t){
    TABMMS* a = le_nodo(arvbmms, t);
    if (!a) return -1;
    int i = 0;
    while ((i < a->nchaves) && (cod > a->chave[i])) i++;
    if ((i < a->nchaves) && (a->folha) && (cod == a->chave[i])){
        // pizza encontrada
        // libera_nodo(a);
        return a->pizza_pos[i];
    }
    if (a-> folha) return -1;
    if (a->chave[i] == cod) i++;
    fseek(arvbmms, a->filho[i], SEEK_SET);
    // libera_nodo(a);
    return busca_pizza(arvbmms, cod, t);
}


// função auxiliar para inserir e remover nodos da árvore
// função auxiliar
TABMMS *divisao(FILE* arvbmsout, TABMMS *raiz, int i, TABMMS* nodo_ant, int t){
    // a função fará a distribuição dos dados do nodo a ser dividido em
    // 3 novos nodos (pai)-> (medade esq) /->(metade dir)
    //[ depois da divisão]
    // raiz -> raiz da subarv dividida
    // nodo_ant -> sub arvore da esquerda (0 até t-1)
    // nodo_dir -> sub arvore da direita
    TABMMS *nodo_dir = cria_arvore_bmms(t);
    nodo_dir->folha = nodo_ant->folha;
    int j;
    if(!nodo_ant->folha){
        // caso não for folha deve-se copiar os filhos da sub arvore antiga
        // copiando os filhos da direita de t no nodo_ant
        // para a esquerda de nodo_dir.
        nodo_dir->nchaves = t-1;
        for(j=0;j<t-1;j++){
            nodo_dir->chave[j] = nodo_ant->chave[j+t];
            nodo_dir->pizza_pos[j] = nodo_ant->pizza_pos[j+t];
        }
        for(j=0;j<t;j++){
          nodo_dir->filho[j] = nodo_ant->filho[j+t];
          nodo_ant->filho[j+t] = -1;// endereço nulo
        }
    }
    else {
        //nodo_dir possuirá uma chave a mais que nodo_ant se for folha
        nodo_dir->nchaves = t;
        for(j=0;j < t;j++){
            //Caso em que nodo_ant seja folha, temos q passar a info para o nó da direita
            nodo_dir->chave[j] = nodo_ant->chave[j+t-1];
            nodo_dir->pizza_pos[j] = nodo_ant->pizza_pos[j+t-1];
        }
        nodo_ant->prox = nodo_dir->pizza_pos[0];
    }
    nodo_ant->nchaves = t-1;
    // salva nodo_ant no fim do arqv da arvore
    fseek(arvbmsout, 0L, SEEK_END);
    salva_nodo(arvbmsout, nodo_ant, t);
    // salva nodo_dir no fim do arqv da arvore (depois do nodo_ant)
    fseek(arvbmsout, 0L, SEEK_END);
    // posição no arqv de chaves [fim + nodo_ant]
    int nodo_dir_pos = ftell(arvbmsout);
    salva_nodo(arvbmsout, nodo_dir, t);

    for(j=raiz->nchaves; j>=i; j--) raiz->filho[j+1]=raiz->filho[j];
    raiz->filho[i] = nodo_dir_pos;
    for(j=raiz->nchaves; j>=i; j--){
        raiz->chave[j] = raiz->chave[j-1];
        raiz->pizza_pos[j] = raiz->pizza_pos[j-1];
    }
    raiz->chave[i-1] = nodo_ant->chave[t-1];
    raiz->pizza_pos[i-1] = nodo_ant->pizza_pos[t-1];
    raiz->nchaves++;
    // libera_nodo(nodo_dir);
    return raiz;
}

// Este método seta o nchaves do nodo encontrado no local do cursor para 0
void apaga_nodo(FILE* arvbmms, int t){
    int nodo_pos = ftell(arvbmms);
    TABMMS* a = le_nodo(arvbmms, t);
    if(a){
        a->nchaves = 0;
        fseek(arvbmms, nodo_pos, SEEK_SET);
        salva_nodo(arvbmms, a, t);
        fseek(arvbmms, nodo_pos, SEEK_SET);
        // libera_nodo(a);
    }
}

int insere_nao_completo(char* arvbmsout_filename, char* pizzaout_filename, char* catFile_filename, TPizza* pizza, int t, int nodo_pos){
    puts("insere_nao_completo");
    FILE* arvbmsout = fopen(arvbmsout_filename, "rb");
    setbuf(arvbmsout, NULL);
    if(!arvbmsout) exit(1);
    fseek(arvbmsout, nodo_pos, SEEK_SET);
    printf("nodo a ser lido %d\n", nodo_pos);
    TABMMS* arvbmms = le_nodo(arvbmsout, t);
    if(!arvbmms) return -1;

    // printf("Pos da pizza lida %d: %d\n", pizza->cod, arvbmms->pizza_pos[0]);
    int i = arvbmms->nchaves-1;
    // anda de trás pra frente no nodo chegando as chaves para o lado
    // isso é feito para abrir espaço para a nova chave
    if(arvbmms && arvbmms->folha){
        puts("nodo lido é folha");
        while((i>=0) && (pizza->cod < arvbmms->chave[i])){
            arvbmms->chave[i+1] = arvbmms->chave[i];
            arvbmms->pizza_pos[i+1] = arvbmms->pizza_pos[i];
            i--;
        }

        arvbmms->chave[i+1] = pizza->cod;
        arvbmms->pizza_pos[i+1] = dump_pizza(pizza, pizzaout_filename, catFile_filename);
        printf("Salvando a pizza %d em %d na pos %d do arqv de dados\n", arvbmms->chave[i+1], i+1, arvbmms->pizza_pos[i+1]);
        arvbmms->nchaves++;
        // salva nodo atualizado
        imprime_nodo(arvbmms);
        arvbmsout = reload_file(arvbmsout, arvbmsout_filename, "rb+");
        fseek(arvbmsout, nodo_pos, SEEK_SET);
        printf("atualiza nodo em %lu\n", ftell(arvbmsout));
        salva_nodo(arvbmsout, arvbmms, t);
        // libera_nodo(arvbmms);
        fclose(arvbmsout);
        return nodo_pos;
    }
    puts("nodo lido não é folha");
    // caso não seja folha deve-se encontrar o local certo para inserir
    while((i>=0) && (pizza->cod < arvbmms->chave[i])) i--;
    i++;
    // checa se o filho está cheio
    fseek(arvbmsout, arvbmms->filho[i], SEEK_SET);
    TABMMS* nodo_filho = le_nodo(arvbmsout, t);
    puts("nodo filho antes da inserção");
    imprime_nodo(nodo_filho);

    if(nodo_filho->nchaves == ((2*t)-1)){
        puts("nodo filho está cheio");
        // Nodo filho está cheio
        // arvbmsout = reload_file(arvbmsout, arvbmsout_filename, "rb+");
        // puts("Dividing ...");
        // imprime_nodo(arvbmms);
        // puts("#");
        // novo_nodo = divisao(arvbmsout, novo_nodo, 1, arvbmms, t);
        // puts("To");
        // imprime_nodo(arvbmms);

        arvbmsout = reload_file(arvbmsout, arvbmsout_filename, "rb+");
        fseek(arvbmsout, nodo_pos, SEEK_SET);
        puts("Dividing ...");
        imprime_nodo(nodo_filho);
        puts("#");
        arvbmms->filho[i] = end_fim_do_arqv(arvbmsout);
        arvbmms = divisao(arvbmsout, arvbmms, (i+1), nodo_filho, t);
        puts("To");
        fseek(arvbmsout, arvbmms->filho[i+1], SEEK_SET);
        nodo_filho = le_nodo(arvbmsout, t);
        imprime_nodo(nodo_filho);
        puts("And");
        fseek(arvbmsout, arvbmms->filho[i], SEEK_SET);
        nodo_filho = le_nodo(arvbmsout, t);
        imprime_nodo(nodo_filho);
        fseek(arvbmsout, nodo_pos, SEEK_SET);
        salva_nodo(arvbmsout, arvbmms, t);
        if(pizza->cod > arvbmms->chave[i]) i++;
    }

    fclose(arvbmsout);
    arvbmms->filho[i] = insere_nao_completo(arvbmsout_filename, pizzaout_filename, catFile_filename, pizza, t, arvbmms->filho[i]);
    arvbmsout = fopen(arvbmsout_filename, "rb+");
    fseek(arvbmsout, nodo_pos, SEEK_SET);
    salva_nodo(arvbmsout, arvbmms, t);
    fclose(arvbmsout);
    // libera_nodo(nodo_filho);
    // libera_nodo(arvbmms);
    return nodo_pos;
}

// Insere a pizza no arquivo ou atualiza(caso já exista) a pizza
// retorna True or False
int insere_pizza(char* arvbmsout_filename, char* pizzaout_filename, char* catFile_filename, TPizza* pizza, int t){
    // [ CHECAGEM ]
    // abre arquivo da arvore
    FILE* arvbmsout = fopen(arvbmsout_filename, "rb");
    if(!arvbmsout) exit(1);
    // tenta encontrar a pizza
    int pizza_pos = busca_pizza(arvbmsout, pizza->cod, t);
    fclose(arvbmsout);
    if(pizza_pos != -1){
        //update de pizza
        FILE* pizzaout = fopen(pizzaout_filename, "rb+");
        fseek(pizzaout, pizza_pos, SEEK_SET);
        atualiza_pizza(pizzaout, pizza);
        fclose(pizzaout);
        return false;
    }
    // [ FIM DE CHECAGEM ]

    puts("Pizza nova!");

    // [ INSERE NODO NOVO]
    // abre arquivo
    arvbmsout = fopen(arvbmsout_filename, "rb");
    if(!arvbmsout) exit(1);
    TABMMS* arvbmms = le_nodo(arvbmsout, t);
    // [ INSERE NODO NOVO -> INICIALIZAÇÃO DA ARVORE ]
    if(!arvbmms){
        //arvore vazia
        puts("inicializa arvore!");

        arvbmms = cria_arvore_bmms(t);
        arvbmms->chave[0] = pizza->cod;
        arvbmms->nchaves = 1;
        // printf("Pos da pizza nova %d: %d\n", arvbmms->chave[0], arvbmms->pizza_pos[0]);
        arvbmms->pizza_pos[0] = dump_pizza(pizza, pizzaout_filename, catFile_filename);
        printf("Pos da pizza nova %d: %d\n", arvbmms->chave[0], arvbmms->pizza_pos[0]);

        arvbmsout = reload_file(arvbmsout, arvbmsout_filename, "wb");
        puts("arquivo arvore recarregado rb+");
        // fseek(arvbmsout, 0L, SEEK_SET);
        int resp = salva_nodo(arvbmsout, arvbmms, t);
        // fecha arquivo da arvore
        fclose(arvbmsout);
        // libera_nodo(arvbmms);
        printf("Pizza salva retornando %d\n", resp);
        return true;
    }

    // [ INSERE NODO NOVO -> FIM DE INICIALIZAÇÃO DA ARVORE ]
    // [ INSERE NODO NOVO -> RAIZ CHEIA ]
    if(arvbmms->nchaves == (2*t)-1){ // Raiz cheia
        puts("raiz cheia");
        TABMMS* novo_nodo = cria_arvore_bmms(t);
        novo_nodo->nchaves=0;
        novo_nodo->folha = false;
        // mandaremos o nodo anterior para o fim do arquivo
        novo_nodo->filho[0] = end_fim_do_arqv(arvbmsout);
        // novo_nodo vira raiz da sub arvore
        arvbmsout = reload_file(arvbmsout, arvbmsout_filename, "rb+");
        puts("Dividing ...");
        imprime_nodo(arvbmms);
        puts("#");
        novo_nodo = divisao(arvbmsout, novo_nodo, 1, arvbmms, t);
        puts("To");
        imprime_nodo(arvbmms);
        rewind(arvbmsout); // volta pro inicio do arquivo para salvar a raiz
        salva_nodo(arvbmsout, novo_nodo, t);
        fclose(arvbmsout);
        // libera_nodo(novo_nodo);
        // libera_nodo(arvbmms);
        return insere_nao_completo(arvbmsout_filename, pizzaout_filename, catFile_filename, pizza, t, 0L);
    }
    // [ INSERE NODO NOVO -> FIM DE RAIZ CHEIA ]
    // Raiz ok, segue o baile
    puts("raiz ok");
    fclose(arvbmsout);
    // libera_nodo(arvbmms);
    return insere_nao_completo(arvbmsout_filename, pizzaout_filename, catFile_filename, pizza, t, 0L);
    // [ FIM DE INSERE NODO NOVO ]
}

void libera_nodo(TABMMS* nodo){
    if(nodo){
        free(nodo->chave);
        free(nodo->pizza_pos);
        free(nodo->filho);
        free(nodo);
    }
}

int tamanho_abmms_bytes(int t){
    return sizeof(int)*4 + // nchaves + folha + pizza_pos + prox
        sizeof(int)*t*2 + // *filho
        sizeof(int)*((t*2)-1)*2; // *chave + *pizza_pos
}
