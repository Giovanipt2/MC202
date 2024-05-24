#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "peca.h"


/*Inicializa a esteira com base em seu tamanho na simulação

Parâmetro:
tam_esteira -- tamanho fixo que a esteira (fila) terá durante a simulação

Retorno:
esteira -- ponteiro para a struct fila
*/
p_fila cria_fila(int tam_fila){
    p_fila fila;
    fila = malloc(sizeof(struct fila));
    fila->vetor_pecas = malloc(tam_fila * sizeof(p_peca));
    fila->ini = fila->fim = 0;
    fila->usado = 0;
    fila->tam_fila = tam_fila;

    return fila;
}


/*Verifica se há espaço suficiente na esteira para a entrada de uma nova peça

Parâmetro:
esteira -- ponteiro para a struct fila

Retorno:
1, caso haja espaço suficiente na esteira, ou 0, caso contrário
*/
int cabe_na_esteira(p_fila esteira){
    if (esteira->usado < esteira->tam_fila)
        return 1;

    return 0;
}


/*Verifica se a fila está vazia

Parâmetro:
fila -- ponteiro para a struct fila

Retorno:
1, caso a fila esteja vazia, ou 0, caso contrário
*/
int fila_vazia(p_fila fila){
    if (fila->usado == 0)
        return 1;

    return 0;
}


/*Preenche a fila de espera com as entradas da simulação, de forma que seja possível controlar o tempo de entradas das peças na esteira

Parâmetro:
fila_espera -- ponteiro para a struct fila que armazena todas as entradas

Retorno:
void
*/
void le_entradas_simulacao(p_fila fila_espera){
    char tamanho_peca[10];          //string que representa o tamanho da peça (pequena, média ou grande)
    int tipo_peca;                  //número inteiro que indica se a peça é do tipo 1 ou 2

    for (int i = 0; i < fila_espera->tam_fila; i++){
        scanf("%s %d", tamanho_peca, &tipo_peca);
        p_peca peca = cria_peca(tamanho_peca, tipo_peca);

        fila_espera->fim++;
        fila_espera->usado++;
        fila_espera->vetor_pecas[i] = peca;
    }
}


/*Adiciona uma nova peça à esteira

Parâmetros:
esteira -- ponteiro para a struct fila
peca -- ponteiro para a struct peça

Retorno:
void
*/
void adiciona_esteira(p_fila esteira, p_peca peca){
    esteira->vetor_pecas[esteira->fim] = peca;
    esteira->fim = (esteira->fim + 1) % esteira->tam_fila;
    esteira->usado++;
}


/*Retira uma peça da fila de espera, a qual foi colocada na esteira

Parâmetro:
fila_espera -- ponteiro para a struct fila que armazena todas as entradas

Retorno:
peca_retirada -- ponteiro para a struct peça que representa a peça que foi colocada na esteira
*/
p_peca remove_fila_espera(p_fila fila_espera){
    p_peca peca_retirada = fila_espera->vetor_pecas[fila_espera->ini];
    fila_espera->ini = fila_espera->ini + 1;
    fila_espera->usado--;

    return peca_retirada;
}


/*Retira uma peça da esteira, a qual foi pega pelo classficador

Parâmetro:
esteira -- ponteiro para a struct fila

Retorno:
peca_retiara -- ponteiro para a struct peça que representa a peça que foi pega pelo classificador (ou seja, agora ela está em sua mão)
*/
p_peca remove_esteira(p_fila esteira){
    p_peca peca_retirada = esteira->vetor_pecas[esteira->ini];
    esteira->ini = (esteira->ini + 1) % esteira->tam_fila;
    esteira->usado--;

    return peca_retirada;
}


/*Libera a memória alocada para a esteira durante a simulação

Parâmetro:
esteira -- ponteiro para a struct fila

Retorno:
void
*/
void libera_fila(p_fila fila){
    free(fila->vetor_pecas);
    free(fila);
}
