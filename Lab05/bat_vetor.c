#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bat_vetor.h"


/*Cria a batmemória com a quantidade correta de espaços iniciais

Retorno:
bat_memoria -- ponteiro para a struct bat_vetor
*/
p_bat_vetor cria_bat_memoria(){
    p_bat_vetor bat_memoria;
    bat_memoria = malloc(sizeof(struct bat_vetor));
    bat_memoria->bat_dados = calloc(8, sizeof(int));
    bat_memoria->bat_n_dados = 0;
    bat_memoria->bat_alocado = 8;
    bat_memoria->ultima_bat_posicao_alocada = 0;
    return bat_memoria;
}


/*Encontra, se possível, a posição em que o vetor deve ser inserido na bat_memória

Caso não haja espaço, retorna -1 indicando que não há um índice de inserção válido

Parâmetros:
bat_memoria -- ponteiro para a struct bat_vetor
espaco_necessario -- quantidade de espaços na bat_memória necessaŕios para bat-alocar o vetor

Retorno:
posicao_alloc -- número inteiro que representa a posição da bat_memória na qual devem ser inseridas as informações do vetor
-1, caso não haja espaço disponível na memória, ou a posição da memória na qual o vetor deve ser alocado
*/
int encontra_posicao_bat_alloc(p_bat_vetor bat_memoria, int espaco_necessario){
    //variável que armazena em qual posição da bat_memória as informações do vetor serão alocadas
    int i, posicao_alloc;
    //variável que guarda quantos espaços de bat_memória consecutivos estão livres
    int bat_contador_espacos = 0;

    for (i = 0; i < bat_memoria->bat_alocado; i++){
        if (bat_memoria->bat_dados[i] == 0){
            posicao_alloc = i;
            bat_contador_espacos++;
            
            if (bat_contador_espacos == espaco_necessario){
                posicao_alloc -= (espaco_necessario - 1);
                return posicao_alloc;
            }
        }
        else
            bat_contador_espacos = 0;
    }
    posicao_alloc = -1;

    return posicao_alloc;
}


/*Procura pela última bat_posição que está sendo utilizada na bat_memória

Parâmetro:
bat_memoria -- ponteiro para a struct bat_vetor

Retorno:
ultima_bat_posicao -- última posição da bat_memória que está sendo utilizada
*/
int encontra_ultima_bat_posicao(p_bat_vetor bat_memoria, int bat_inicio){
    int i, ultima_bat_posicao;
    
    for (i = bat_inicio; i >=0; i--)
        if (bat_memoria->bat_dados[i] != 0){
            ultima_bat_posicao = i + 1;
            break;
        }
    return ultima_bat_posicao;
}


/*Caso não tenha espaço suficiente para bat_alocar, dobra o tamanaho da bat_memória

Parâmetro:
bat_memoria -- ponteiro para a struct bat_vetor

Retorno:
void
*/
void expande_bat_memoria(p_bat_vetor bat_memoria){
    //bat_temp é um vetor que armazenará o que havia na memória antes de ela ser expandida
    int i, *bat_temp;

    bat_temp = bat_memoria->bat_dados;
    bat_memoria->bat_alocado *= 2;
    bat_memoria->bat_dados = calloc(bat_memoria->bat_alocado, sizeof(int));

    for (i = 0; i < (bat_memoria->bat_alocado) / 2; i++)
        bat_memoria->bat_dados[i] = bat_temp[i];
    
    bat_libera_memoria(bat_temp);
}


/*Quando há 3 vezes mais bat_memória usada do que alocada, reduz a bat_memória pela metade

Parâmetro:
bat_memoria -- ponteiro para a struct bat_vetor

Retorno:
void
*/
void reduz_bat_memoria(p_bat_vetor bat_memoria){
    int i, *bat_temp;

    bat_temp = bat_memoria->bat_dados;
    bat_memoria->bat_alocado /= 2;
    bat_memoria->bat_dados = calloc(bat_memoria->bat_alocado, sizeof(int));

    for (i = 0; i < (bat_memoria->bat_alocado) / 2; i++)
        bat_memoria->bat_dados[i] = bat_temp[i];

    bat_libera_memoria(bat_temp);
}


/*Compara duas posições alocadas da bat_memória para saber qual delas tem o maior índice

Ela permite saber qual foi a última posição alocada, evitando que toda a bat_memória tenha que ser percorrida para saber se ela deve ou não ser reduzida

Parâmetros:
bat_memoria -- ponteiro para a struct bat_vetor
ultima_bat_posicao_aux -- bat_posicao auxiliar que guarda a última posição alocada na bat_memória na chamada mais recente da função bat-alloc

Retorno:
void
*/
void compara_bat_posicoes(p_bat_vetor bat_memoeria, int ultima_bat_posicao_aux){
    if (ultima_bat_posicao_aux > bat_memoeria->ultima_bat_posicao_alocada)
        bat_memoeria->ultima_bat_posicao_alocada = ultima_bat_posicao_aux;
}


/*Aloca, na primeira região contígua de memória possível, o tamanho de um vetor e, em seguida, seus elementos

Ademais, imprime qual a posição da bat_memória em que o vetor foi alocado

Parâmetros:
bat_memoria -- ponteiro para a struct bat_vetor
tam_vetor -- tamanho do vetor que será alocado
vetor -- vetor com os elementos que serão guardados na bat_memória

Retorno:
void
*/
void bat_alloc(p_bat_vetor bat_memoria, int tam_vetor, int *vetor){
    //variável que armazena em qual posição da bat_memória as informações do vetor serão alocadas
    int i, j, posicao_alloc;
    posicao_alloc = encontra_posicao_bat_alloc(bat_memoria, tam_vetor + 1);

    if (posicao_alloc == -1){
        expande_bat_memoria(bat_memoria);
        posicao_alloc = encontra_ultima_bat_posicao(bat_memoria, (bat_memoria->bat_alocado / 2) + 1);
    }

    bat_memoria->bat_dados[posicao_alloc] = tam_vetor;
    bat_memoria->bat_n_dados++;
    //variável necessária, já que as posições de inserção na bat_memória não são as mesmas acessadas no vetor
    j = 0;          

    for (i = posicao_alloc + 1; i <= posicao_alloc + tam_vetor; i++){
        bat_memoria->bat_dados[i] = vetor[j];
        bat_memoria->bat_n_dados++;
        j++;
    }

    //variável que armazenará a última posição alocada na bat_memória nesta chamada da função, para que possa se comparar com a que se tinha anteriormente
    int ultima_bat_posicao_aux;
    ultima_bat_posicao_aux = posicao_alloc + tam_vetor;
    compara_bat_posicoes(bat_memoria, ultima_bat_posicao_aux);

    printf("%d\n", posicao_alloc);
}


/*Libera da bat_memória uma região correspondente a um vetor, com base em seu índice de início

Parâmetros:
bat_memoria -- ponteiro para a struct bat_vetor
bat_endereco -- local na bat_memória em que se inicia o vetor que se deseja liberar

Retorno:
void
*/
void bat_free(p_bat_vetor bat_memoria, int bat_endereco){
    //variável utilizada para verificar se a última bat_posição que foi liberada era a última sendo utilizada
    int i, ultima_bat_posicao_liberada;
    ultima_bat_posicao_liberada = bat_endereco + bat_memoria->bat_dados[bat_endereco];

    for (i = bat_endereco; i <=  ultima_bat_posicao_liberada; i++){
        bat_memoria->bat_dados[i] = 0;
        bat_memoria->bat_n_dados--;
    }

    if (ultima_bat_posicao_liberada == bat_memoria->ultima_bat_posicao_alocada)
        bat_memoria->ultima_bat_posicao_alocada = encontra_ultima_bat_posicao(bat_memoria, bat_memoria->ultima_bat_posicao_alocada) - 1;

    if (bat_memoria->bat_alocado > 8)
        if (bat_memoria->ultima_bat_posicao_alocada < (bat_memoria->bat_alocado / 4))
            reduz_bat_memoria(bat_memoria);
}


/*Imprime uma lista de números inteiros, indicada pelo seu índice de início

Parâmetros:
bat_memoria -- ponteiro para a struct bat_vetor
bat_endereco -- local na bat_memória em que se inicia o vetor que se deseja imprimir
*/
void bat_print(p_bat_vetor bat_memoria, int bat_endereco){
    int i;

    for (i = bat_endereco + 1; i <= bat_endereco + bat_memoria->bat_dados[bat_endereco]; i++)
        printf("%d ", bat_memoria->bat_dados[i]);

    printf("\n");
}


/*Imprime o quanto do espaço de memória da bat_memória está sendo usado no momento

Parâmetros:
bat_memoria -- ponteiro para a struct bat_vetor

Retorno;
void
*/
void bat_uso(p_bat_vetor bat_memoria){
    printf("%d de %d\n", bat_memoria->bat_n_dados, bat_memoria->bat_alocado);
}


/*Decide, a partir do comando dado, qual função deverá ser chamada

Parâmetros:
bat_comando -- string que representa o comando dado ao programa
bat_memoria -- ponteiro para a struct bat_vetor

Retorno:
void
*/
void decide_bat_funcao(p_bat_vetor bat_memoria, char bat_comando[]){
    if (strcmp(bat_comando, "bat-alloc") == 0){
        //tam_vetor é o tamanho do vetor que será alocado na bat_memória
        int i, tam_vetor;
        scanf("%d", &tam_vetor);

        int *vetor = malloc(tam_vetor * sizeof(int));
        
        for (i = 0; i < tam_vetor; i++)
            scanf("%d", &vetor[i]);

        bat_alloc(bat_memoria, tam_vetor, vetor);

        free(vetor);
    }

    else if (strcmp(bat_comando, "bat-free") == 0){
        //endereço que marca o início do vetor que será liberado
        int bat_endereco;
        scanf("%d", &bat_endereco);

        bat_free(bat_memoria, bat_endereco);
    }

    else if (strcmp(bat_comando, "bat-print") == 0){
        //endereço que marca o início do vetor que será impresso
        int bat_endereco;
        scanf("%d", &bat_endereco);

        bat_print(bat_memoria, bat_endereco);
    }

    else
        bat_uso(bat_memoria);
}


/*Libera a memória que foi alocada dinamicamente durante o programa

Não recebe, necessariamente, um ponteiro do mesmo tipo para ser liberado; por isso o void

Parâmetro:
pointer -- algum ponteiro que foi alocado dinamicamente, do tipo que foi necessário na ocasião

Retorno:
void
*/
void bat_libera_memoria(void *pointer){
    free(pointer);
}
