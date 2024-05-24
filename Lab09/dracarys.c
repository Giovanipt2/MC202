#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "che_flamenguista.h"


//Criado para facilitar a leitura do código, permitindo saber que tipo de linha está sendo analisada
enum tipo_de_linha {DECLARACAO, OPERACAO, NDA};


/*Ajusta a linha lida do buffer, retirando o ponto e vírgula ou o \n do final da linha

Parâmetro:
string -- vetor de caracteres que será ajustado

Retorno:
void
*/
void ajusta_string(char string[]){
    for (int i = 1; string[i - 1] != '\0'; i++){
        if (string[i] == '\n' || string[i] == ';')
            string[i] = '\0';
    }
}


/*Verifica qual o tipo da linha analisada com base em seus elementos

Caso a linha comece com um caractere que não é uma letra ou contenha parênteses, ela não deve ser analisada (apenas contada)

Se ela possuir um igual, trata-se de uma operação. Caso contrário, tem-se uma declaração

Parâmetros:
buffer -- string que guarda uma linha toda de entrada do programa
tipo_linha -- variável do tipo enum tipo_de_linha que representa o tipo da linha que está sendo analisada
simb1 -- string que guarda o primeiro símbolo lido na linha
simb2 -- string que guarda o segundo símbolo lido na linha
simb3 -- string que guarda o terceiro símbolo lido na linha

Retorno:
tipo_linha -- variável do tipo enum tipo_de_linha que representa o tipo da linha que está sendo analisada
*/
enum tipo_de_linha verifica_tipo_linha(char buffer[], enum tipo_de_linha tipo_linha, char simb1[], char simb2[], char simb3[]){
    sscanf(buffer, "%s %s %s", simb1, simb2, simb3);

    if(simb2[0] == '=')
        tipo_linha = OPERACAO;

    else if (!isalpha(simb1[0]) || simb2[4] == '(' || simb3[0] == '(')
        tipo_linha = NDA;

    else if (strcmp(simb1, "int") == 0 || strcmp(simb1, "float") == 0 ||
        strcmp(simb1, "double") == 0 || strcmp(simb1, "char") == 0)
        tipo_linha = DECLARACAO;

    return tipo_linha;
}


/*Verifica se uma operação ou uma atribuição é válida considerando os tipos das variáveis envolvidas

Parâmetros:
tipo_variavel1 -- string que armazena o tipo da primeira variável em análise
tipo_variavel2 -- string que armazena o tipo da segunda variável em análise

Retorno:
1, caso a operação seja válida; ou 0, caso contrário
*/
int operacao_valida(char tipo_variavel1[], char tipo_variavel2[]){
    if (strcmp(tipo_variavel1, tipo_variavel2) == 0)
        return 1;

    return 0;
}


/*Verifica se houve erro na linha em análise e de qual tipo foi

Já imprime os erros presentes, caso exista algum

Parâmetros:
contador_linhas -- número inteiro que representa qual o número da linha que está sendo analisada
no_simb1 -- nó que está armazenando o simb1 na árvore
no_simb2 -- nó que está armazenando o simb2 na árvore
no_simb3 -- nó que está armazenando o simb3 na árvore
operador -- caractere que representa o operador utilizado na linha que representa uma operação
simb1 -- string que guarda o primeiro símbolo lido na linha
simb2 -- string que guarda o segundo símbolo lido na linha
simb3 -- string que guarda o terceiro símbolo lido na linha

Retorno:
1, caso haja pelo menos um erro na linha em análise; ou 0, caso contrário
*/
int verifica_erros_linha(int contador_linhas, p_no no_simb1, p_no no_simb2, p_no no_simb3, char operador, char simb1[], char simb2[], char simb3[]){
    int teve_erro = 0;      //variável que guarda se houve ou não erro na linha analisada

    if (no_simb1 == NULL){
        printf("Linha %d: o símbolo %s não foi definido.\n", contador_linhas, simb1);
        teve_erro = 1;
    }

    else if (no_simb2 == NULL){
        printf("Linha %d: o símbolo %s não foi definido.\n", contador_linhas, simb2);
        teve_erro = 1;
    }

    else if (no_simb3 == NULL){
        printf("Linha %d: o símbolo %s não foi definido.\n", contador_linhas, simb3);
        teve_erro = 1;
    }

    else if (!operacao_valida(no_simb2->tipo_variavel, no_simb3->tipo_variavel)){
        printf("Linha %d: tipos incompatíveis: %s (%s) %c %s (%s).\n", contador_linhas, no_simb2->nome_variavel, 
            no_simb2->tipo_variavel, operador, no_simb3->nome_variavel, no_simb3->tipo_variavel);
        teve_erro = 1;
    }

    else if (!operacao_valida(no_simb1->tipo_variavel, no_simb2->tipo_variavel)){
        printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, obteve %s.\n", contador_linhas, 
            no_simb1->nome_variavel, no_simb1->tipo_variavel, no_simb2->tipo_variavel);
        teve_erro = 1;
    }

    return teve_erro;
}


int main(){
    //respectivamente, o local para armazenar a linha lida, os símbolos lidos e o operador que pode existir caso se tenha uma operação
    char buffer[MAX], simb1[MAX], simb2[MAX], simb3[MAX], operador;
    //respectivamente, um contador de erros presentes no código de entrada e um contador de linhas
    int contador_erros = 0, contador_linhas = 0;
    enum tipo_de_linha tipo_linha;          //variável que armazenará o tipo da linha que está sendo lida

    p_no raiz = NULL;       //raiz da árvore que será usada 

    while (fgets(buffer, MAX, stdin) != NULL){
        //as três linhas abaixo reinicializam as strings para que a linha passada não interfira na continuidade do código
        simb1[0] = '\0';
        simb2[0] = '\0';
        simb3[0] = '\0';
        tipo_linha = NDA;       //reseta o tipo da linha na leitura de uma nova linha

        contador_linhas++;
        tipo_linha = verifica_tipo_linha(buffer, tipo_linha, simb1, simb2, simb3);

        if (tipo_linha == DECLARACAO){
            ajusta_string(simb2);
            raiz = insere_arvore(raiz, simb2, simb1); 
        }   

        else if (tipo_linha == OPERACAO){
            sscanf(buffer, "%s = %s %c %s", simb1, simb2, &operador, simb3);
            ajusta_string(simb3);
            //variáveis que armazenarão os nós em que se encontram cada um dos símbolos, no caso em que eles foram declarados
            p_no no_simb1, no_simb2, no_simb3;

            no_simb1 = busca_variavel(raiz, simb1);
            no_simb2 = busca_variavel(raiz, simb2);
            no_simb3 = busca_variavel(raiz, simb3);

            //variável que guarda se houve ou não erro na linha analisada
            int teve_erro = verifica_erros_linha(contador_linhas, no_simb1, no_simb2, no_simb3, operador, simb1, simb2, simb3);

            contador_erros += teve_erro;
        }
    }

    if (contador_erros == 0)
        printf("Não há erros de tipo.\n");

    imprime_arvore(raiz);
    libera_arvore(raiz);

    return 0;
}
