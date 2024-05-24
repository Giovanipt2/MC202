#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "crianca.h"


//Usado para facilitar a leitura do código, possibilitando maior clareza na distinção dos tipos de comandos
enum tipo_comando {ENTRAR, SAIR, COMPRAR, TRICKORTREAT, FINALIZAR, NDA};


/*Ajusta a string, retirando o \n do final dela

Parâmetro:
string -- string que será ajustada

Retorno:
void
*/
void ajusta_string(char string[]){
    for (int i = 1; string[i - 1] != '\0'; i++){
        if (string[i] == '\n')
            string[i] = '\0';
    }
}


/*Verifica, a partir da entrada, qual o tipo de comando dado

Parâmetro:
comando_lido -- string que representa o comando dado na linha

Retorno:
comando -- variável do tipo tipo_comando que guarda o tipo do comando dado
*/
enum tipo_comando decide_tipo_comando(char comando_lido[]){
    switch (comando_lido[0]){
        case 'E':
            return ENTRAR;
            break;
    
        case 'S':
            return SAIR;
            break;

        case 'C':
            return COMPRAR;
            break;

        case 'T':
            return TRICKORTREAT;
            break;

        case 'F':
            return FINALIZAR;
            break;

        default:
            return NDA;
            break;
    }
}


int main(){
    enum tipo_comando comando;      //Comando que será dado ao programa
    char comando_lido[14];  //String que representa o comando lido na linha em questão

    p_hash tab_hash = cria_tab_hash();  //Tabela de hashing que será usada durante o programa
    inicializa_hash_vazio(tab_hash);    //Inicializa a tabela de hashing com "famílias vazias" (posições desocupadas)
    Crianca crianca;            //Variável do tipo criança que será usada para representar a criança da vez

    while (1){
        scanf("%s", comando_lido);

        //Comando que foi dado ao serviço
        comando = decide_tipo_comando(comando_lido);

        if (comando == FINALIZAR)
            break;

        else if (comando == ENTRAR){
            char sobrenome_familia[11]; //String que representa o sobrenome da família
            int n_doces_familia;        //Número inteiro que representa o número de doces da família inicialmente
            scanf("%s %d", sobrenome_familia, &n_doces_familia);

            Familia familia = cria_familia(sobrenome_familia, n_doces_familia);
            insere_no_hash(tab_hash, familia);
        }

        else if (comando == SAIR){
            char sobrenome_familia[11]; //String que representa o sobrenome da família
            scanf("%s", sobrenome_familia);
            ajusta_string(sobrenome_familia);

            Familia *familia_retirada = busca_no_hash(tab_hash, sobrenome_familia);
            retira_familia(familia_retirada);
            printf("A familia %s saiu com %d doce(s) sobrando.\n", familia_retirada->sobrenome, familia_retirada->n_doces);
        }

        else if (comando == COMPRAR){
            char sobrenome_familia[11]; //String que representa o sobrenome da família
            int n_doces_comprados;      //Número de doces comprados pela família
            scanf("%s %d", sobrenome_familia, &n_doces_comprados);

            Familia *familia_que_comprou = busca_no_hash(tab_hash, sobrenome_familia);

            if (n_doces_comprados != 0) 
                familia_que_comprou->comecou_zerada = 0;    //Se a família comprou doces, não importa mais que ela tenha começado zerada

            adiciona_doces_comprados(familia_que_comprou, n_doces_comprados);
            printf("A familia %s agora possui %d doces.\n", familia_que_comprou->sobrenome, familia_que_comprou->n_doces);
        }

        else if (comando == TRICKORTREAT){
            //Respectivamente, as strings que representam o nome e o sobrenome da criança que acessou o serviço
            char nome_crianca[11], sobrenome_crianca[11];
            int n_casas;        //Quantidade de casas disponíveis para a criança visitar
            scanf("%s %s %d", nome_crianca, sobrenome_crianca, &n_casas);

            crianca = cria_crianca(nome_crianca, sobrenome_crianca);

            for (int i = 0; i < n_casas; i++){
                //Respecitivamente as strings que representam o sobrenome da família e a nota dada à fantasia da criança
                char sobrenome_familia[11], nota_dada[6];
                
                scanf("%s %s", sobrenome_familia, nota_dada);
                Familia *familia_visitada = busca_no_hash(tab_hash, sobrenome_familia);

                int n_doces_a_dar = calcula_doces_dados(*familia_visitada, nota_dada);
                retira_doces_dados(familia_visitada, n_doces_a_dar);

                //Verifica se a família não tem mais doces, se ela não tinha começado já zerada, e a última condição é feita para que a família não seja printada mais de uma vez
                if (ficou_sem_doces(*familia_visitada) && familia_visitada->comecou_zerada != 1 && familia_visitada->ja_ficou_zerada != 1){
                    printf("A familia %s ficou sem doces.\n", familia_visitada->sobrenome);
                    familia_visitada->ja_ficou_zerada = 1;
                }

                adiciona_doces_ganhos(&crianca, n_doces_a_dar);
            }

            if (!ganhou_doce(crianca))
                printf("%s %s recebeu 10 doces da prefeitura.\n", crianca.nome, crianca.sobrenome);

            else
                printf("%s %s recebeu %d doce(s) das familias.\n", crianca.nome, crianca.sobrenome, crianca.n_doces);
        }
    }

    libera_tab_hash(tab_hash);

    return 0;
}
