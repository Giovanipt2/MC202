#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "familia.h"


/*Verfica se a família já começou com seu número de doces igual a zero

Parâmetro:
n_doces -- número inteiro que representa o número de doces que a família começou

Retorno:
1, caso a família tenha começado com 0 doces; ou 0, caso contrário
*/
int comecou_zerada(int n_doces){
    if (n_doces == 0)
        return 1;

    return 0;
}


/*Cria a família inserida no programa

Parâmetros:
sobrenome -- string que representa o sobrenome da família inserida
n_doces -- número de doces que a família possui

Retorno:
familia -- objeto da struct Familia que representa a família inserida
*/
Familia cria_familia(char sobrenome[], int n_doces){
    Familia familia;
    
    strcpy(familia.sobrenome, sobrenome);
    familia.n_doces = n_doces;
    familia.removida = 0;       //No começo, a família não foi removida; por isso o 0, significando FALSO
    familia.ja_ficou_zerada = 0;

    if (comecou_zerada(n_doces))
        familia.comecou_zerada = 1;

    else
        familia.comecou_zerada = 0;

    return familia;
}


/*Verifica se a família tem doces suficientes para dar a uma criança de acordo com a nota dada

Parâmetros:
familia -- objeto da struct Familia que representa a família inserida
n_doces_a_dar -- número de doces que a família deveria dar para a criança, com base na nota dada por ela

Retorno:
1, caso a família tenha doces suficientes; ou 0, caso contrário
*/
int tem_doces_suficientes(Familia familia, int n_doces_a_dar){
    if (familia.n_doces >= n_doces_a_dar)
        return 1;

    return 0; 
}


/*Verifica se a família ficou sem doces

Parâmetro:
familia -- objeto da struct Familia que representa a família inserida

Retorno:
1, caso a família ainda tenha doces; ou 0, caso contrário
*/
int ficou_sem_doces(Familia familia){
    if (familia.n_doces == 0)
        return 1;

    return 0;
}


/*Adiciona à quantidade atual o número de doces comprados pela família

Parâmetros:
p_família -- ponteiro para a struct Familia que permite alterar um campo do objeto familia localmente
n_doces_comprados -- quantidade de doces que foram comprados pela família

Retorno:
void
*/
void adiciona_doces_comprados(Familia *p_familia, int n_doces_comprados){
    p_familia->n_doces += n_doces_comprados;
}


/*Calcula, com base na nota dada à fantasia, o número de doces que a família deve dar à criança

O valor pode ser diferente do referente à nota dado caso a família não tenha doces o suficiente para dar

Parâmetros:
familia -- objeto da struct Familia que representa a família inserida
nota_dada -- string que representa a nota que tal família deu à fantasia da criança

Retorno:
3, se a nota dada foi "Boa", 2, caso tenha sido "Media", ou 1, se ela foi "Ruim"
*/
int calcula_doces_dados(Familia familia, char nota_dada[]){
    int n_doces_a_dar;

    if (strcmp(nota_dada, "Boa") == 0)
        n_doces_a_dar = 3;

    else if (strcmp(nota_dada, "Media") == 0)
        n_doces_a_dar = 2;

    else if (strcmp(nota_dada, "Ruim") == 0)
        n_doces_a_dar = 1;

    if (tem_doces_suficientes(familia, n_doces_a_dar))
        return n_doces_a_dar;

    return familia.n_doces;
}   


/*Diminui, da quantidade de doces da família, o número de doces dados a uma criança

Parâmetros:
p_família -- ponteiro para a struct Familia que permite alterar um campo do objeto familia localmente
n_doces_retirados -- número de doces que devem ser subtraídos da quantidade de doces que a família tinha

Retorno:
void
*/
void retira_doces_dados(Familia *p_familia, int n_doces_retirados){
    p_familia->n_doces -= n_doces_retirados;
}


/*Marca a família que saiu de sua casa, ficando fora do programa

Parâmetro:
p_família -- ponteiro para a struct Familia que permite alterar um campo do objeto familia localmente

Retorno:
void
*/
void retira_familia(Familia *p_familia){
    p_familia->removida = 1;        //1 significa VERDADEIRO para tal campo; ou seja, a família foi removida
}
