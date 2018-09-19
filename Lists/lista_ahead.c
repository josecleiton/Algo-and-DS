#include <stdio.h>
#include <stdlib.h>
#define ERRO 3141592

typedef struct node Node;
Node* lista_cria (void);
int lista_insere (int n, Node** inicio);
int lista_remove_um (int n, Node** inicio);
int lista_remove (int n, Node** inicio); //REMOVE TODAS AS OCORRENCIAS DE n NAS LISTAS
int lista_vazia (Node* inicio);
int lista_libera (Node** inicio);
Node* lista_remove_pares (Node** inicio); //PEGA OS PARES DA LISTA INSERIDA E CRIA UMA PILHA COM ELES, LEMBRANDO QUE ESSES VALORES VÃO ESTAR INVERTIDOS, PARA ACERTAR A ORDEM PRECISA APENAS CHAMAR A FUNÇÃO COM O PARAMETRO CORRETO!
Node* lista_remove_impares (Node** inicio); //PEGA OS IMPARES DA LISTA INSERIDA E CRIA UMA PILHA COM ELES, LEMBRANDO QUE ESSES VALORES VÃO ESTAR INVERTIDOS, PARA ACERTAR A ORDEM PRECISA APENAS CHAMAR A FUNÇÃO COM O PARAMETRO CORRETO!
Node* stack_inverte (Node** inicio); //em construção
void lista_print (Node* inicio);
int lista_conta (Node* inicio);
int lista_pertence (int n, Node* inicio);
Node* lista_inverte (Node** inicio);
void stack_push (int n, Node** s);

struct node
{
    int info;
    Node* prox;
};

int main (void)
{
    Node* list = NULL;
    Node *pares, *impares;
    lista_insere (3, &list);
    lista_insere (5, &list);
    lista_insere (6, &list);
    lista_insere (6, &list);
    lista_insere (14, &list);
    lista_insere (-4, &list);
    //lista_remove (6, &list);
    pares = lista_remove_pares (&list);
    pares = lista_remove_pares (&pares);
    impares = lista_remove_impares (&list);
    impares = lista_remove_impares (&impares);
    printf("PILHA COM OS PARES\n");
    lista_print (pares);
    putchar('\n');
    printf("PILHA COM OS IMPARES\n");
    lista_print (impares);
    putchar('\n');
    lista_libera (&list);
    lista_print (list);
    return 0;
}

int lista_insere (int n, Node** inicio)
{
    Node* no = (Node*) malloc (sizeof(Node));
    if (!no) exit (ERRO);
    Node* aux = *inicio;
    no -> info = n;
    if (*inicio == NULL || n < aux -> info)
        *inicio = no;
    else
    {
        Node* ant = *inicio;
        aux = ant -> prox;
        while (aux && n > aux -> info)
        {
            ant = ant -> prox;
            aux = aux -> prox;
        }
        ant -> prox = no;
    }
    no -> prox = aux;
}
int lista_remove_um (int n, Node** inicio); //EM CONSTRUÇÃO
int lista_remove (int n, Node** inicio) //REMOVE TODAS AS OCORRENCIAS DE n NAS LISTAS
{
    if (lista_vazia(*inicio)) return ERRO/2;
    Node *aux, *rem, *ant;
    ant = NULL;
    aux = *inicio;
    while (aux)
    {
        rem = aux;
        aux = aux -> prox;
        if (n == (*inicio) -> info)
        {
            *inicio = aux;
            free (rem);
        }
        else
        {
            if (rem && n == rem -> info)
            {
                ant -> prox = aux;
                free (rem);
                rem = NULL;
            }
            else
                ant = rem;
        }
    }
}
int lista_vazia (Node* inicio)
{
    if (!inicio)
        return 1;
    else
        return 0;
}
int lista_libera (Node** inicio)
{
    Node* aux = *inicio;
    if (aux)
    {
        aux = aux -> prox;
        while (aux)
            free (aux);
        free (*inicio);
        *inicio = NULL;
    }
    else
        printf("LISTA JÁ NULA!\n");
    return 1;

    /*
    if ((*inicio) ->)
    {
        Node* aux = (*inicio) -> prox;
        while (aux)
            free (aux);
        free (*inicio);
        *inicio = NULL;
        return 1;
    }*/
}
Node* lista_remove_pares (Node** inicio)
{
    if (lista_vazia(*inicio)) return NULL;
    Node *aux, *rem, *ant, *pares;
    pares = ant = NULL;
    aux = *inicio;
    while (aux)
    {
        rem = aux;
        aux = aux -> prox;
        if (rem && !(rem -> info % 2))
        {
            if (rem == *inicio)
                *inicio = aux;
            else
                ant -> prox = aux;
            stack_push (rem -> info, &pares);
            free (rem);
        }
        else
            ant = rem;
    }
    return (pares); 
}
Node* lista_remove_impares (Node** inicio)
{
    if (lista_vazia(*inicio)) return NULL;
    Node *aux, *rem, *ant, *pares;
    pares = ant = NULL;
    aux = *inicio;
    while (aux)
    {
        rem = aux;
        aux = aux -> prox;
        if (rem && (rem -> info % 2))
        {
            if (rem == *inicio)
                *inicio = aux;
            else
                ant -> prox = aux;
            stack_push (rem -> info, &pares);
            free (rem);
        }
        else
            ant = rem;
    }
    return (pares); 
}
Node* stack_inverte (Node** inicio)
{

}
void lista_print (Node* inicio)
{
    if (!inicio) return;
    for (Node* aux = inicio; aux != NULL; aux = aux -> prox)
        printf("%d\n", aux -> info);
}
int lista_conta (Node* inicio)
{
    int n = 0;
	for (Node* aux = inicio; aux != NULL; aux = aux -> prox)
		n++;
    return n;
}
int lista_pertence (int n, Node* inicio)
{
    Node* aux;
    for (aux = inicio; aux != NULL; aux = aux -> prox)
    {
        if (aux -> info == n)
            return 1;
    }
    return 0;
}
Node* lista_converte (Node** inicio)
{
    Node *topo, *aux, *ant, *rem;
    aux = *inicio;
    if (!aux || !(aux -> prox))
    {
        topo = *inicio;
        return topo;
    }
    ant = aux;
    aux = aux -> prox;
    while (aux)
    {
        rem = aux;
        aux = aux -> prox;
    }


}
void stack_push (int n, Node** s)
{
    Node* no = (Node*) malloc (sizeof(Node));
    if (!no) exit (ERRO);
    no -> info = n;
    no -> prox = *s;
    *s = no;
}