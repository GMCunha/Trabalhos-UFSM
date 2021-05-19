#include <stdlib.h>
#include <stdio.h>

#include "fila.h"

struct no {
    int info;
    int bandeja;
    struct no* prox;
};
typedef struct no No;

struct fila {
    No* ini;
    No* fim;
};

static int fila_vazia (Fila* f);
static void no_imprime(No* no);
static void fila_insere (Fila* f, int v);
static int fila_retira (Fila* f);

Fila* fila_cria (void){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

static int fila_vazia (Fila* f){
    return (f->ini == NULL);
}

void aluno_cadastra (Fila* f){
    int ticket;
    printf("Digite o ticket do aluno: ");
    scanf("%d", &ticket);
    setbuf(stdin, NULL);
    printf("Aluno inserido na fila!\n");
    fila_insere(f, ticket);
}

static void fila_insere (Fila* f, int v){
    No* n = (No*) malloc(sizeof (No));

    n->info = v;   
    n->prox = NULL;      
    n->bandeja = 0;

    if (f->fim != NULL) {
        f->fim->prox = n;
    } else {
        f->ini = n;
    }   
    f->fim = n;               
}

int fila_tamanho(Fila* f) {
    No* no = f->ini;
    int cont = 0;
    while(no != NULL){
        no = no->prox;
        cont++;
    }
    return cont;
}

static int fila_retira (Fila* f){
    if (fila_vazia(f)) {
        return 0;                 
    }

    No* t = f->ini;
    int v = t->info;
    f->ini = t->prox;

    if (f->ini == NULL) {
        f->fim = NULL;
    }        
    free(t);

    return v;
}

void fila_libera (Fila* f){
    No* q = f->ini;
    while (q != NULL) {
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
}

Fila* filas_junta (Fila* p, Fila* n, Fila* u){
    int cont = fila_tamanho(u);
    while(!fila_vazia(p) && cont < 10){
        fila_insere(u, fila_retira(p));
        cont++;
    }
    while(!fila_vazia(n) && cont < 10){
        fila_insere(u, fila_retira(n));
        cont++;
    }
    return u;
}

void aluno_pega_bandeja(Fila* f, Pilha* p) {
    if (pilha_vazia (p)){
        printf("A pilha de bandejas esta vazia, aguarde reposicao.\n");
        return;
    }
    if (fila_vazia (f)){
        printf("A fila unica esta vazia!\n");
        return;
    }

    No* aluno = f->ini;

    while (aluno->bandeja > 0) {
        if (aluno == NULL){
            printf("Todos os alunos da fila unica ja pegaram bandeja!\n");
            return;
        }

        aluno = aluno->prox;
    }

    aluno->bandeja = pilha_retira(p);
}

static void no_imprime(No* no) {
    if (!no) return;

    printf("Ticket No: %d\n", no->info);
}

void fila_imprime(Fila* f) {
    if (fila_vazia(f)){
        printf("A fila esta vazia!\n");
        return;
    }

    No* no = f->ini;
    while (no) {
        no_imprime(no);
        no = no->prox;
    }
}

void aluno_serve(Fila* f){
    if (fila_vazia(f)){
        printf("A fila esta vazia!\n");
        return;        
    }

    if (f->ini->bandeja > 0){
        fila_retira(f);
    } else {
        printf("O aluno ainda nao pegou bandeja!\n");
    }
}

