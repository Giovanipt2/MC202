#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"


/*Cria a pilha que será usada para fazer busca em profundidade no grafo

Retorno:
pilha -- ponteiro para a struct pilha
*/
p_pilha cria_pilha(){
    p_pilha pilha = malloc(sizeof (struct pilha));
    pilha->v_vertices = malloc(20 * sizeof(int));
    pilha->n_vertices = 0;
    pilha->alocado = 20;
    pilha->topo = 0;

    return pilha;
}


/*Verifica se a pilha está vazia

Parâmetro:
pilha -- ponteiro para a struct pilha

Retorno:
1, caso a pilha esteja vazia; ou 0, caso contrário
*/
int pilha_vazia(p_pilha pilha){
    if (pilha->n_vertices == 0)
        return 1;

    return 0;
}


/*Coloca um novo vértice no topo da pilha

Parâmetros:
pilha -- ponteiro para a struct pilha
vértice -- número inteiro que representa um vértice do grafo

Retorno:
void
*/
void empilha(p_pilha pilha, int vertice){
    pilha->v_vertices[pilha->topo] = vertice;
    pilha->topo++;
    pilha->n_vertices++;
}


/*Remove o elemento que está no ponto da pilha

Parâmetro:
pilha -- ponteiro para a struct pilha

Retorno:
vértice -- número inteiro que representa um vértice do grafo
*/
int desempilha(p_pilha pilha){
    int vertice;

    vertice = pilha->v_vertices[pilha->topo - 1];
    pilha->topo--;
    pilha->n_vertices--;

    return vertice;
}


/*Libera a memória alocada para a pilha durante o programa

Parãmetro:
pilha -- ponteiro para a struct pilha

Retorno:
void
*/
void libera_pilha(p_pilha pilha){
    free(pilha->v_vertices);
    free(pilha);
}
