#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"


/*Cria a fila que será utilizada para fazer busca em largura no grafo

Retorno:
fila -- ponteiro para a struct fila
*/
p_fila cria_fila(){
    p_fila fila;
    fila = malloc(sizeof(struct fila));
    fila->v_vertices = malloc(20 * sizeof(int));
    fila->ini = fila->fim = 0;
    fila->n_vertices = 0;
    fila->alocado = 20;

    return fila;
}


/*Verifica se a fila está vazia

Parâmetro:
fila -- ponteiro para a struct fila

Retorno:
1, caso a fila esteja vazia, ou 0, caso contrário
*/
int fila_vazia(p_fila fila){
    if (fila->n_vertices == 0)
        return 1;

    return 0;
}


/*Adiciona um novo vértice na fila

Parâmetros:
esteira -- ponteiro para a struct fila
vertice -- número inteiro que representa um vértice do grafo

Retorno:
void
*/
void enfileira(p_fila fila, int vertice){
    fila->v_vertices[fila->fim] = vertice;
    fila->fim = (fila->fim + 1) % fila->alocado;
    fila->n_vertices++;
}


/*Retira um vértice da fila

Parâmetro:
fila -- ponteiro para a struct fila

Retorno:
vertice -- número inteiro que representa um vértice do grafo
*/
int desenfileira(p_fila fila){
    int vertice = fila->v_vertices[fila->ini];
    fila->ini = (fila->ini + 1) % fila->alocado;
    fila->n_vertices--;

    return vertice;
}


/*Libera a memória alocada para a fila

Parâmetro:
fila -- ponteiro para a struct fila

Retorno:
void
*/
void libera_fila(p_fila fila){
    free(fila->v_vertices);
    free(fila);
}
