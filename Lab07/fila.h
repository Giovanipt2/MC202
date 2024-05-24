#include "peca.h"


typedef struct fila *p_fila;        //ponteiro para a struct fila

struct fila{
    p_peca *vetor_pecas;        
    //respectivamente, posições de início e fim da fila (local se inserção de uma nova peça); e os espaços, usado e alocado para a fila
    int ini, fim, usado, tam_fila;
};


/*Inicializa a esteira com base em seu tamanho na simulação*/
p_fila cria_fila(int tam_fila);

/*Verifica se há espaço suficiente na esteira para a entrada de uma nova peça*/
int cabe_na_esteira(p_fila esteira);

/*Verifica se a fila está vazia*/
int fila_vazia(p_fila fila);

/*Preenche a fila de espera com as entradas da simulação, de forma que seja possível controlar o tempo de entradas das peças na esteira*/
void le_entradas_simulacao(p_fila fila_espera);

/*Adiciona uma nova peça à esteira*/
void adiciona_esteira(p_fila esteira, p_peca peca);

/*Retira uma peça da fila de espera, a qual foi colocada na esteira*/
p_peca remove_fila_espera(p_fila fila_espera);

/*Retira uma peça da esteira, a qual foi pega pelo classficador*/
p_peca remove_esteira(p_fila esteira);

/*Libera a memória alocada para a esteira durante a simulação*/
void libera_fila(p_fila esteira);
