#include "pilha.h"


typedef struct fila Fila;


Fila* fila_cria (void);

Fila* filas_junta (Fila* p, Fila* n, Fila* u);

void fila_imprime (Fila* f);

void fila_libera (Fila* f);

void aluno_pega_bandeja(Fila* f, Pilha* p);

void aluno_cadastra (Fila* f);

void aluno_serve(Fila* f);