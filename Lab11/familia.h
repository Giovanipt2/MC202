#ifndef familia_h
#define familia_h

typedef struct{
    char sobrenome[11]; //Sobrenome da família
    int n_doces;        //Número de doces que a família possui
    int removida;       //Número inteiro que diz se a família foi removida ou não (1, em caso afirmativo; ou 0, caso contrário)
    int comecou_zerada; //Número inteiro que indica se a família já começou com 0 doces (1, em caso afirmativo; ou 0, caso contrário)
    //Número inteiro que indica se a família já ficou sem doces ou não, para que ela NÃO seja impressa mais de uma vez 
    int ja_ficou_zerada;   //Tal campo assume valor 1, caso já tenha sido impressa; ou 0, caso contrário 
} Familia;  


/*Verfica se a família já começou com seu número de doces igual a zero*/
int comecou_zerada(int n_doces);

/*Cria família que foi inserida no programa*/
Familia cria_familia(char sobrenome[], int n_doces);

/*Verifica se a família tem doces suficientes para dar a uma criança de acordo com a nota dada*/
int tem_doces_suficientes(Familia familia, int n_doces_a_dar);

/*Verifica se a família ficou sem doces*/
int ficou_sem_doces(Familia familia);

/*Adiciona à quantidade atual o número de doces comprados pela família*/
void adiciona_doces_comprados(Familia *p_familia, int n_doces_comprados);

/*Calcula, com base na nota dada à fantasia, o número de doces que a família deve dar à criança*/
int calcula_doces_dados(Familia familia, char nota_dada[]);

/*Diminui, da quantidade de doces da família, o número de doces dados a uma criança*/
void retira_doces_dados(Familia *p_familia, int n_doces_retirados);

/*Marca a família que saiu de sua casa, ficando fora do programa*/
void retira_familia(Familia *p_familia);

#endif
