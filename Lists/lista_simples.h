/*
FUNÇÕES DO LIVRO WALDEMAR CELES
INTRODUÇÃO A ESTRUTURA DE DADOS
*/

typedef struct lista Lista;
typedef struct listano ListaNo;

/* função de criação: retorna uma lista inicialmente vazia */
Lista* lst_cria (void);

/* inserção no início */
void lst_insere (Lista* l, int v);

/* função imprime valores dos elementos */
void lst_imprime (Lista* l);

/* função pertence: verifica se um elemento está na lista */
int pertence (Lista* l, int v);

/* função insere_ordenado: insere elemento em ordem */
void lst_insere_ordenado (Lista* l, int v);

/* função retira: retira elemento da lista */
void lst_retira (Lista* l, int v);

/* função vazia: retorna 0 se vazia ou 1 se não vazia */
int lst_vazia (Lista* l);

/* função libera lista */
void lst_libera (Lista* l);