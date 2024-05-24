#include <stdio.h>
#include <stdlib.h>

typedef struct lista_ligada *p_lista_ligada;
typedef struct no *p_no;

struct lista_ligada{
    //respectivamente, ponteiros para o início, para o final e para o último livro inserido na lista ligada
    p_no inicio, fim, ultimo_add;
};

struct no{
    char livro[60];                 //string que representa o livro que está guardado em um nó
    p_no prox, ant;                 //respetivamente, ponteiro que aponta para o próximo nó e para o nó anterior
};


/*Cria o ponteiro para o início da lista ligada, sendo que, este, é vazio*/
p_lista_ligada cria_lista_livros();

/*Ajusta o formato da string, retirando o espaço em branco desnecessário e o '\n', ajustando a posição do '\0'*/
void ajusta_string(char livro[]);

/*Encontra a posição de inserção do livro na lista ligada, considerando os comandos dados*/
char encontra_posicao_add(char comando_passado[]);

/*Adiciona o livro pedido na lista de livros na posição pedida*/
p_lista_ligada adiciona_livro(p_lista_ligada lista_livros, char comando_passado[], char livro[]);

/*Busca e remove o pedido da lista de livros*/
p_lista_ligada remove_livro(p_lista_ligada lista_livros, char livro_removido[]);

/*Imprime os livros da lista com base na posição em que foram colocados*/
void imprime_lista(p_lista_ligada lista_livros);

/*Libera cada um dos nós da lista de livros utilizada*/
void libera_lista(p_no livro_atual);

/*Decide qual função será chamda com base no comando dado*/
void decide_funcao(p_lista_ligada lista_livros, char comando_passado[], char comando[]);
