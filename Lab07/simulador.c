#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "fila.h"
#include "funcionario.h"


int main(){
    int tam_esteira, tam_pilha, n_entradas;         //respectivamente, o tamanho da esteira, o tamanho pilha e o número de entradas da simulação
    scanf("%d %d", &tam_esteira, &tam_pilha);
    scanf("%d", &n_entradas);

    p_fila fila_espera = cria_fila(n_entradas);     //ponteiro para a struct fila que armazena todas as entradas
    le_entradas_simulacao(fila_espera);             //função que preenche a fila de espera com as peças da simulação
    p_fila esteira = cria_fila(tam_esteira);        //ponteiro para a struct fila que simula a esteira do programa
    p_pilha pilha = cria_pilha(tam_pilha);          //ponteiro para a struct pilha que simula a pilha do programa

    p_funcionario classificador = cria_funcionario('c');    //ponteiro para a struct funcionario que faz o papel do classificador
    p_funcionario embalador = cria_funcionario('e');        //ponteiro para a struct funcionario que faz o papel do embalador        
    p_peca peca_largada;

    printf("##### Simulação\n");

    //variáveis que representam, respectivamente, o tempo de atraso da simulação, e os minutos que uma peça está no processo de classificação/embalagem
    int t_atraso = 0, mins_classificacao = 0, mins_embalagem = 0;
    //variáveis que serão utilizadas, respectivamente, para contabilizar os minutos passados na simulação e para contar a quantidade de peças que já foram processadas
    int mins = 1, contador_pecas_liberadas = 0;
    //variáveis que serão utilizadas para representar a entrada e saída de peças da esteira, da pilha e dos processos de classificação e embalagem
    int entrou_esteira = 0, saiu_classificacao = 0, entrou_pilha = 0, saiu_embalagem = 0;
        
    while (contador_pecas_liberadas < n_entradas){
        if (!mao_vazia(embalador)){
            if (acabou_processamento(embalador, mins_embalagem)){
                peca_largada = larga_peca(embalador);
                contador_pecas_liberadas++;
                mins_embalagem = 0;
                saiu_embalagem = 1;
                libera_peca(peca_largada);

                if (contador_pecas_liberadas == n_entradas){
                    printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n", mins, entrou_esteira, saiu_classificacao, entrou_pilha, saiu_embalagem);
                    printf("Tempo atraso: %d.\n", t_atraso);
                    break;
                }
            }
            else{
                mins_embalagem++;
            }
        }

        if (!pilha_vazia(pilha) && mao_vazia(embalador)){
            peca_largada = desempilha(pilha);
            pega_peca(embalador, peca_largada);
            mins_embalagem++;
        }

        if (!mao_vazia(classificador)){
            if (acabou_processamento(classificador, mins_classificacao)){
                if (cabe_na_pilha(pilha)){
                    peca_largada = larga_peca(classificador);
                    mins_classificacao = 0;
                    saiu_classificacao = 1;
                    empilha(pilha, peca_largada);
                    entrou_pilha = 1;
                }
            }
            else{
                mins_classificacao++;
            }
        }

        if (!fila_vazia(esteira) && mao_vazia(classificador)){
            peca_largada = remove_esteira(esteira);
            pega_peca(classificador, peca_largada);
            mins_classificacao++;
        }

        if (!fila_vazia(fila_espera)){
            if (cabe_na_esteira(esteira)){
                peca_largada = remove_fila_espera(fila_espera);
                adiciona_esteira(esteira, peca_largada);
                entrou_esteira = 1;
            }

            else{
                t_atraso++;
            }
        }

        printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n", mins, entrou_esteira, saiu_classificacao, entrou_pilha, saiu_embalagem);

        mins++;
        entrou_esteira = saiu_classificacao = entrou_pilha = saiu_embalagem = 0;
    }
    
    libera_fila(fila_espera);
    libera_fila(esteira);
    libera_no(pilha->topo);
    free(pilha);
    ferias(classificador);
    ferias(embalador);

    return 0;
}
