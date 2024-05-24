#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_binaria.h"


/*Cria os nós da árvore binária, que conterão os elementos da expressão dada

Parâmetros:
elemento -- caractere que será colocado no dado do nó
esq -- ponteiro para a struct nó que aponta para o filho esquerdo de um nó pai
dir -- ponteiro para a struct nó que aponta para o filho direito de um nó pai

Retorno:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)
*/
p_no cria_no(char elemento, p_no esq, p_no dir){
    p_no raiz = malloc(sizeof(struct no));
    raiz->dado = elemento;
    raiz->esq = esq;
    raiz->dir = dir;

    return raiz;
}


/*Decide se um caractere é um número ou não

Importante para saber se é possível realizar algumas comparações específicas

Parâmetro:
caractere -- um caractere da expressão de entrada, o qual será classificado como operador ou não

Retorno:
1, caso seja um número, ou 0, caso contrário
*/
int eh_numero(char caractere){
    if (caractere >= '0' && caractere <= '9')
        return 1;
        
    return 0;
}


/*Decide se um caractere é um operador ou não

Importante para que os operadores sejam colocados na árvore de tal sorte que seus filhos esquerdo e direito sejam os seus operandos

Parâmetro:
caractere -- um caractere da expressão de entrada, o qual será classificado como operador ou não

Retorno:
1, caso ele seja um operador, ou 0, caso contrário
*/
int eh_operador(char caractere){
    switch (caractere){
        case '=':
        case '!':
        case '<':
        case '>':
        case '{':
        case '}':
        case '&':
        case '|':
            return 1;
            break;

        default:
            return 0;
            break;
    }
}


/*Otimiza a expressão contida na árvore, liberando os nós filhos quando a otimização é possível

Parâmetro:
raiz -- ponteiro que aponta para a struct nó que representa a raiz de uma árvore (ou subárvore)

Retorno:
raiz -- ponteiro que aponta para a struct nó que representa a raiz de uma árvore (ou subárvore). Agora, após a otimização
*/
p_no otimiza_expressao(p_no raiz){
    if (raiz == NULL){
        return raiz;
    }
    //dado da raiz que está sendo analisada. Variável que será usada para saber se foi possível otimizar ou não
    char dado_atual = raiz->dado;

    raiz->esq = otimiza_expressao(raiz->esq);
    raiz->dir = otimiza_expressao(raiz->dir);

    if (raiz->dado == '|'){
        if (raiz->esq->dado == 'T' || raiz->dir->dado == 'T'){
            raiz->dado = 'T';
        }
    }

    else if (raiz->dado == '&'){
        if (raiz->esq->dado == 'F' || raiz->dir->dado == 'F'){
            raiz->dado = 'F';
        }
    }

    else if (raiz->dado == '{'){
        if (raiz->dir->dado == '9'){
            raiz->dado = 'T';
        }

        else if (raiz->esq->dado == '0'){
            raiz->dado = 'T';
        }

        else if (!eh_operador(raiz->esq->dado) && !eh_operador(raiz->dir->dado)){
            if (eh_numero(raiz->esq->dado) && eh_numero(raiz->dir->dado)){
                if (raiz->esq->dado <= raiz->dir->dado){
                    raiz->dado = 'T';
                }
            
                else{
                    raiz->dado = 'F';
                }
            }
            else if (raiz->esq->dado == raiz->dir->dado){
                raiz->dado = 'T';
            }
        }
    }
    else if (raiz->dado == '}'){
        if (raiz->dir->dado == '0'){
            raiz->dado = 'T';
        }

        else if (raiz->esq->dado == '9'){
            raiz->dado = 'T';
        }

        else if (!eh_operador(raiz->esq->dado) && !eh_operador(raiz->dir->dado)){
            if (eh_numero(raiz->esq->dado) && eh_numero(raiz->dir->dado)){
                if (raiz->esq->dado >= raiz->dir->dado){
                    raiz->dado = 'T';
                }
            
                else{
                    raiz->dado = 'F';
                }
            }
            else if (raiz->esq->dado == raiz->dir->dado){
                raiz->dado = 'T';
            }
        }
    }
    else if (raiz->dado == '>'){
        if (raiz->dir->dado == '9'){
            raiz->dado = 'F';
        }

        else if (raiz->esq->dado == '0'){
            raiz->dado = 'F';
        }
        
        else if (!eh_operador(raiz->esq->dado) && !eh_operador(raiz->dir->dado)){
            if (eh_numero(raiz->esq->dado) && eh_numero(raiz->dir->dado)){
                if (raiz->esq->dado > raiz->dir->dado){
                    raiz->dado = 'T';
                }
            
                else{
                    raiz->dado = 'F';
                }
            }
            else if (raiz->esq->dado == raiz->dir->dado){
                raiz->dado = 'F';
            }
        }
    }
    else if (raiz->dado == '<'){
        if (raiz->dir->dado == '0'){
            raiz->dado = 'F';
        }

        else if (raiz->esq->dado == '9'){
            raiz->dado = 'F';
        }

        else if (!eh_operador(raiz->esq->dado) && !eh_operador(raiz->dir->dado)){
            if (eh_numero(raiz->esq->dado) && eh_numero(raiz->dir->dado)){
                if (raiz->esq->dado < raiz->dir->dado){
                    raiz->dado = 'T';
                }
            
                else{
                    raiz->dado = 'F';
                }
            }
            else if (raiz->esq->dado == raiz->dir->dado){
                raiz->dado = 'F';
            }
        }
    }
    else if (raiz->dado == '='){
        if (!eh_operador(raiz->esq->dado) && !eh_operador(raiz->dir->dado)){
            if (eh_numero(raiz->esq->dado) && eh_numero(raiz->dir->dado)){
                if (raiz->esq->dado == raiz->dir->dado){
                    raiz->dado = 'T';
                }
            
                else{
                    raiz->dado = 'F';
                }
            }
            else if (raiz->esq->dado == raiz->dir->dado){
                raiz->dado = 'T';
            }
        }
    }

    else if (raiz->dado == '!'){
        if (!eh_operador(raiz->esq->dado) && !eh_operador(raiz->dir->dado)){
            if (eh_numero(raiz->esq->dado) && eh_numero(raiz->dir->dado)){
                if (raiz->esq->dado != raiz->dir->dado){
                    raiz->dado = 'T';
                }
            
                else{
                    raiz->dado = 'F';
                }
            }
            else if (raiz->esq->dado == raiz->dir->dado){
                raiz->dado = 'F';
            }
        }
    }
    
    if (raiz->dado != dado_atual){
        libera_filhos(raiz);
    }


    return raiz;
}


/*Imprime a expressão da forma correta, considerando os parênteses

Parâmetro:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)

Retorno:
void
*/
void imprime_expressao(p_no raiz){
    if (raiz != NULL){
        if (raiz->esq != NULL || raiz->dir != NULL){
            printf("(");
            imprime_expressao(raiz->esq);
            printf(" ");
        }
        
        printf("%c", raiz->dado);

        if (raiz->esq != NULL || raiz->dir != NULL){
            printf(" ");
            imprime_expressao(raiz->dir);
            printf(")");
        }
    }
}


/*Libera os filhos de uma raiz caso a otimização tenha sido possível

Parâmetro:
raiz -- ponteiro para a struct nó que representa a raiz de uma árvore (ou subárvore)

Retorno:
void
*/
void libera_filhos(p_no raiz){
    libera_arvore(raiz->esq);
    libera_arvore(raiz->dir);
    raiz->esq = raiz->dir = NULL;
}


/*Libera a memória alocada para a árvore durante o programa

Parâmetro:
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
