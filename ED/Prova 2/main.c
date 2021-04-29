#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dicionario.h"

// Protoipos
Entrada** teste(Dicionario* dic, char* str, int grao);

void imprime_entrada(Dicionario* dic, Entrada** vet);

int obtem_grao(int size);

char* obtem_string();
char* retorna_string_p(char* aux);

// ------------------------------------

Entrada** teste(Dicionario* dic, char* str, int grao){
    int i, size;
    size = strlen(str) + 1;

    char** aux = (char**)malloc(sizeof(char*)*(size-grao)); 
    /* Estou armazenando os diferentes graos da string eh um vetor de strings,
    isso porque depois de tentar usar um unico ponteiro de char, altera-lo para
    guardar o proximo grao, alterava seu valor em todos as outros ocorrencias no codigo, 
    inclusive onde ele ja estava armazenado dentro do dicionario, o que fazia com que 
    no teste de frequencia o grao testado sempre era igual ao armazenado*/

    for (i = 0; i < size - grao; i++){
        aux[i] = (char*)malloc(sizeof(char)*(grao+1));
        strncpy(aux[i], str+i, grao); // Copia para aux[i] grao caracteres a partir de str+i
        aux[i][grao] = '\0';
        adicionarEntrada(dic, aux[i]);
    }
    
    free(aux);
    /* Os ponteiros dentro do vetor aux serao desalocados junto com a funcao removeDicionario*/
    return exportaEntrada(dic);
}

void imprime_entrada(Dicionario* dic, Entrada** vet){
    int i, size;
    size = lista_tamanho(dic);
    for (i = 0; i < size; i++){
        printf("%s\t%d\n", vet[i]->str, vet[i]->freq);
    }
}

int obtem_grao(int size){
    int grao = 0; // grao = 0 para entrar no laco a primeira vez
    while (grao < 1 || grao > size) {
        printf("Informe o tamanho do grao: \n");
        scanf("%d", &grao);
    }
    return grao;
}

char* obtem_string(){
    char aux[100];
    printf("Informe uma string de ate 100 caracteres: \n");
    scanf(" %100[^\n]", aux); // Caracteres diferentes de letras tambem serao aceitos

    return retorna_string_p(aux);
}

char* retorna_string_p(char* aux){
    int size = strlen(aux);
    char *str = (char*)malloc(sizeof(char)*(size+1));
    strcpy(str, aux);
    return str;
}

int main(){
    int i = 0, size, grao;
    Dicionario* dic = criaDicionario();
    //char str[] = "TORPOR";

    char* str = obtem_string();
    
    grao = obtem_grao(strlen(str));

    Entrada** vet = teste(dic, str, grao);

    imprime_entrada(dic, vet);

    free(vet);
    free(str);
    removeDicionario(dic);
}