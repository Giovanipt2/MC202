#ifndef hash_h
#define hash_h

#include "familia.h"

#define MAX 3011    //Tamanho escolhido de forma a deixar o vetor, no máximo, meio cheio; tornando a busca mais rápida

typedef struct hash *p_hash;

struct hash{
    Familia vetor_h[MAX];
};


/*Calcula o hash de uma determinada família*/
int calcula_hash(char *chave);

/*Cria a tabela de hashing que será usada no programa*/
p_hash cria_tab_hash();

/*Inicializa a tabela de hashing com "famílias vazias"*/
void inicializa_hash_vazio(p_hash tab_hash);

/*Insere uma família na tabela de hashing*/
void insere_no_hash(p_hash tab_hash, Familia familia);

/*Busca uma família na tabela de hashing*/
Familia *busca_no_hash(p_hash tab_hash, char sobrenome_familia[]);

/*Libera a memória alocada para a tabela de hashing durante o programa*/
void libera_tab_hash(p_hash tab_hash);

#endif
