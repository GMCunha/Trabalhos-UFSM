#include <stdlib.h>
#include <stdio.h>

#include "pilha.h"

struct no{
   int info;
   struct no* prox;
};
typedef struct no No;

struct pilha {
   No* prim;
};

static void pilha_insere (Pilha* p, int idnt);

Pilha* pilha_cria (void){
   Pilha* p = (Pilha*) malloc(sizeof(Pilha));
   p->prim = NULL;
   return p;
}

void pilha_libera (Pilha* p){
    No* n = p->prim;

    while (n != NULL) {
        No* aux = n->prox;
        free(n);
        n = aux;
    }
    free(p);
}

int pilha_vazia (Pilha* p){
    return (p->prim == NULL);
}

void bandeja_cadastra (Pilha* p){
    int idnt = 0;
    while(idnt <= 0){
        printf("Digite o identificador da bandeja (Deve ser diferente de 0): ");
        scanf("%d", &idnt);
        setbuf(stdin, NULL);
    }
    printf("Bandeja colocada na pilha!\n");
    pilha_insere(p, idnt);
}

static void pilha_insere (Pilha* p, int idnt){
    No* n = (No*) malloc(sizeof (No));

    n->info = idnt;
    n->prox = p->prim;
    p->prim = n;
}

int pilha_retira (Pilha* p){
    No* n;
    int i;
    
    n = p->prim;
    i = n->info;
    p->prim = n->prox;
    free(n);

    return i;
}

void pilha_imprime (Pilha* p){
    No* n;

    if (pilha_vazia(p)){
        printf("A pilha esta vazia!\n");
        return;
    }
    
    n = p->prim;
    
    while (n != NULL){
        printf("ID No: %d\n", n->info);
        n = n->prox;
    }
}
