#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prato.h"


/*Cria o prato que foi pedido pelo sobrevivente

Parâmetros:
nome_prato -- string que representa o nome do prato pedido pelo sobrevivente

Retorno:
*/
p_prato cria_prato(char nome_prato[]){
    p_prato prato = malloc(sizeof (struct prato));
    strcpy(prato->nome_prato, nome_prato);

    return prato;
}


/*Libera a memória alocada para o prato durante o programa

Parâmetros:
prato -- ponteiro para a struct prato

Retorno:
void
*/
void libera_prato(p_prato prato){
    free(prato);
}
