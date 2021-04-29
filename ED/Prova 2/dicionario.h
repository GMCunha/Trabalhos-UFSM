// o dicionário propriamente dito.
typedef struct dicionario Dicionario;

//uma entrada do dicionário.
typedef struct entrada {
    char * str;
    int freq;
}Entrada;

// Funcoes do dicionario

Dicionario* criaDicionario();
void removeDicionario(Dicionario* dic);
void adicionarEntrada(Dicionario* dic, char* str);
Entrada** exportaEntrada(Dicionario* dic);

// Funcao de lista encadeada

int lista_tamanho(Dicionario* dic);