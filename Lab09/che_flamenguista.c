#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "che_flamenguista.h"


/*Checa se a cor de um determinado nó é vermelha

Parâmetro:
no -- ponteiro para a struct nó

Retorno:
1, caso a cor do nó for vermelha, ou 0, caso contrário
*/
int eh_vermelho(p_no no){
    if (no == NULL)
        return 0;

    return no->cor == VERMELHO;
}


/*Checa se a cor de um determinado nó é preta

Parâmetro:
no -- ponteiro para a struct nó

Retorno:
1, caso a cor do nó for preta, ou 0, caso contrário
*/
int eh_preto(p_no no){
    if (no == NULL)
        return 1;

    return no->cor == PRETO;
}


/*Rotaciona a árvore para a esquerda para manter a propriedade de que nós vermelhos sempre são filhos esquerdos

Parâmetro:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)

Retorno:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)
*/
p_no rotaciona_esquerda(p_no raiz){
    //nova_raiz é a variável que representa o nó que será colocado no lugar da raiz original
    p_no nova_raiz = raiz->dir;
    raiz->dir = nova_raiz->esq;
    nova_raiz->esq = raiz;
    nova_raiz->cor = raiz->cor;
    raiz->cor = VERMELHO;

    return nova_raiz;
}


/*Rotaciona a árvore para a direita para manter a propriedade de que os filhos de um nó vermelho sempre são pretos

Parâmetro:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)

Retorno:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)
*/
p_no rotaciona_direita(p_no raiz){
    //nova_raiz é a variável que representa o nó que será colocado no lugar da raiz original
    p_no nova_raiz = raiz->esq;
    raiz->esq = nova_raiz->dir;
    nova_raiz->dir = raiz;
    nova_raiz->cor = raiz->cor;
    raiz->cor = VERMELHO;

    return nova_raiz;
}


/*Sobe a cor vermelha de um nó na árvore para manter a propriedade de que somente o filho esquerdo pode ser vermelho

Parâmetro:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)

Retorno:
void
*/
void sobe_cor_vermelha(p_no raiz){
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}


/*Busca por uma variável na árvore

Parâmetros:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)
nome_variavel -- string que representa o nome de uma variável

Retorno:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)
*/
p_no busca_variavel(p_no raiz, char nome_variavel[]){
    if (raiz == NULL || strcmp(nome_variavel, raiz->nome_variavel) == 0)
        return raiz;

    if (strcmp(nome_variavel, raiz->nome_variavel) < 0)
        return busca_variavel(raiz->esq, nome_variavel);

    else
        return busca_variavel(raiz->dir, nome_variavel);
}


/*Insere recursivamente um novo nó na árvore

Ao final da inserção, verifica as possíveis correções necessárias para manter as propriedades desse tipo de árvore

Parãmetros:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)
nome_variavel -- string que representa o nome de uma variável
tipo_variavel -- string que representa o tipo de uma variável

Retorno:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)
*/
p_no insere_recursivamente(p_no raiz, char nome_variavel[], char tipo_variavel[]){
    //novo nó que será inserido na árvore
    p_no novo_no;

    if (raiz == NULL){
        novo_no = malloc(sizeof (struct no));
        novo_no->esq = novo_no->dir = NULL;
        strcpy(novo_no->nome_variavel, nome_variavel);
        strcpy(novo_no->tipo_variavel, tipo_variavel);
        novo_no->cor = VERMELHO;
        return novo_no;
    }

    if (strcmp(nome_variavel, raiz->nome_variavel) < 0)
        raiz->esq = insere_recursivamente(raiz->esq, nome_variavel, tipo_variavel);

    else
        raiz->dir = insere_recursivamente(raiz->dir, nome_variavel, tipo_variavel);

    if (eh_vermelho(raiz->dir) && eh_preto(raiz->esq))
        raiz = rotaciona_esquerda(raiz);
    if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->esq->esq))
        raiz = rotaciona_direita(raiz);
    if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->dir))
        sobe_cor_vermelha(raiz);

    return raiz;
}


/*Insere um novo nó na árvore

Mantém a raiz preta e chama uma função que inserirá recursivamente na árvore, fazendo os demais ajustes necessários

Parâmetros:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)
nome_variavel -- string que representa o nome de uma variável
tipo_variavel -- string que representa o tipo de uma variável

Retorno:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)
*/
p_no insere_arvore(p_no raiz, char nome_variavel[], char tipo_variavel[]){
    raiz = insere_recursivamente(raiz, nome_variavel, tipo_variavel);
    raiz->cor = PRETO;
    return raiz;
}


/*Imprime as variáveis da árvore em ordem alfabética

Parâmetro:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)

Retorno:
void
*/
void imprime_arvore(p_no raiz){
    if (raiz != NULL){
        imprime_arvore(raiz->esq);
        printf("%s %s\n", raiz->nome_variavel, raiz->tipo_variavel);
        imprime_arvore(raiz->dir);
    }
}


/*Libera a memória alocada para a árvore durante o programa

Parãmetro:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)

Retorno:
void    
*/
void libera_arvore(p_no raiz){
    if (raiz == NULL)
        return;
    
    libera_arvore(raiz->esq);
    libera_arvore(raiz->dir);
    free(raiz);
}
