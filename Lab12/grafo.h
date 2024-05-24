#ifndef grafo_h
#define grafo_h

#include "pilha.h"
#include "fila.h"

typedef struct grafo *p_grafo;

struct grafo{
    int **m_adj;        //Grafo representado como uma matriz de adjacências
    int n_vertices;     //Número inteiro que representa o número de vértices do grafo
};


/*Cria o grafo que será usado no programa*/
p_grafo cria_grafo(int n_max);

/*Verifica se existe uma aresta ligando os vértices v1 e v2*/
int tem_aresta(p_grafo g, int v1, int v2);

/*Coloca uma aresta ligando os vértices v1 e v2*/
void insere_aresta(p_grafo g, int v1, int v2);

/*Retira a aresta existente entre v1 e v2*/
void retira_aresta(p_grafo, int v1, int v2);

/*Busca um possível caminho entre os vértices v1 e v2, a fim de verificar sua existência*/
int busca_rec(p_grafo g, int *visitado, int v1, int v2);

/*Verifica se existe algum caminho que conecta os vértices v1 e v2*/
int tem_caminho(p_grafo g, int v1, int v2);

/*Realiza uma busca em profundidade no grafo para encontrar os vértices conectados a um outro*/
int * busca_em_profundidade(p_grafo g, int v1);

/*Realiza uma busca em largura no grafo para encontrar um dos menores caminhos possíveis entre dois vértices*/
void busca_em_largura(p_grafo g, int *pai, int v1);

/*Utilizando-se da busca em largura, encontra o menor caminho entre dois vértices*/
int * encontra_menor_caminho(p_grafo g, int v1);

/*Imprime o menor caminho encontrado entre um vértice e outro*/
void imprime_menor_caminho(int v, int vf, int *pai);

/*Imprime todos os vértices conectados direta ou indiretamente a um outro*/
void imprime_vertices_conectados(int v, int n_vertices, int *visitado);

/*Libera a memória alocada para o gráfico durante o programa*/
void libera_grafo(p_grafo g, int n_max);

#endif
