#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_ligada.h"


int main(){
    p_lista_ligada lista_livros;                    //ponteiro para a struct no que representa a lista de livros de Wickerbottom, na forma de lista ligada
    char comando[60], comando_passado[60] = "";     //comando que será dado ao programa, referente à função que se deseja chamar; e último comando dado ao programa, para saber a posiçãop de inserção

    lista_livros = cria_lista_livros();
    
    while (scanf("%s", comando) != EOF){
        if (strcmp(comando, "inicio") == 0){            
            strcpy(comando_passado, comando);
            continue;
        }

        else if (strcmp(comando, "final") == 0){
            strcpy(comando_passado, comando);
            continue;
        }

        else{
            decide_funcao(lista_livros, comando_passado, comando);
            strcpy(comando_passado, comando);      //necessário para que o comando não seja utilizado mais vezes que o devido
        }
    }
    
    libera_lista(lista_livros->inicio);
    free(lista_livros);

    return 0;
}
