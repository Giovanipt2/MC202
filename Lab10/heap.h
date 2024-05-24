#ifndef heap_h
#define heap_h

#include "prato.h"

#define PAI(i)  ((i - 1) / 2)       //nó que representa o pai de outros dois nós
#define FILHO_ESQ(i) (2 * i + 1)    //filho esquerdo de um nó pai
#define FILHO_DIR(i) (2 * i + 2)    //filho direito de um nó pai


typedef struct sobrevivente *p_sobrevivente;    //ponteiro para a struct sobrevivente
typedef struct fila_prio *p_fila_prio;          //ponteiro para a struct fila_prio

struct sobrevivente{
    char nome[16];          //nome do sobrevivente
    char sobrenome[16];     //sobrenome do sobrevivente
    int pos_heap;           //posição que o sobrevivente ocupa no heap
    int dias_sobrevividos;  //número de dias sobrevividos
    int chave_prio;         //chave de prioridade (valor que representa a prioridade de um sobrevivente)
    p_prato prato_pedido;   //parto escolhido pelo sobrevivente
};


struct fila_prio{
    p_sobrevivente *vetor_sobreviventes;    //vetor de sobreviventes
    int n_elementos, tam_fila;              //respectivamente, as quantidades do vetor que estão sendo usada e alocada
};


/*Cria um sobrevivente*/
p_sobrevivente cria_sobrevivente(char nome[], char sobrenome[], int dias_sobrevividos);

/*Cria a fila de prioridade*/
p_fila_prio cria_fila_prio(int tam_fila);

/*Adiciona um novo prato a um sobrevivente*/
void adiciona_prato(p_prato prato, p_fila_prio fila_chegada, int id);

/*Remove um prato já preparado do sobrevivente que o havia pedido*/
void remove_prato(p_prato prato, p_fila_prio fila_chegada, int id);

/*Troca dois sobrevivente de lugar no heap*/
void troca(p_fila_prio f_prio ,int pos_sobrevivente_1, int pos_sobrevivente_2);

/*Sobe um sobrevivente no heap, ajustando-o de acordo com sua chave de prioridade*/
void sobe_no_heap(p_fila_prio f_prio, int posicao);

/*Desce um sobrevivente no heap, ajustando-o de acordo com sua chave de prioridade*/
void desce_no_heap(p_fila_prio f_prio, int posicao);

/*Insere um sobrevivente no heap*/
void insere_no_heap(p_fila_prio f_prio, p_sobrevivente sobrevivente);

/*Insere um sobrevivente na fila de chegada*/
void insere_fila_chegada(p_fila_prio fila_chegada, p_sobrevivente sobrevivente);

/*Retira o prato do sobrevivente no heap cuja prioridade é máxima*/
p_sobrevivente extrai_maximo(p_fila_prio f_prio);

/*Altera a prioridade de um pedido de um sobrevivente*/
void altera_prioridade(int valor, p_fila_prio fila_chegada, p_fila_prio f_prio, int id);

/*Após o pedido ter sido entregue, reinicia a prioridade do sobrevivente para ser igual a inicial*/
void reseta_prioridade(p_sobrevivente sobrevivente);

/*Libera a memória usada para o heap durante o programa*/
void libera_heap(p_fila_prio f_prio);

#endif
