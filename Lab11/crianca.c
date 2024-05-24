#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crianca.h"


/*Cria a criança que acessou o serviço

Parâmetros:
nome -- String que representa o nome da criança que acessou o serviço
sobrenome -- String que representa o sobrenome da criança que acessou o serviço

Retorno:
crianca -- objeto da struct Crianca que representa a criança que acessou o serviço
*/
Crianca cria_crianca(char nome[], char sobrenome[]){
    Crianca crianca;

    strcpy(crianca.nome, nome);
    strcpy(crianca.sobrenome, sobrenome);
    crianca.n_doces = 0;

    return crianca;
}   


/*Adiciona os doces ganhos pela criança

Parâmetros:
p_crianca -- ponteiro para a struct Crianca que permite alterar um campo do objeto crianca localmente
n_doces_ganhos -- número inteiro que representa a quantidade de doces que tal criança ganhou

Retorno:
void
*/
void adiciona_doces_ganhos(Crianca *p_crianca, int n_doces_ganhos){
    p_crianca->n_doces += n_doces_ganhos;
}


/*Verifica se a criança ganhou algum doce, ou terá que receber doces da prefeitura

Parâmetros:
crianca -- objeto da struct Crianca que representa a criança inserida

Retorno:
void
*/
int ganhou_doce(Crianca crianca){
    if (crianca.n_doces > 0)
        return 1;

    return 0;
}
