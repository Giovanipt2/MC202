#ifndef arvore_binaria_h
#define arvore_binaria_h


typedef struct no *p_no;

struct no{
    char dado;          //caractere que representa um dos elementos da expressão
    p_no esq, dir;      //respectivamente, ponteiros para a struct nó que apontam para os filhos esquerdo e direito de um nó pai
};


/*Cria a árvore binária que conterá os elementos da expressão dada*/
p_no cria_no(char elemento, p_no esq, p_no dir);

/*Decide se um caractere é um número ou não*/
int eh_numero(char caractere);

/*Decide se um caractere é um operador ou não*/
int eh_operador(char caractere);

/*Otimiza a expressão contida na árvore*/
p_no otimiza_expressao(p_no raiz);

/*Imprime a expressão da forma correta, considerando os parênteses*/
void imprime_expressao(p_no raiz) ;

/*Libera os filhos de uma raiz caso a otimização tenha sido possível*/
void libera_filhos(p_no raiz);

/*Libera a memória alocada para a árvore durante o programa*/
void libera_arvore(p_no raiz);

#endif
