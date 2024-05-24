#ifndef pilha_h
#define pilha_h

#include "arvore_binaria.h"

typedef struct pilha *p_pilha;

struct pilha{
    p_no *vetor_nos;                //vetor de nós da pilha, onde serão guardados os elementos da expressão dada
    int topo, n_dados, alocado;     //respectivamente, a posição de topo da pilha (local de inserção), o número de posições que está sendo utilizada e a quantidade de posições alocadas
};


/*Cria a pilha que será usada para montar a árvore posteriormente*/
p_pilha cria_pilha();

/*Aumenta o tamanho da pilha quando necessário*/
void expande_pilha(p_pilha pilha);

/*Reduz o tamanho da pilha quando menos de 1/4 de seu tamanho sendo usado*/
void reduz_pilha(p_pilha pilha);

/*Coloca um novo elemento no topo da pilha*/
void empilha(p_pilha pilha, p_no elemento);

/*Remove o elemento que está no ponto da pilha*/
p_no desempilha(p_pilha pilha);

/*Libera a memória alocada para a pilha durante o programa*/
void libera_pilha(p_pilha pilha);

#endif
