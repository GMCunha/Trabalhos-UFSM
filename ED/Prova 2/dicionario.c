#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dicionario.h"

// Structs 

typedef struct no{
    struct no * pai;
    struct no * esq;
    struct no * dir;
    Entrada * entrada;
}No;

struct dicionario{
    No* inicio;
    int entradas;
};

//  ----------------------------------

//  Prototipos de funcoes

static No* no_cria(char* str);

static void no_libera(No* atual);
static void entrada_bubble(Entrada** vet, int size);
static int no_insere_ordenado(char* str, No* atual, Dicionario* dic);

static Entrada* entrada_cria(char *str);
static Entrada** entrada_vet_inicializa(No* atual, int size);
static int entrada_vet_i(No* atual, Entrada** vet, int i);

static int arvore_tamanho(No* no);
static int arvore_fator_bal(No* no);
static No* arvore_pivo(No* no);
static void arvore_balancear(Dicionario* dic, No* no, char* str);
static void rotacao_simples_esquerda(Dicionario* dic, No* pivo, No* mover);
static void rotacao_simples_direita(Dicionario* dic, No* pivo, No* mover, char* str);

// ----------------------------------

// Funcoes relacionadas ao dicionario

Dicionario* criaDicionario(){
    Dicionario* dic = (Dicionario*)malloc(sizeof(Dicionario));
    dic->inicio = NULL;
    dic->entradas = 0;
    return dic; // retorna dicionario zerado e alocado
}

void removeDicionario(Dicionario* dic){
    no_libera(dic->inicio); // libera as entradas do dicionario
    free(dic); // libera o dicionario
}

void adicionarEntrada(Dicionario* dic, char* str){
    if (dic->inicio == NULL) { // Caso em que o dicionario esta vazio
        dic->inicio = no_cria(str);
        dic->entradas = 1;
    }
    else // soma 1 ao total de entradas caso uma nova seja adicionada
        dic->entradas += no_insere_ordenado(str, dic->inicio, dic);

    No* pivo = arvore_pivo(dic->inicio); // se a arvore nao estiver balanceada, retorna o pivo

    if (pivo)
        arvore_balancear(dic, pivo, str); // faz o balanceamento da arvore a partir do pivo
}

// ----------------------------------

// Funcoes relacionadas a arvore

static int no_insere_ordenado(char* str, No* atual, Dicionario* dic){
    if (strcmp(str, atual->entrada->str) == 0){
        atual->entrada->freq++; // Soma as ocorrencia da entrada
        return 0; // retorna
    }

    if (strcmp(str, atual->entrada->str) > 0){ // Caso em que a string eh maior que a entrada atual
        if (atual->dir == NULL){ // Caso em que nao existe no a direita
            No* novo = no_cria(str);
            novo->pai = atual;
            atual->dir = novo;
            return 1; // retorna
        }
        else {
            return no_insere_ordenado(str, atual->dir, dic); //segue indo a direita
        }
    }
    else { // Caso em que a string eh menor que a entrada atual
        if (atual->esq == NULL){ // Caso em que nao existe no a esquerda
            No* novo = no_cria(str);
            novo->pai = atual;
            atual->esq = novo;
            return 1; // retorna
        }
        else {
            return no_insere_ordenado(str, atual->esq, dic); //segue indo a esquerda
        }
    }
}

int lista_tamanho(Dicionario* dic){
    return dic->entradas; // retorna numero de entradas
}

static No* no_cria(char* str){
    No* novo = (No*)malloc(sizeof(No));
    novo->entrada = entrada_cria(str);
    novo->pai = NULL;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo; // retorna o no alocado
}

static void no_libera(No* atual){
    if (!atual) return;

    No* aux1 = atual->esq; // salva os nos filhos
    No* aux2 = atual->dir; 

    free(atual->entrada->str);
    free(atual->entrada);
    atual->entrada = NULL; // libera entrada e atual
    free(atual);
    atual = NULL;

    no_libera(aux1); // libera os filhos
    aux1 = NULL;
    no_libera(aux2);
    aux2 = NULL;
}

// ------------------------------

// Funcoes relacionadas a balanceamento

static int arvore_tamanho(No* no) {
    if (!no) return 0;

    int esq = arvore_tamanho(no->esq);
    int dir = arvore_tamanho(no->dir);

    if (esq > dir) return (esq + 1); // retorna a maior subarvore de no
    else return (dir + 1);
}

static int arvore_fator_bal(No* no) {
    if (!no) return 0;

    int esq = arvore_tamanho(no->esq);
    int dir = arvore_tamanho(no->dir);

    return (esq-dir); // retorna a diferenca entre as maiores subarvores de no
}

static No* arvore_pivo(No* no) {
    if (!no) return NULL; // se no nao existir retorna NULL
    
    No* f = arvore_pivo(no->esq); // salva f como o no a esquerda caso tenha pivo
    if (!f) // se o no a esquerda nao tiver pivo, faz o mesmo com a direita
        f = arvore_pivo(no->dir);

    int dif = arvore_fator_bal(no); // verifica a diferenca de altura das subarvores de no

    if(dif<-1 || dif>1)
        f = no;

    return f; // retorna f
}

static void arvore_balancear(Dicionario* dic, No* no, char* str) {
    int teste = arvore_fator_bal(no);
    int neto;   // variavel para descobrir a direcao do neto
    if (no->esq){
        neto = arvore_fator_bal(no->esq);// descobre qual a maior subarvore do no a esquerda
        if ((teste > 1) && (neto > 0)) {// se o no a esquerda tiver mais subarvores a esquerda, a rotacao eh simples
            rotacao_simples_direita(dic, no, no->esq, str);
            return;
        }
        if ((teste > 1) && (neto < 0)) {// se o no a esquerda tiver mais subarvores a direita, a rotacao eh dupla
            rotacao_simples_esquerda(dic, no->esq, no->esq->dir);//rota para esquerda
            rotacao_simples_direita(dic, no, no->esq, str);//rota para direita
            return;
        }
    }
    
    if (no->dir) {
        neto = arvore_fator_bal(no->dir);// descobre qual a maior subarvore no no a direita
        if ((teste < -1) && (neto < 0)) {// se o no a direita tiver mais subarvores a direita, a rotacao eh simples
            rotacao_simples_esquerda(dic, no, no->dir);
            return;
        }
        if ((teste < -1) && (neto > 0)) {// se o no a direita tiver mais subarvores a esquerda, a rotacao eh dupla
            rotacao_simples_direita(dic, no->dir, no->dir->esq, str);//rota para direita
            rotacao_simples_esquerda(dic, no, no->dir);//rota para a esquerda
            return;
        }
    }
}

static void rotacao_simples_esquerda(Dicionario* dic, No* pivo, No* mover) {
    No* aux = mover->esq; // salva o endereco a esquerda (no ou NULL)
    No* pai = pivo->pai; // salva o endereco pai (no ou NULL)

    pivo->dir = aux;
    if (aux) // associa aux a direita de pivo e, caso exista no em aux, salva pivo como pai
        aux->pai = pivo;

    mover->esq = pivo; // salva pivo a esquerda do no sendo movido
    pivo->pai = mover;

    if (dic->inicio == pivo) // associa o no movido como raiz da arvore caso pivo o fosse anteriormente
        dic->inicio = mover;
    else { // caso contrario pivo tem pai, entao o no movido eh associado como filho do mesmo
        mover->pai = pai;
        if (pai->dir == pivo)
            pai->dir = mover;
        if (pai->esq == pivo)
            pai->esq = mover;
    }
}

static void rotacao_simples_direita(Dicionario* dic, No* pivo, No* mover, char* str) {
    No* aux = mover->dir; // salva o endereco a direita (no ou NULL)
    No* pai = pivo->pai; // salva o endereco pai (no ou NULL)

    pivo->esq = aux;
    if (aux) // associa aux a direita de pivo e, caso exista no em aux, salva pivo como pai
        aux->pai = pivo;

    mover->dir = pivo; // salva pivo a direita do no sendo movido
    pivo->pai = mover;

    if (dic->inicio == pivo) // associa o no movido como raiz da arvore caso pivo o fosse anteriormente
        dic->inicio = mover;
    else { // caso contrario pivo tem pai, entao o no movido eh associado como filho do mesmo
        mover->pai = pai;
        if (pai->dir == pivo)
            pai->dir = mover;
        if (pai->esq == pivo)
            pai->esq = mover;
    }
}

// ------------------------------

// Funcoes relacionadas a Entrada

Entrada** exportaEntrada(Dicionario* dic){
    No* atual = dic->inicio;
    int size;

    size = lista_tamanho(dic);

    Entrada** vet = entrada_vet_inicializa(atual, size); // cria e associa o vetor de entradas
    
    entrada_bubble(vet, size); // organiza baseado em frequencia

    return vet; // retorna o vetor
}

static Entrada* entrada_cria(char *str){
    Entrada* nova = (Entrada*)malloc(sizeof(Entrada));
    nova->str = str;
    nova->freq = 1;

    return nova; // retorna uma nova entrada
}

static void entrada_bubble(Entrada** vet, int size){
    int i, j;
    Entrada* aux;
    for (i = 0; i < size; i++) {
        for (j = i; j < size; j++) {
            if (vet[i]->freq < vet[j]->freq) {
                aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
    }
}

static Entrada** entrada_vet_inicializa(No* atual, int size){
    Entrada** vet = (Entrada**)malloc(size*sizeof(Entrada*));
    int i = 0;

    entrada_vet_i(atual, vet, i); // associa valores ao vetor

    return vet; // retorna o vetor
}


static int entrada_vet_i(No* atual, Entrada** vet, int i) {
    if (!atual) return i;

    int ni = i;

    vet[ni] = atual->entrada; // salva o vetor na posicao atual
    ni++; // incrementa posicao atual

    if (atual->esq)
        ni = entrada_vet_i(atual->esq, vet, ni); // define ni como a posicao atual depois de salvar os valores a esquerda
    
    if (atual->dir)
        ni = entrada_vet_i(atual->dir, vet, ni); // define ni como a posicao atual depois de salvar os valores a direita

    return ni; // retorna posicao atual
}