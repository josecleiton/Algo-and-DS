#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERRO 3141592

typedef struct node Node;
struct node
{
    char s[50];
    Node* prox;
};

void insere_lista (FILE* pal, Node** inicio)
{
    char* w = (char*) malloc (50);
    if (!w) exit (ERRO);
    while (!feof(pal))
    {
        fscanf(pal, "%s", w);
        Node* novo = (Node*) malloc (sizeof(Node));
        if (!novo) exit (-ERRO);
        strcpy (novo -> s, w);
        Node* aux = *inicio;
        if (*inicio == NULL || strcmp(aux ->s, novo ->s) > 0) //SE A LISTA ESTÁ VAZIA OU O ELEMENTO QUE QUEREMOS INSERIR É MENOR DO QUE O INICIO DELA
            *inicio = novo;
        else
        {
            Node* ant = *inicio;
            aux = ant -> prox;
            while (aux && strcmp(aux -> s, novo -> s) < 0)
            {
                ant = ant -> prox;
                aux = aux -> prox;
            }
            ant -> prox = novo;
        }
        novo -> prox = aux;
    }
}

void print_lista (Node* inicio)
{
    Node* aux;
    for (aux = inicio; aux != NULL; aux = aux -> prox)
        printf("%s\n", aux -> s);
}

char minus_maius (char c)
{
    if ((c >= 'a') && (c <= 'z'))
        c += 'A' - 'a';
    else
        c += 'a' - 'A';
    return c;
}

void busca_palavras (Node* inicio, char c)
{
    Node* aux = inicio;
    while (aux)
    {
        if (c == aux -> s[0] || minus_maius(c) == aux -> s[0])
            puts (aux->s);
        aux = aux -> prox;
    }
}

int main (void)
{
    FILE* p = fopen("pal.txt", "rt");
    if (p == NULL) exit (ERRO);
    Node* lista = NULL;
    insere_lista (p, &lista);
    //print_lista (lista);
    busca_palavras (lista, 'c');
    return 0;
}
