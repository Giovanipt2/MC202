#ifndef pilha_h
#define pilha_h

typedef struct pilha *p_pilha;

struct pilha{
    int *v_vertices;        //Vetor de vértices da pilha, onde serão guardados um vértice do grafo (e seus adjacentes)
    //Respectivamente, a posição de topo da pilha (local de inserção); e os espaços, usado e alocado para a pilha
    int topo, n_vertices, alocado;  
};


/*Cria a pilha que será usada para fazer busca em profundidade no grafo*/
p_pilha cria_pilha();

/*Verifica se a pilha está vazia*/
int pilha_vazia(p_pilha pilha);

/*Coloca um novo vértice no topo da pilha*/
void empilha(p_pilha pilha, int elemento);

/*Remove o vérticeo que está no ponto da pilha*/
int desempilha(p_pilha pilha);

/*Libera a memória alocada para a pilha durante o programa*/
void libera_pilha(p_pilha pilha);

#endif
