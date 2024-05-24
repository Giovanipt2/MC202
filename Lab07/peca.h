#ifndef peca_h
#define peca_h

typedef struct peca *p_peca;        //ponteiro para a struct peça (juro que é só um ponteiro hahhaahahahahha)

struct peca{
    char tamanho[10];                           //string referente ao tamanho da embalagem (pequeno, médio ou grande)
    int tipo, t_classificacao, t_embalagem;     //respectivamente, tipo da embalagem (1 ou 2), e os tempos de classificação e embalagem da peça
};


/*Inicializa a peça com base na entrada da simulação*/
p_peca cria_peca(char tamanho_peca[], int tipo_peca);

/*Calcula o tempo necessário para a classificação da peça ser finalizada, com base em seu tamanho*/
int calcula_tempo_classificacao(p_peca peca);

/*Calcula o tempo necessário para embalar a peça, com base no seu tipo*/
int calcula_tempo_embalagem(p_peca peca);

/*Libera a memória alocada para a peça*/
void libera_peca(p_peca peca);

#endif