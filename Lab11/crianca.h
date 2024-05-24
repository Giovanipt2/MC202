#ifndef crianca_h
#define crianca_h

typedef struct{
    char nome[11];          //String que representa o nome da criança que acessou o serviço
    char sobrenome[11];     //String que representa o sobrenome da criança que acessou o serviço
    int n_doces;            //Número de doces ganhos pela criança
} Crianca;


/*Cria a criança que acessou o serviço*/
Crianca cria_crianca(char nome[], char sobrenome[]);

/*Adiciona os doces ganhos pela criança*/
void adiciona_doces_ganhos(Crianca *p_crianca, int n_doces_ganhos);

/*Verifica se a criança ganhou algum doce, ou terá que receber doces da prefeitura*/
int ganhou_doce(Crianca crianca);

#endif
