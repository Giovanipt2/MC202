#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"


/*Cria um sobrevivente

Parâmetros:
nome -- string que representa o nome do sobrevivente
dias_sobrevividos -- número inteiro que representa há quantos dias o sobrevivente está vivo

Retorno:
sobrevivente -- ponteiro para a struct sobrevivente
*/
p_sobrevivente cria_sobrevivente(char nome[], char sobrenome[], int dias_sobrevividos){
    p_sobrevivente sobrevivente = malloc(sizeof (struct sobrevivente));
    strcpy(sobrevivente->nome, nome);
    strcpy(sobrevivente->sobrenome, sobrenome);
    //inicializa com uma posição que não está no heap, indicando que o sobrevivente não foi inserido
    sobrevivente->pos_heap = -1;          
    sobrevivente->dias_sobrevividos = dias_sobrevividos;
    sobrevivente->chave_prio = dias_sobrevividos;
    sobrevivente->prato_pedido = NULL;

    return sobrevivente;
}


/*Cria a fila de prioridade

Parâmetro:
tam_fila -- número inteiro que representa o tamanho da fila que será usada

Retorno:
f_prio -- ponteiro para a struct fila_prio que representa a fila de prioridade
*/
p_fila_prio cria_fila_prio(int tam_fila){
    p_fila_prio f_prio = malloc(sizeof(struct fila_prio));
    f_prio->vetor_sobreviventes = malloc(tam_fila * sizeof(p_sobrevivente));
    f_prio->n_elementos = 0;
    f_prio->tam_fila = tam_fila;

    return f_prio;
}


/*Adiciona um novo prato a um sobrevivente

Parâmetros:
fila_chegada -- ponteiro para a struct fila_prio que representa a fila de chegada dos sobreviventes (ID's)
prato -- ponteiro para a struct prato que representa o prato pedido por um sobrevivente
id -- ID de um sobrevivente, ou seja, posição dele na fila_chegada

Retorno:
void
*/
void adiciona_prato(p_prato prato, p_fila_prio fila_chegada, int id){
    fila_chegada->vetor_sobreviventes[id]->prato_pedido = prato;
}


/*Remove um prato já preparado do sobrevivente que o havia pedido

Parâmetros:
fila_chegada -- ponteiro para a struct fila_prio que representa a fila de chegada dos sobreviventes (ID's)
prato -- ponteiro para a struct prato que representa o prato pedido por um sobrevivente
id -- ID de um sobrevivente, ou seja, posição dele na fila_chegada

Retorno:
void
*/
void remove_prato(p_prato prato, p_fila_prio fila_chegada, int id){
    p_prato prato_feito = fila_chegada->vetor_sobreviventes[id]->prato_pedido;

    fila_chegada->vetor_sobreviventes[id]->prato_pedido = NULL;
    free(prato_feito);
}


/*Troca dois sobrevivente de lugar no heap

Parâmetros:
f_prio -- ponteiro para a struct fila_prio que representa a fila de prioridade
pos_sobrevivente_1 -- posição no heap do primeiro sobrevivente que será trocado de lugar
pos_sobrevivente_2 -- posição no heap do segundo sobrevivente que será trocado de lugar

Retorno:
void
*/
void troca(p_fila_prio f_prio, int pos_sobrevivente_1, int pos_sobrevivente_2){
    //sobrevivente temporário que será usado para realizar a troca
    p_sobrevivente sobrevivente_temp;
    //posição do sobrevivente temporário que será usado para realizar a troca
    int pos_heap_sobrevivente_temp;

    pos_heap_sobrevivente_temp = pos_sobrevivente_1;
    sobrevivente_temp = f_prio->vetor_sobreviventes[pos_sobrevivente_1];

    f_prio->vetor_sobreviventes[pos_sobrevivente_1]->pos_heap = pos_sobrevivente_2;
    f_prio->vetor_sobreviventes[pos_sobrevivente_1] = f_prio->vetor_sobreviventes[pos_sobrevivente_2];
    f_prio->vetor_sobreviventes[pos_sobrevivente_2]->pos_heap = pos_heap_sobrevivente_temp;
    f_prio->vetor_sobreviventes[pos_sobrevivente_2] = sobrevivente_temp;
}


/*Sobe um sobrevivente no heap, ajustando-o de acordo com sua chave de prioridade

Parâmetros:
f_prio -- ponteiro para a struct fila_prio que representa a fila de prioridade
posicao -- última posição do heap, a partir da qual se iniciará o ajuste 

Retorno:
void
*/
void sobe_no_heap(p_fila_prio f_prio, int posicao){
    if (posicao > 0 && f_prio->vetor_sobreviventes[PAI(posicao)]->chave_prio < f_prio->vetor_sobreviventes[posicao]->chave_prio){
        troca(f_prio, posicao, PAI(posicao));
        sobe_no_heap(f_prio, PAI(posicao));
    }
}


/*Desce um sobrevivente no heap, ajustando-o de acordo com sua chave de prioridade

Parâmetros:
f_prio -- ponteiro para a struct fila_prio que representa a fila de prioridade
posicao -- primeia posição do heap, a partir da qual se iniciará o ajuste

Retorno:
void
*/
void desce_no_heap(p_fila_prio f_prio, int posicao){
    int pos_maior_filho;        //posição do filho com maior prioridade de um nó pai

    if (FILHO_ESQ(posicao) < f_prio->n_elementos){
        pos_maior_filho = FILHO_ESQ(posicao);
        
        if (FILHO_DIR(posicao) < f_prio->n_elementos && 
            f_prio->vetor_sobreviventes[FILHO_ESQ(posicao)]->chave_prio < f_prio->vetor_sobreviventes[FILHO_DIR(posicao)]->chave_prio)
            pos_maior_filho = FILHO_DIR(posicao);

        if (f_prio->vetor_sobreviventes[posicao]->chave_prio < f_prio->vetor_sobreviventes[pos_maior_filho]->chave_prio){
            troca(f_prio, posicao, pos_maior_filho);
            desce_no_heap(f_prio, pos_maior_filho);
        }
    }
}


/*Insere um sobrevivente no heap

Parâmetros:
f_prio -- ponteiro para a struct fila_prio que representa a fila de prioridade
sobrevivente -- ponteiro para a struct sobrevivente

Retorno:
void
*/
void insere_no_heap(p_fila_prio f_prio, p_sobrevivente sobrevivente){
    f_prio->vetor_sobreviventes[f_prio->n_elementos] = sobrevivente;
    sobrevivente->pos_heap = f_prio->n_elementos;
    f_prio->n_elementos++;
    sobe_no_heap(f_prio, f_prio->n_elementos - 1);
}


/*Insere um sobrevivente na fila de chegada

Parâmetros:
fila_chegada -- ponteiro para a struct fila_prio que representa a fila de chegada dos sobreviventes (ID's)
sobrevivente -- ponteiro para a struct sobrevivente

Retorno:
void
*/
void insere_fila_chegada(p_fila_prio fila_chegada, p_sobrevivente sobrevivente){
    fila_chegada->vetor_sobreviventes[fila_chegada->n_elementos] = sobrevivente;
    fila_chegada->n_elementos++;
}


/*Retira o prato do sobrevivente no heap cuja prioridade é máxima

Parâmetro:
f_prio -- ponteiro para a struct fila_prio que representa a fila de prioridade

Retorno:
sobrevivente_max -- ponteiro para a struct sobrevivente que representa o sobrevivente com a maior prioridade
*/
p_sobrevivente extrai_maximo(p_fila_prio f_prio){
    p_sobrevivente sobrevivente_max;

    sobrevivente_max = f_prio->vetor_sobreviventes[0];
    troca(f_prio, 0, f_prio->n_elementos - 1);
    f_prio->n_elementos--;
    desce_no_heap(f_prio, 0);
    sobrevivente_max->pos_heap = -1;

    return sobrevivente_max;
}


/*Altera a prioridade de um pedido de um sobrevivente

Parâmetros:
valor -- número que será acrescido ao valor original de prioridade
fila_chegada -- ponteiro para a struct fila_prio que guarda os ID's dos sobreviventes (ordem de chegada)
f_prio -- ponteiro para a struct fila_prio que representa a fila de prioridade
id -- ID de um sobrevivente, ou seja, posição dele na fila_chegada

Retorno:
void
*/
void altera_prioridade(int valor, p_fila_prio fila_chegada, p_fila_prio f_prio, int id){
    if (valor > 0){
        fila_chegada->vetor_sobreviventes[id]->chave_prio += valor;
        sobe_no_heap(f_prio, fila_chegada->vetor_sobreviventes[id]->pos_heap);
    }

    else{
        fila_chegada->vetor_sobreviventes[id]->chave_prio += valor;
        desce_no_heap(f_prio, fila_chegada->vetor_sobreviventes[id]->pos_heap);
    }
}


/*Após o pedido ter sido entregue, reinicia a prioridade do sobrevivente para ser igual a inicial

Parâmetros:
sobrevivente -- ponteiro para a struct sobrevivente

Retorno:
void
*/
void reseta_prioridade(p_sobrevivente sobrevivente){
    sobrevivente->chave_prio = sobrevivente->dias_sobrevividos;
}


/*Libera a memória usada para o heap durante o programa

Parâmetro:
f_prio -- ponteiro para a struct fila_prio que representa a fila de prioridade

Retorno:
void
*/
void libera_heap(p_fila_prio f_prio){
    for (int i = 0; i < f_prio->n_elementos; i++)
        free(f_prio->vetor_sobreviventes[i]);
    
    free(f_prio->vetor_sobreviventes);
    free(f_prio);
}
