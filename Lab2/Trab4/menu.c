#include <stdlib.h>
#include <stdio.h>

#include "menu.h"

void menu(Fila** fila_normal, Fila** fila_prioridade, Fila** fila_unica, Pilha** pilha_bandejas, int opcao) {
    switch(opcao){
        case 1:
            aluno_cadastra (*fila_normal);
            break;
        case 2:
            aluno_cadastra (*fila_prioridade);
            break;
        case 3:
            *fila_unica = filas_junta (*fila_prioridade, *fila_normal, *fila_unica);
            break;
        case 4:
            bandeja_cadastra (*pilha_bandejas);
            break;
        case 5:
            aluno_pega_bandeja(*fila_unica, *pilha_bandejas);
            break;
        case 6:
            aluno_serve(*fila_unica);         
            break;
        case 7:
            printf("\nFila normal:\n");
            fila_imprime (*fila_normal);
            printf("\nFila prioritaria:\n");
            fila_imprime (*fila_prioridade);
            printf("\nFila unica:\n");
            fila_imprime (*fila_unica);
            printf("\nPilha de bandejas:\n");
            pilha_imprime (*pilha_bandejas);
            break;
        case 8:
            printf("Fechando programa.\n");
            fila_libera (*fila_normal);
            fila_libera (*fila_prioridade);
            fila_libera (*fila_unica);
            pilha_libera (*pilha_bandejas);
            exit(0);
    }

}

int menu_esc() {
    int escolha = -1;

    while (escolha < 1 || escolha > 8) {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Inserir aluno normal;\n");
        printf("2 - Inserir aluno prioritario;\n");
        printf("3 - Fundir filas;\n");
        printf("4 - Colocar bandeja na pilha;\n");
        printf("5 - Aluno retira bandeja;\n");
        printf("6 - Retirar aluno da fila;\n");
        printf("7 - Imprimir filas;\n");
        printf("8 - Sair do programa.\n");

        scanf(" %d", &escolha);
        setbuf(stdin, NULL);
    }

    return escolha;
}

