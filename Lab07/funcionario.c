#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionario.h"
#include "peca.h"


/*Cria o funcionário, podendo representar o classificador ou o embalador

Parâmetro:
tipo_funcionario -- caractere que indica qual é o tipo do funcionário ('c' para classificador e 'e' para empacotador)

Retorno:
funcionario -- ponteiro para a struct funcionario
*/
p_funcionario cria_funcionario(char tipo_funcionario){
    p_funcionario funcionario = malloc(sizeof (struct funcionario));
    funcionario->mao = NULL;
    funcionario->tipo = tipo_funcionario;

    return funcionario;
}


/*Verifica se a mão do funcionário está vazia, possibilitando que ele pegue uma peça

Parâmetro:
funcionario -- ponteiro para a struct funcionario

Retorno:
1, caso a mão dele esteja vazia, ou 0, caso contrário
*/
int mao_vazia(p_funcionario funcionario){
    if (funcionario->mao == NULL)
        return 1;
    
    return 0;
}


/*Verifica se o funcionário já acabou de processar a peça, com base na tabela fornecida por Antônio

Parâmetro:
funcionario -- ponteiro para a struct funcionario
mins_processamento -- número inteiro que representa os minutos que uma peça está em uma das etapas de processamento

Retorno:
1, caso a peça já tenha sido processada, ou 0, caso contrário
*/
int acabou_processamento(p_funcionario funcionario, int mins_processamento){
    if (funcionario->tipo == 'c'){
        if (funcionario->mao->t_classificacao == mins_processamento)
            return 1;
    }
        
    else{
        if (funcionario->mao->t_embalagem == mins_processamento)
            return 1;
    }

    return 0;
}


/*Pega (ou seja, adiciona na mão) uma peça disponível

Parâmetros:
funcionario -- ponteiro para a struct funcionario

Retorno:
void
*/
void pega_peca(p_funcionario funcionario, p_peca peca){
    funcionario->mao = peca;
}


/*Larga (ou seja, retira da mão) a peça que já foi processada

Parâmetro:
funcionario -- ponteiro para a struct funcionario

Retorno:
peca_lardada -- ponteiro para a struct peça que representa a peça sai da mão do funcionário
*/
p_peca larga_peca(p_funcionario funcionario){
    p_peca peca_largada = funcionario->mao;
    funcionario->mao = NULL;

    return peca_largada;
}


/*Libera a memória alocada para o funcionário durante a simulação

O nome é férias porque não tem mais trabalho :)

Parâmetro:
funcionario -- ponteiro para a struct funcionario

Retorno:
void
*/
void ferias(p_funcionario funcionario){
    free(funcionario);
}
