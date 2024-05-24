#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "arvore_binaria.h"


/*Cria a pilha que será usada para montar a árvore posteriormente

Retorno:
pilha -- ponteiro para a struct pilha
*/
p_pilha cria_pilha(){
    p_pilha pilha = malloc(sizeof (struct pilha));
    pilha->vetor_nos = malloc(8 * sizeof(p_no));
    pilha->n_dados = 0;
    pilha->alocado = 8;
    pilha->topo = 0;

    return pilha;
}


/*Aumenta o tamanho da pilha quando necessário

Parâmetro:
pilha -- ponteiro para a struct pilha

Retorno:
void
*/
void expande_pilha(p_pilha pilha){
    p_no *vetor_temp;           //vetor temporário de nós que será usado para armazenar as informações do original enquanto seu tamanho é alterado
    int i;

    vetor_temp = pilha->vetor_nos;
    pilha->alocado *= 2;
    pilha->vetor_nos = malloc(pilha->alocado * sizeof(p_no));

    for (i = 0; i < pilha->alocado / 2; i++)
        pilha->vetor_nos[i] = vetor_temp[i];
    
    free(vetor_temp);
}   


/*Reduz o tamanho da pilha quando menos de 1/4 de seu tamanho sendo usado

Parâmetro:
pilha -- ponteiro para a struct pilha

Retorno:
void
*/
void reduz_pilha(p_pilha pilha){
    p_no *vetor_temp;           //vetor temporário de nós que será usado para as informações do original enquanto seu tamanho é alterado
    int i;

    vetor_temp = pilha->vetor_nos;
    pilha->alocado /= 2;
    pilha->vetor_nos = malloc(pilha->alocado * sizeof(p_no));

    for (i = 0; i < pilha->alocado / 2; i++)
        pilha->vetor_nos[i] = vetor_temp[i];
    
    free(vetor_temp);
}


/*Coloca um novo elemento no topo da pilha

Parâmetros:
pilha -- ponteiro para a struct pilha
elemento -- ponteiro para a struct nó que representa o elemento

Retorno:
void
*/
void empilha(p_pilha pilha, p_no elemento){
    if (pilha->n_dados == pilha->alocado)
        expande_pilha(pilha);
    
    pilha->vetor_nos[pilha->topo] = elemento;
    pilha->topo++;
    pilha->n_dados++;
}


/*Remove o elemento que está no ponto da pilha

Parâmetro:
pilha -- ponteiro para a struct pilha

Retorno:
elemento -- ponteiro para a struct nó que representa o elemento
*/
p_no desempilha(p_pilha pilha){
    p_no elemento;
    elemento = pilha->vetor_nos[pilha->topo - 1];
    pilha->topo--;
    pilha->n_dados--;

    if (pilha->n_dados <= (pilha->alocado / 4) && pilha->alocado > 8)
        reduz_pilha(pilha);

    return elemento;
}


/*Libera a memória alocada para a pilha durante o programa

Parãmetro:
pilha -- ponteiro para a struct pilha

Retorno:
void
*/
void libera_pilha(p_pilha pilha){
    free(pilha->vetor_nos);
    free(pilha);
}
