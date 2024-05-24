#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "grafo.h"

#define MAX 20      //Número máximo de vértices que podem estar contidos no grafo


int main(){
    p_grafo g = cria_grafo(MAX);
    int operacao;           //Número inteiro que representa a operação dada ao programa

    scanf("%d", &operacao);

    while (operacao >= 1 && operacao <= 6){
        if (operacao == 1){
            int ID_vertice;        //ID (ou número) do vértice
            scanf(" %d", &ID_vertice);  //Nada precisa ser feito pois o grafo já é criado com espaço para todos os vértices
            g->n_vertices++;
        }

        else if (operacao == 2){
            int v1, v2;     //Vértices que terão uma aresta conectando-os
            scanf(" %d %d", &v1, &v2);
            insere_aresta(g, v1 - 1, v2 - 1);   //Precisa dessa correção (-1), já que, no grafo, o primeiro vértice é 0
        }

        else if (operacao == 3){
            int v1, v2;     //Vértices que terão sua aresta desfeita
            scanf(" %d %d", &v1, &v2);
            retira_aresta(g, v1 - 1, v2 - 1);
        }

        else if (operacao == 4){
            int v1, v2;     //Vértices que terão sua conexão checada
            scanf(" %d %d", &v1, &v2);
            if (tem_caminho(g, v1 - 1, v2 - 1))
                printf("Existe conexão entre os nós.\n");

            else
                printf("Não existe conexão entre os nós.\n");
        }

        else if (operacao == 5){
            int v1, v2;     //Vértices para os quais se deseja encontrar um caminho mínimo
            scanf(" %d %d", &v1, &v2);

            if (!tem_caminho(g, v1 - 1, v2 - 1))
                printf("Não existe conexão entre os nós.\n");

            else{
                int * pai = encontra_menor_caminho(g, v1 - 1);
                imprime_menor_caminho(v2 - 1, v2 - 1, pai);
                free(pai);
            }
        }

        else if (operacao == 6){
            for (int i = 0; i < g->n_vertices; i++){
                int *visitado = busca_em_profundidade(g, i);
                imprime_vertices_conectados(i, g->n_vertices, visitado);
                free(visitado);
            }
        }

        scanf(" %d", &operacao);
    }

    libera_grafo(g, MAX);

    return 0;
}
