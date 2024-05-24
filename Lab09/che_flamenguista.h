#ifndef che_flamenguista_h
#define che_flamenguista_h


#define MAX 202             //dado o tamanho máximo de cada linha de entrada
enum cor {VERMELHO, PRETO};

typedef struct no *p_no;

struct no{
    //respectivamente, strings que representam o nome e o tipo de uma variável 
    char nome_variavel[MAX], tipo_variavel[7];
    enum cor cor;                   //cor que o nó possui
    p_no esq, dir;                  //ponteiros, respectivamente, para os filhos esquerdo e direito de um nó
};


/*Checa se a cor de um determinado nó é vermelha*/
int eh_vermelho(p_no no);

/*Checa se a cor de um determinado nó é preta*/
int eh_preto(p_no no);

/*Rotaciona a árvore para a esquerda para manter a propriedade de que nós vermelhos sempre são filhos esquerdos*/
p_no rotaciona_esquerda(p_no raiz);

/*Rotaciona a árvore para a direita para manter a propriedade de que os filhos de um nó vermelho sempre são pretos*/
p_no rotaciona_direita(p_no raiz);

/*Sobe a cor vermelha de um nó na árvore para manter a propriedade de que somente o filho esquerdo pode ser vermelho*/
void sobe_cor_vermelha(p_no raiz);

/*Busca por uma variável na árvore*/
p_no busca_variavel(p_no raiz, char nome_variavel[]);

/*Insere recursivamente um novo nó na árvore
Ao final da inserção, verifica as possíveis correções necessárias para manter as propriedades desse tipo de árvore*/
p_no insere_recursivamente(p_no raiz, char nome_variavel[], char tipo_variavel[]);

/*Insere um novo nó na árvore
Mantém a raiz preta e chama uma função que inserirá recursivamente na árvore, fazendo os demais ajustes necessários*/
p_no insere_arvore(p_no raiz, char nome_variavel[], char tipo_variavel[]);

/*Imprime as variáveis da árvore em ordem alfabética*/
void imprime_arvore(p_no raiz);

/*Libera a memória alocada para a árvore durante o programa*/
void libera_arvore(p_no raiz);

#endif
