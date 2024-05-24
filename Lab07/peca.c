#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peca.h"


/*Calcula o tempo necessário para a classificação da peça ser finalizada, com base em seu tamanho

Parâmetro:
peca -- ponteiro para a struct peça

Retorno:
Número inteiro que representa o tempo necessário para que a peça seja classificada
*/
int calcula_tempo_classificacao(p_peca peca){
    if (strcmp(peca->tamanho, "grande") == 0)
        return 3;

    else if (strcmp(peca->tamanho, "media") == 0)
        return 2;

    return 1;
}


/*Calcula o tempo necessário para embalar a peça, com base no seu tipo

Parâmetro:
peca -- ponteiro para a struct peça

Retorno:
void
*/
int calcula_tempo_embalagem(p_peca peca){
    if (strcmp(peca->tamanho, "pequena") == 0){
        if (peca->tipo == 1)
            return 1;

        return 2;
    }

    if (peca->tipo == 1)
        return 2;

    return 3;
}


/*Inicializa a peça com base na entrada da simulação

Parâmetros:
tamanho_peca -- string que representa o tamanho da peça (pequena, média ou grande)
tipo_peca -- número inteiro que diz se a peça é do tipo 1 ou 2

Retorno:
peca -- ponteiro para a struct peça
*/
p_peca cria_peca(char tamanho_peca[], int tipo_peca){
    p_peca peca = malloc(sizeof(struct peca));
    strcpy(peca->tamanho, tamanho_peca);
    peca->tipo = tipo_peca;
    //inicialização usada apenas para que não ocorram erros na passagem de "peca" para as funções que calculam o tempo adequadamente
    peca->t_classificacao = peca->t_embalagem = 0;             
    peca->t_classificacao = calcula_tempo_classificacao(peca);
    peca->t_embalagem = calcula_tempo_embalagem(peca);

    return peca;
}


/*Libera a memória alocada para a peça

Parâmetro:
peca -- ponteiro para a struct peça

Retorno:
void
*/
void libera_peca(p_peca peca){
    free(peca);
}
