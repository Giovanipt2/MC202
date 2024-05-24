#ifndef fila_h
#define fila_h


typedef struct fila *p_fila;        //Ponteiro para a struct fila

struct fila{
    int *v_vertices;        //Vetor de vértices usado para guardar os elementos da fila
    //Respectivamente, posições de início e fim da fila (local de inserção de um vértice); e os espaços, usado e alocado para a fila
    int ini, fim, n_vertices, alocado;
};


/*Cria a fila que será utilizada para fazer busca em largura no grafo*/
p_fila cria_fila();

/*Verifica se a fila está vazia*/
int fila_vazia(p_fila fila);

/*Adiciona um novo vértice na fila*/
void enfileira(p_fila fila, int vertice);

/*Retira um vértice da fila*/
int desenfileira(p_fila fila);

/*Libera a memória alocada para a fila*/
void libera_fila(p_fila esteira);

#endif
