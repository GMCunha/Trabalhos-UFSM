#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"
#include "fila.h"
#include "menu.h"

void main(void){
    Fila* fila_normal = fila_cria();
    Fila* fila_prioridade = fila_cria();
    Fila* fila_unica = fila_cria();
    Pilha* pilha_bandejas = pilha_cria();

    while(1){
        int opcao = menu_esc();
        menu(&fila_normal, &fila_prioridade, &fila_unica, &pilha_bandejas, opcao);
    }
}