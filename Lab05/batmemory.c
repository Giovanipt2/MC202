#include <stdio.h>
#include <stdlib.h>
#include "bat_vetor.h"


int main(){
    //bat_memoria é um ponteiro para a struct bat_vetor
    p_bat_vetor bat_memoria;
    bat_memoria = cria_bat_memoria();

    //variável que armazena o número de comandos que serão dados para o programa
    int i, n_comandos;
    scanf("%d", &n_comandos);

    for (i = 0; i < n_comandos; i++){
        char bat_comando[10];
        scanf("%s", bat_comando);
        decide_bat_funcao(bat_memoria, bat_comando);
    }

    bat_libera_memoria(bat_memoria->bat_dados);
    bat_libera_memoria(bat_memoria);

    return 0;
}
