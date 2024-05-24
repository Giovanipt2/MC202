#include "peca.h"

typedef struct funcionario *p_funcionario;

struct funcionario{
    p_peca mao;             //a mão do funcionário é usada para saber se ele está ou não ocupado e, se estiver, qual a peça que ele possui
    char tipo;              //caractere usado para identificar qual é o classficador ('c') e qual é o empacotador ('e')
};


/*Cria o funcionário, podendo representar o classificador ou o embalador*/
p_funcionario cria_funcionario(char tipo_funcionario);

/*Verifica se a mão do funcionário está vazia, possibilitando que ele pegue uma peça*/
int mao_vazia(p_funcionario funcionario);

/*Verifica se o funcionário já acabou de processar a peça, com base na tabela fornecida por Antônio*/
int acabou_processamento(p_funcionario funcionario, int mins_processamento);

/*Pega (ou seja, adiciona na mão) uma peça disponível*/
void pega_peca(p_funcionario funcionario, p_peca peca);

/*Larga (ou seja, retira da mão) a peça que já foi processada*/
p_peca larga_peca(p_funcionario funcionario);

/*Libera a memória alocada para o funcionário durante a simulação*/
void ferias(p_funcionario funcionario);
