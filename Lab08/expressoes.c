#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "arvore_binaria.h"


/*Lê a expressão dada, a fim de montar a árvore que possibilitará sua otimização

Parâmetro;
pilha -- ponteiro para a struct pilha, que auxiliará no preenchimento da árvore

Retorno:
raiz -- ponteiro para a struct nó que representa a raiz da árvore que será utilizada
*/
p_no le_expressao(p_pilha pilha){
    char caractere;         //caractere da expressão que será colocado na árvore binária
    //respectivamente, o a raiz de um nó que está sendo criado, e seus filhos esquerdo e direito
    p_no raiz, filho_esq, filho_dir;

    scanf("%c", &caractere);
    while (caractere != '\n'){
        if (eh_operador(caractere)){
            filho_dir = desempilha(pilha);
            filho_esq = desempilha(pilha);
            raiz = cria_no(caractere, filho_esq, filho_dir);
            empilha(pilha, raiz);
        }

        else{
            raiz = cria_no(caractere, NULL, NULL);
            empilha(pilha, raiz);
        }
        scanf("%c", &caractere);     //repetição necessária para que o while pare corretamente ao ler o final da expressão
    }
    raiz = desempilha(pilha);

    return raiz;
}


int main(){
    int n_expressoes;           //número de operações que devem ser otimizadas no programa
    scanf("%d\n", &n_expressoes);

    for (int i = 0; i < n_expressoes; i++){
        p_no raiz = NULL;                   //a raiz da árvore binária que será utilizada começa como NULL
        p_pilha pilha = cria_pilha();       //pilha que será usada para o preenchimento correto da árvore
        raiz = le_expressao(pilha);         //função para preencher a árvore com os caracteres da expressão dada
        imprime_expressao(raiz);
        printf("\n");                       //printf necessaŕio para pular linha de uma expressão para a outra
        otimiza_expressao(raiz);
        imprime_expressao(raiz);
        printf("\n");                       //printf necessaŕio para pular linha de uma expressão para a outra
        libera_pilha(pilha);
        libera_arvore(raiz);
        printf("\n");                       //printf necessaŕio para pular linha de uma expressão para a outra
    }

    return 0;
}
