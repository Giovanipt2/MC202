#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "heap.h"


#define MAX 40


/*Verifica se há a quantidade de panelas suficiente para atender todos os pedidos feitos na rodada

Parâmetros:
n_panelas -- número de panelas disponíveis para serem usadas
n_pedidos -- número de pedidos feitos na rodada

Retorno:
1, caso tenha, ou 0, caso contrário (número de pedidos maior que o número de panelas)
*/
int tem_panela_suficiente(int n_panelas, int n_pedidos){
    if (n_panelas >= n_pedidos)
        return 1;

    return 0;
}


/*Encontra a posição na linha em que o nome do prato começa

Parâmetro:
linha -- string que representa a linha lida na entrada do programa

Retorno:
Posição de início do nome do prato na linha
*/
int posicao_inicio_prato(char linha[]){
    int i;

    for (i = 0; linha[i] != '\0'; i++){
        if (isupper(linha[i]))
            break;;
    }
    return i;
}


/*Copia o nome do prato obtido na linha para a variável que será usada para criá-lo

Parâmetros:
pos_inicio -- posição em que o nome do prato começa na string que representa a linha
linha -- string que representa a linha lida na entrada do programa
nome_prato -- string que representa o nome do prato lido

Retorno:
void
*/
void copia_nome_prato(int pos_inicio, char linha[], char nome_prato[]){
    for (int i = 0; linha[pos_inicio + i] != '\n'; i++){
        nome_prato[i] = linha[pos_inicio + i];
    }
}


int main(){
    //respectivamente, os números de panelas e de sobreviventes
    int n_panelas, n_sobreviventes;
    scanf("%d %d", &n_panelas, &n_sobreviventes);

    p_fila_prio f_prio = cria_fila_prio(n_sobreviventes);           //heap que será usado para ordenar a prioridade dos sobreviventes
    p_fila_prio fila_chegada = cria_fila_prio(n_sobreviventes);     //fila que será usada para guardar o ID de cada sobrevivente  (ordem de chegada)

    //respectivamente, o nome e o sobrenome do sobrevivente que foi lido
    char nome_sobrevivente[16], sobrenome_sobrevivente[16];
    int dias_sobrevividos;          //quantidade de dias sobrevivida pelo sobreviveente

    for (int i = 0; i < n_sobreviventes; i++){
        scanf("%s %s %d", nome_sobrevivente, sobrenome_sobrevivente, &dias_sobrevividos);
        p_sobrevivente sobrevivente = cria_sobrevivente(nome_sobrevivente, sobrenome_sobrevivente, dias_sobrevividos);
        insere_fila_chegada(fila_chegada, sobrevivente);
    }

    int n_comandos, contador_rodadas = 1;           //quantidade de comandos dados para a cozinha e o contador de rodadas
    scanf("%d ", &n_comandos);

    char linha[MAX];                //linha de entrada que será lida
    char comando[8];                //string que representa o comando dado ("novo" ou "altera")
    int id;                         //ID (posição na fila de chegada) do sobrevivente que sofrerá alguma mudança
    int n_pedidos = 0;              //número de pedidos da rodada

    while (n_comandos != 0 || f_prio->n_elementos != 0){
        for (int i = 0; i < n_comandos; i++){
            fgets(linha, MAX, stdin);
            sscanf(linha, "%s %d", comando, &id);

            if (strcmp(comando, "novo") == 0){
                char nome_prato[27] =  "";              //string que representa o nome do prato lido
                int pos_inicio_prato = posicao_inicio_prato(linha);
                copia_nome_prato(pos_inicio_prato, linha, nome_prato);      //extrai, da linha, o nome do prato
                p_prato prato = cria_prato(nome_prato);
                adiciona_prato(prato, fila_chegada, id);
                //sobrevivente que fez um pedido será inserido no heap
                p_sobrevivente sobrevivente_inserido = fila_chegada->vetor_sobreviventes[id];
                insere_no_heap(f_prio, sobrevivente_inserido);
                n_pedidos++;
            }

            else{
                int valor_acrescentado;
                sscanf(linha, "%s %d %d", comando, &id, &valor_acrescentado);
                altera_prioridade(valor_acrescentado, fila_chegada, f_prio, id);
            }
        }

        printf("---- rodada %d ----\n", contador_rodadas);

        if (tem_panela_suficiente(n_panelas, f_prio->n_elementos)){
            for (int i = 0; i < n_pedidos; i++){
                p_sobrevivente sobrevivente_max = extrai_maximo(f_prio);
                printf("%s %s %s %d\n", sobrevivente_max->nome, sobrevivente_max->sobrenome, 
                    sobrevivente_max->prato_pedido->nome_prato, sobrevivente_max->chave_prio);
                libera_prato(sobrevivente_max->prato_pedido);
                reseta_prioridade(sobrevivente_max);
            }
            n_pedidos = 0;
        }

        else{
            for (int i = 0; i < n_panelas; i++){
                p_sobrevivente sobrevivente_max = extrai_maximo(f_prio);
                printf("%s %s %s %d\n", sobrevivente_max->nome, sobrevivente_max->sobrenome, 
                    sobrevivente_max->prato_pedido->nome_prato, sobrevivente_max->chave_prio);
                libera_prato(sobrevivente_max->prato_pedido);
                reseta_prioridade(sobrevivente_max);
                n_pedidos--;
            }
        }
        contador_rodadas++;

        if (n_comandos != 0)
            scanf("%d ", &n_comandos);
    }

    libera_heap(f_prio);
    libera_heap(fila_chegada);

    return 0;
}
