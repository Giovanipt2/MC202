#ifndef prato_h
#define prato_h


typedef struct prato *p_prato;      //ponteiro para a struct prato

struct prato{
    char nome_prato[26];        //nome do prato
};


/*Cria o prato que foi pedido pelo sobrevivente*/
p_prato cria_prato(char nome_prato[]);

/*Libera a memória alocada para o prato durante o programa*/
void libera_prato(p_prato prato);

#endif
