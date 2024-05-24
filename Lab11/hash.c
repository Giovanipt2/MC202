#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


/*Realiza o cálculo do hash, de forma a possibilitar a construção da tabela

Parâmetro:
chave -- ponteiro para char que representa a string que será usada para o cálculo da chave

Retorno:
Número inteuro que representa a posição de uma determinada família na tabela de hashing
*/
int calcula_hash(char chave[]){
    int i, n = 0;

    for (i = 0; chave[i] != '\0'; i++)
        n = (256 * n + chave[i]) % MAX;

    return n;
 
}


/*Cria a tabela de hashing que será usada no programa

Retorno:
tab_hash -- ponteiro para a struct hash que representa a tabela de hashing
*/
p_hash cria_tab_hash(){
    p_hash tab_hash = malloc(sizeof(struct hash));

    return tab_hash;
}


/*Inicializa a tabela de hashing com "famílias vazias"

Uma posição vazia do vetor será identificada com uma família cujo sobrenome é "VAZIA"

Parâmetro:
tab_hash -- ponteiro para a struct hash que representa a tabela de hashing

Retorno:
void
*/
void inicializa_hash_vazio(p_hash tab_hash){
    //família que preencherá a tabela de hashing inicialmente, indicando que ele está vazio
    Familia familia_vazia = cria_familia("\0", 0);    

    for (int i = 0; i < MAX; i++)
        tab_hash->vetor_h[i] = familia_vazia;
}


/*Insere uma família na tabela de hashing

Parâmetros:
tab_hash -- ponteiro para a struct hash que representa a tabela de hashing
familia -- objeto da struct Familia que representa a família inserida

Retorno:
void
*/
void insere_no_hash(p_hash tab_hash, Familia familia){
    int n = calcula_hash(familia.sobrenome);       //Posição que tal família teria no hash

    while (tab_hash->vetor_h[n].removida == 0 && strcmp(tab_hash->vetor_h[n].sobrenome, "\0") != 0)
        n = (n + 1) % MAX;
    
    tab_hash->vetor_h[n] = familia;
}


/*Busca uma família na tabela de hashing

Parâmetros:
tab_hash -- ponteiro para a struct hash que representa a tabela de hashing
sobrenome_familia -- string que representa o sobrenome da família buscada

Retorno:
familia -- retorna a família que estava sendo procurada
*/
Familia *busca_no_hash(p_hash tab_hash, char sobrenome_familia[]){
    int n = calcula_hash(sobrenome_familia);       //Posição que tal família teria no hash

    while (strcmp(tab_hash->vetor_h[n].sobrenome, sobrenome_familia) != 0 && strcmp(tab_hash->vetor_h[n].sobrenome, "\0") != 0) 
        n = (n + 1) % MAX; 

    return &tab_hash->vetor_h[n];
}

/*Libera a memória alocada para a tabela de hashing durante o programa

Parâmetro:
tab_hash -- ponteiro para a struct hash que representa a tabela de hashing

Retorno:
void
*/
void libera_tab_hash(p_hash tab_hash){
    free(tab_hash);
}
