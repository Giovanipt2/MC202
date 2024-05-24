#include <stdio.h>
#include <stdlib.h>

//p_bat_vetor é um ponteiro para a struct bat_vetor
typedef struct bat_vetor *p_bat_vetor;

struct bat_vetor{
    int *bat_dados;                     //vetor que armazenará os dados em questão
    int bat_n_dados;                    //número de posições ocupadas com informações válidas
    int bat_alocado;                    //espaço no bat_vetor que foi alocado
    int ultima_bat_posicao_alocada;     //guarda a informação de qual é o último espaço da bat_memória que está sendo utilizado
};


/*Cria a batmemoria com a quantidade correta de espaços iniciais*/
p_bat_vetor cria_bat_memoria();

/*Encontra, se possível, a posição em que o vetor deve ser inserido na bat_memória*/
int encontra_posicao_bat_alloc(p_bat_vetor bat_memoria, int espaco_necessario);

/*Procura pela última bat_posição que está sendo utilizada na bat_memória*/
int encontra_ultima_bat_posicao(p_bat_vetor bat_memoria, int bat_inicio);

/*Caso não tenha espaço suficiente para bat_alocar, dobra o tamanaho da bat_memória*/
void expande_bat_memoria(p_bat_vetor bat_memoria);

/*Quando há 3 vezes mais bat_memória usada do que alocada, reduz a bat_memória pela metade*/
void reduz_bat_memoria(p_bat_vetor bat_memoria);

/*Compara duas posições alocadas da bat_memória para saber qual delas tem o maior índice
Ela permite saber qual foi a última posição alocada, evitando que toda a bat_memória tenha que ser percorrida para saber se ela deve ou não ser reduzida*/
void compara_bat_posicoes(p_bat_vetor bat_memoria, int ultima_bat_posicao_aux);

/*Aloca, na primeira região contígua de memória possível, o tamanho de um vetor e, em seguida, seus elementos
Ademais, imprime qual a posição da bat_memória em que o vetor foi alocado*/
void bat_alloc(p_bat_vetor bat_memoria, int tam_vetor, int *vetor);

/*Libera da bat_memória uma região correspondente a um vetor, com base em seu índice de início*/
void bat_free(p_bat_vetor bat_memoria, int bat_endereco);

/*Imprime uma lista de números inteiros, indicada pelo seu índice de início*/
void bat_print(p_bat_vetor bat_memoria, int bat_endereco);

/*Imprime o quanto do espaço de memória da bat_memória está sendo usado no momento*/
void bat_uso(p_bat_vetor bat_memoria);

/*Decide, a partir do comando dado, qual função deverá ser chamada*/
void decide_bat_funcao(p_bat_vetor bat_memoria, char bat_comando[]);

/*Libera a memória que foi alocada dinamicamente durante o programa
Não recebe, necessariamente, um ponteiro do mesmo tipo para ser liberado*/
void bat_libera_memoria(void *pointer);
