#include "peca.h"


typedef struct pilha *p_pilha;          //ponteiro para a struct fila
typedef struct no *p_no;                //ponteiro para a struct no

struct pilha{
    p_no topo;                          //ponteiro que aponta para o nó mais de cima da pilha
    int usado, tam_pilha;               //respectivamente, quantos espaços estão sendo usados e quanto foi alocado, com base na entrada da simulação
};

struct no{
    p_peca peca;                        //ponteiro para a struct peça
    p_no prox;                          //ponteiro para o próximo nó da lista ligada
};


/*Inicializa a pilha com base em seu tamanho dado na simulação*/
p_pilha cria_pilha(int tam_pilha);

/*Verifica se há espaço na pilha para a entrada de uma nova peça*/
int cabe_na_pilha(p_pilha pilha);

/*Verifica se a pilha está vazia*/
int pilha_vazia(p_pilha pilha);

/*Coloca uma nova peça na pilha*/
void empilha(p_pilha pilha, p_peca peca);

/*Retira da pilha a peça do topo, a qual foi pega pelo embalador*/
p_peca desempilha(p_pilha pilha);

/*Libera a memória alocada para a pilha durante a simulação*/
void libera_no(p_no topo);
