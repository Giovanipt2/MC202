#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_ligada.h"


p_lista_ligada cria_lista_livros(){
    p_lista_ligada lista_livros = malloc(sizeof(struct lista_ligada));
    lista_livros->inicio = lista_livros->fim = lista_livros->ultimo_add = NULL;
    return lista_livros;
}


/*Ajusta o formato da string, retirando o espaço em branco desnecessário e o '\n', ajustando a posição do '\0'

Parâmetro:
livro -- string que representa o nome do livro em questão

Retorno:

*/
void ajusta_string(char livro[]){
    int i;

    for (i = 1; livro[i] != '\0'; i++){
        if (livro[i] == '\n'){
            livro[i - 1] = '\0';
            break;
        }
       
        else
            livro[i - 1] = livro[i];
    }
}


/*Encontra a posição de inserção do livro na lista ligada, considerando os comandos dados anteriormente

Parâmetros:
comando_passado -- string que representa qual a função que foi chamada anteriormente

Retorno:
posicao -- caractere que indica onde na lista de livros deve ocorrer a inserção do novo livro
*/
char encontra_posicao_add(char comando_passado[]){
    char posicao;

    if (strcmp(comando_passado, "inicio") == 0)
        posicao = 'i';

    else if (strcmp(comando_passado, "final") == 0)
        posicao = 'f';

    else
        posicao = 'd';

    return posicao;
}


/*Adiciona o livro pedido na lista de livros na posição pedida

Parâmetros:
lista_livros -- ponteiro para a struct lista_ligada que representa a lista de livros de Wickerbottom
comando_passado -- string que representa qual a função que foi chamada anteriormente
livro -- string que representa o nome do livro em questão

Retorno:
lista_livros -- ponteiro para a struct lista_ligada que representa a lista de livros de Wickerbottom
*/
p_lista_ligada adiciona_livro(p_lista_ligada lista_livros, char comando_passado[], char livro[]){
    p_no novo_no = malloc(sizeof(struct no));                   //novo nó que será adicionado na lista ligada
    strcpy(novo_no->livro, livro);
    char posicao = encontra_posicao_add(comando_passado);       //posição de inserção do livro na lista, podendo ser 'i', significando no início, 'f', fim e 'd', depois do último adicionado

    if (lista_livros->ultimo_add == NULL && lista_livros->inicio != NULL){
        novo_no->ant = NULL;
        novo_no->prox = lista_livros->inicio;
        lista_livros->inicio = lista_livros->ultimo_add = novo_no;
        return lista_livros;
    }

    if (posicao == 'f'){
        if (lista_livros->inicio == NULL){
            lista_livros->inicio = lista_livros->fim = lista_livros->ultimo_add = novo_no;
            novo_no->prox = novo_no->ant = NULL;
        }

        else{
            novo_no->prox = NULL;
            novo_no->ant = lista_livros->fim;
            lista_livros->fim->prox = novo_no;
            lista_livros->fim = lista_livros->ultimo_add = novo_no;
        }
    }

    else if (posicao == 'i'){
        if (lista_livros->inicio == NULL){
            lista_livros->inicio = lista_livros->fim = lista_livros->ultimo_add = novo_no;
            novo_no->prox = novo_no->ant = NULL;
        }

        else{
            novo_no->ant = NULL;
            novo_no->prox = lista_livros->inicio;
            lista_livros->inicio = lista_livros->ultimo_add = novo_no;
        }
    }

    else{
        if (lista_livros->inicio == NULL){
            lista_livros->inicio = lista_livros->fim = lista_livros->ultimo_add = novo_no;
            novo_no->prox = novo_no->ant = NULL;
        }

        else{
            if (lista_livros->ultimo_add == lista_livros->fim){
                novo_no->prox = NULL;
                novo_no->ant = lista_livros->fim;
                lista_livros->fim->prox = novo_no;
                lista_livros->fim = lista_livros->ultimo_add = novo_no;
            }

            else{
                novo_no->ant = lista_livros->ultimo_add;
                novo_no->prox = lista_livros->ultimo_add->prox;
                lista_livros->ultimo_add->prox->ant = novo_no;
                lista_livros->ultimo_add->prox = novo_no;
                lista_livros->ultimo_add = novo_no;
            }
        }
    }
    return lista_livros;
}


/*Busca e remove o pedido da lista de livros

Parâmetro:
lista_livros -- ponteiro para a struct lista_ligada que representa a lista de livros de Wickerbottom
livro_removido -- string que representa o livro que vai ser retirado da lista

Retorno:
lista_livros -- ponteiro para a struct lista_ligada que representa a lista de livros de Wickerbottom
*/
p_lista_ligada remove_livro(p_lista_ligada lista_livros, char livro_removido[]){
    p_no livro_atual, livro_aux;    //respectivamente, o nó que vai sendo atualizado dentro do "for", e o nó que guarda o livro que vai ser retirado

    if (strcmp(lista_livros->inicio->livro, livro_removido) == 0){
        livro_aux = lista_livros->inicio;
        lista_livros->inicio = lista_livros->inicio->prox;
        lista_livros->inicio->ant = NULL;
        livro_atual = NULL;
    }

    else if (strcmp(lista_livros->fim->livro, livro_removido) == 0){
        livro_aux = lista_livros->fim;
        lista_livros->fim = lista_livros->fim->ant;
        lista_livros->fim->prox = NULL;
        livro_atual = lista_livros->fim;
    }

    else{
        for (livro_atual = lista_livros->inicio; strcmp(livro_atual->prox->livro, livro_removido) != 0; livro_atual = livro_atual->prox);
        livro_aux = livro_atual->prox;
        livro_atual->prox = livro_atual->prox->prox;
        livro_atual->prox->ant = livro_atual;
    }

    if (livro_aux == lista_livros->ultimo_add)
        lista_livros->ultimo_add = livro_atual;

    free(livro_aux);
    
    return lista_livros;
}


/*Imprime os livros da lista com base na posição em que foram colocados

Parâmetro:
lista_livros -- ponteiro para a struct lista_ligada que representa a lista de livros de Wickerbottom

Retorno:
void
*/
void imprime_lista(p_lista_ligada lista_livros){
    p_no livro_atual;
    for (livro_atual = lista_livros->inicio; livro_atual != NULL; livro_atual = livro_atual->prox){
        if (livro_atual->prox != NULL)
            printf("%s, ", livro_atual->livro);

        else
            printf("%s", livro_atual->livro);
    }
    printf("\n");
}


/*Libera cada um dos nós da lista de livros utilizada

Parâmetro:
lista_livros -- ponteiro para a struct lista_ligada que representa a lista de livros de Wickerbottom

Retorno:
void
*/
void libera_lista(p_no livro_atual){
    if (livro_atual != NULL){
        libera_lista(livro_atual->prox);
        free(livro_atual);
    }
}


/*Decide qual função será chamda com base no comando dado

Parâmetros:
lista_livros -- ponteiro para a struct lista_ligada que representa a lista de livros de Wickerbottom
ultimo_comando -- salva o ultimo comando 
comando -- string que representa qual a função que se deseja chamar

Retorno:
void
*/
void decide_funcao(p_lista_ligada lista_livros, char comando_passado[], char comando[]){
    if (strcmp(comando, "adicionar") == 0){
        //respectivamemte, o livro a ser inserido, e o lugar de inserção dele na lista ('i' para início, 'f' para fim e 'd' para depois do último alocado)
        char livro[60];   
        fgets(livro, sizeof(livro), stdin);
        ajusta_string(livro);
        lista_livros = adiciona_livro(lista_livros, comando_passado, livro);
    }

    else if (strcmp(comando, "remover") == 0){
        char livro_removido[60];
        fgets(livro_removido, sizeof(livro_removido), stdin);
        ajusta_string(livro_removido);
        lista_livros = remove_livro(lista_livros, livro_removido);
        
    }

    else    
        imprime_lista(lista_livros);
}
