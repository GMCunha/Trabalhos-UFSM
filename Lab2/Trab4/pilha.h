typedef struct pilha Pilha;


Pilha* pilha_cria (void);


void pilha_libera (Pilha* p);

int pilha_retira (Pilha* p);

void pilha_imprime (Pilha* p);

int pilha_vazia (Pilha* p);

void bandeja_cadastra (Pilha* p);