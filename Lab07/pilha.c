#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "peca.h"


/*Inicializa a pilha com base em seu tamanho na simulação

Parâmetro:
tam_pilha -- tamanho fixo que a pilha terá durante a simulção

Retorno:
pilha -- ponteiro para a struct pilha
*/
p_pilha cria_pilha(int tam_pilha){
    p_pilha pilha = malloc(sizeof (struct pilha));
    pilha->tam_pilha = tam_pilha;
    pilha->usado = 0;
    pilha->topo = NULL;

    return pilha;
}


/*Verifica se há espaço na pilha para a entrada de uma nova peça

Parâmetro:
pilha -- ponteiro para a struct pilha

Retorno:
1, caso haja espaço suficiente na pilha, ou 0, caso contrário
*/
int cabe_na_pilha(p_pilha pilha){
    if (pilha->usado < pilha->tam_pilha)
        return 1;

    return 0;
}


/*Verifica se a pilha está vazia

Parâmetro:
pilha -- ponteiro para a struct pilha

Retorno:
1, caso a pilha esteja vazia, ou 0, caso contrário
*/
int pilha_vazia(p_pilha pilha){
    if (pilha->usado == 0)
        return 1;

    return 0;
}


/*Coloca uma nova peça na pilha 

Parâmetro:
pilha -- ponteiro para a struct pilha
peca -- ponteiro para a struct peça

Retorno:
void
*/
void empilha(p_pilha pilha, p_peca peca){
    p_no novo_no = malloc(sizeof (struct no));
    novo_no->peca = peca;
    novo_no->prox = pilha->topo;
    pilha->topo = novo_no;
    pilha->usado++;
}


/*Retira da pilha a peça do topo, a qual foi pega pelo embalador

Parâmetro:
pilha -- ponteiro para a struct pilha

Retorno:
peca_retiara -- ponteiro para a struct peça que representa a peça que foi pega pelo empacotador (ou seja, agora ela está em sua mão)
*/
p_peca desempilha(p_pilha pilha){
    p_no topo = pilha->topo;
    p_peca peca_retirada = topo->peca;
    pilha->topo = pilha->topo->prox;
    pilha->usado--;
    free(topo);

    return peca_retirada;
}


/*Libera a memória alocada para a pilha durante a simulação

Parâmetro:
pilha -- ponteiro para a struct pilha

Retorno:
void
*/
void libera_no(p_no topo){
    if (topo != NULL)
        free(topo);
}
