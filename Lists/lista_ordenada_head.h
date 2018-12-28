/*
 * POSSÍVEL IMPLEMENTAÇÃO DE UMA LISTA AUTO-ORGANIZADA COM CABEÇA!
 * POR: José Cleiton
 *
*/

typedef struct node Node;
typedef struct lista Lista;

Lista* ord_cria (void);
int ord_insere (int n, Lista* ord);
int ord_remove_um (int n, Lista* ord);
int ord_remove (int n, Lista* ord);
int ord_vazia (Lista* ord);
int ord_libera (Lista* ord);
Lista* ord_remove_pares (Lista* ord);

Lista* ord_inverte_queue (Lista* ord); //INVERSÃO COM FILA
int ord_inverte_queue_retira (Lista* ord); // INVERSÃO COM FILA
Lista* ord_inverte_stack (Lista* ord); // INVERSÃO COM PILHA
void stack_push (int n, Lista* s); // INVERSÃO COM PILHA

void ord_print (Lista* ord);
int ord_conta (Lista* ord);
int ord_pertence (int n, Lista* ord);
