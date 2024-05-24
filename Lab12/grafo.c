#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "grafo.h"


/*Cria o grafo que será usado no programa

Parâmetro:
n_max -- número máximo de vértices que o grafo pode ter

Retorno:
g -- ponteiro para a struct grafo que representa o grafo usado no programa
*/
p_grafo cria_grafo(int n_max){
    p_grafo g = malloc(sizeof (struct grafo));
    g->n_vertices = 0;
    g->m_adj = malloc(n_max * sizeof (int *));

    for (int i = 0; i < n_max; i++)
        g->m_adj[i] = calloc(n_max, sizeof (int));

    return g;
}


/*Verifica se existe uma aresta ligando os vértices v1 e v2

Parâmetros:
g -- ponteiro para a struct grafo que representa o grafo usado no programa
v1 -- número inteiro que representa um vértice do grafo
v2 -- número inteiro que representa um vértice do grafo

Retorno:
1, caso exista uma aresta ligando os vértices v1 e v2; ou 0, caso contrário
*/
int tem_aresta(p_grafo g, int v1, int v2){
    return g->m_adj[v1][v2];
}


/*Coloca uma aresta ligando os vértices v1 e v2

Parâmetros:
g -- ponteiro para a struct grafo que representa o grafo usado no programa
v1 -- número inteiro que representa um vértice do grafo
v2 -- número inteiro que representa um vértice do grafo

Retorno:
void
*/
void insere_aresta(p_grafo g, int v1, int v2){
    g->m_adj[v1][v2] = 1;
    g->m_adj[v2][v1] = 1;
}


/*Retira a aresta existente entre v1 e v2

Parâmetros:
g -- ponteiro para a struct grafo que representa o grafo usado no programa
v1 -- número inteiro que representa um vértice do grafo
v2 -- número inteiro que representa um vértice do grafo

Retorno:
void
*/
void retira_aresta(p_grafo g, int v1, int v2){
    g->m_adj[v1][v2] = 0;
    g->m_adj[v2][v1] = 0;
}


/*Busca um possível caminho entre os vértices v1 e v2, a fim de verificar sua existência

Parâmetros:
g -- ponteiro para a struct grafo que representa o grafo usado no programa
visitado -- vetor que guarda a informação se um vértice foi visitado (1) ou não (0)
v1 -- número inteiro que representa um vértice do grafo
v2 -- número inteiro que representa um vértice do grafo 
*/
int busca_rec(p_grafo g, int *visitado, int v1, int v2){
    int u;      //Índice que será usado para percorrer a matriz de adjacências

    if (v1 == v2)
        return 1;

    visitado[v1] = 1;
    for (u = 0; u < g->n_vertices; u++)
        if (tem_aresta(g, v1, u) && !visitado[u])
            if (busca_rec(g, visitado, u, v2))
                return 1;

    return 0;
}


/*Verifica se existe algum caminho que conecta os vértices v1 e v2

Parâmetros:
g -- ponteiro para a struct grafo que representa o grafo usado no programa
v1 -- número inteiro que representa um vértice do grafo
v2 -- número inteiro que representa um vértice do grafo

Retorno:
1, caso exista caminho entre os vértices v1 e v2; ou 0, caso contrário
*/
int tem_caminho(p_grafo g, int v1, int v2){
    int tem;    //Variável que indica se tem ou não caminho entre os vértices v1 e v2
    //Vetor que guarda a informação se um vértice já foi visitado ou não
    int *visitado = calloc(g->n_vertices, sizeof(int));

    tem = busca_rec(g, visitado, v1, v2);
    free(visitado);

    return tem;
}


/*Realiza uma busca em profundidade no grafo para encontrar os vértices conectados a um outro

Parâmetros:
g -- ponteiro para a struct grafo que representa o grafo usado no programa
pai -- vetor que representa o caminho de um vértice "pai" até outro
v1 -- número inteiro que representa um vértice do grafo

Retorno:
visitado -- vetor que guarda os vértices que puderam ser visitados, seguindo um caminho a partir de v1
*/
int * busca_em_profundidade(p_grafo g, int v1){
    int w, u;       //Índices que serão usados para percorrer a matriz de adjacências

    int *visitado = calloc(g->n_vertices, sizeof(int));
    p_pilha pilha = cria_pilha();

    empilha(pilha, v1);

    while (!pilha_vazia(pilha)){
        u = desempilha(pilha);

        if (visitado[u])
            continue;

        visitado[u] = 1;

        for (w = 0; w < g->n_vertices; w++)
            if (tem_aresta(g, u, w) && !visitado[w])
                empilha(pilha, w);
    }
    libera_pilha(pilha);
    
    return visitado;
}


/*Realiza uma busca em largura no grafo para encontrar um dos menores caminhos possíveis entre dois vértices

Parâmetros:
g -- ponteiro para a struct grafo que representa o grafo usado no programa
pai -- vetor que representa o caminho de um vértice "pai" até outro
v1 -- número inteiro que representa um vértice do grafo

Retorno:
void
*/
void busca_em_largura(p_grafo g, int *pai, int v1){
    int w, u;

    int *visitado = calloc(g->n_vertices, sizeof(int));
    p_fila fila = cria_fila();

    enfileira(fila, v1);
    pai[v1] = v1;
    visitado[v1] = 1;

    while (!fila_vazia(fila)){
        u = desenfileira(fila);

        for (w = 0; w < g->n_vertices; w++)
            if (tem_aresta(g, u, w) && !visitado[w]){
                visitado[w] = 1;
                pai[w] = u;
                enfileira(fila, w);
            }
    }
    libera_fila(fila);
    free(visitado);
}


/*Utilizando-se da busca em largura, encontra o menor caminho entre dois vértices

Parâmetros:
g -- ponteiro para a struct grafo que representa o grafo usado no programa
v1 -- número inteiro que representa um vértice do grafo

Retorno:
pai -- vetor que representa o caminho de um vértice "pai" até outro
*/
int * encontra_menor_caminho(p_grafo g, int v1){
    int *pai = malloc(g->n_vertices * sizeof(int));

    for (int i = 0; i < g->n_vertices; i++)
        pai[i] = -1;

    busca_em_largura(g, pai, v1);

    return pai;
}


/*Imprime o menor caminho encontrado entre um vértice e outro

Parâmetros:
v -- número inteiro que representa um vértice do grafo
vf -- número inteiro que representa o vértice que se deseja chegar ('f' de final)
pai -- vetor que representa o caminho de um vértice "pai" até outro

Retorno:
void
*/
void imprime_menor_caminho(int v, int vf, int *pai){
    if (pai[v] != v)
        imprime_menor_caminho(pai[v], vf, pai);

    if (v != vf)
        printf("%d -> ", v + 1);

    else
        printf("%d\n", v + 1);
}


/*Imprime todos os vértices conectados direta ou indiretamente a um outro

Parâmetros:
v -- número inteiro que representa um vértice do grafo
n_vertices -- número de vértices que se tem no grafo
visitado -- vetor que guarda os vértices que puderam ser visitados, seguindo um caminho a partir de v

Retorno:
void
*/
void imprime_vertices_conectados(int v, int n_vertices, int *visitado){
    printf("Ponto %d (Pontos diretamente ou indiretamente conectados): ", v + 1);

    for (int i = 0; i < n_vertices; i++)
        if (visitado[i])
            printf("%d ", i + 1);
    
    printf("\n");
}


/*Libera a memória alocada para o gráfico durante o programa

Parâmetro:
g -- ponteiro para a struct grafo que representa o grafo usado no programa
n_max -- número inteiro que representa o número máximo de vértices do grafo

Retorno:
void
*/
void libera_grafo(p_grafo g, int n_max){
    for (int i = 0; i < n_max; i++)
        free(g->m_adj[i]);

    free(g->m_adj);
    free(g);
}
