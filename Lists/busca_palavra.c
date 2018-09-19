#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca_palavra.h"
#define ERRO 3141592

struct node
{
    char info[200];
    Node* prox;
};

int main (void)
{
    Node* words = lista_cria();
    FILE* palavras = fopen ("palavras.dat", "r");
    if (!palavras)
    {
        printf("Erro na abertura do arquivo 'palavras.txt'!\nTerminando o programa...\n");
        exit(-ERRO);
    }
    printf("%d STRINGS LIDAS\n", le_arquivo (palavras, &words));
    //lista_print (words);
    

    fclose (palavras);
    return 0;
}

Node* lista_cria (void)
{
    Node* inicio = (Node*) malloc (sizeof(Node));
    if (!inicio) exit (ERRO);
    inicio -> prox = NULL;
    return inicio;
}

int le_arquivo (FILE* palavras, Node** inicio)
{
    char w[200] = {'\0'};
    int n = 0;
    while (!feof(palavras))
    {
        //fgets (w, sizeof(w), palavras);
        fscanf(palavras, "%s", w);
        lista_insere (w, inicio);
        //printf("%s\n", w);
        //puts(w);
        n++;
    }
    return n;
    //lista_insere (, *inicio);
}

char *copy_string (char *str)
{
  char *tmp = malloc(strlen(str) + 1);
  if (tmp)
    strcpy(tmp, str);
  return tmp;
}

int lista_insere (char *w, Node** inicio)
{
    //verificar se o arquivo está vazio
    //if (*w == '\0') return (ERRO+2);
    //puts(w);
    Node* no = (Node*) malloc (sizeof(Node));
    char info[200] = copy_string(w);
    strcpy (no->info, info);
    Node* aux;
    if (!no) exit (ERRO);
    if (!(*inicio)) //SENÃO HÁ NÓS ENCADEADOS, ENTÃO AUX É O PRIMEIRO NÓ
    {
        aux = (*inicio) -> prox;
        *inicio = no;
    }   
    else
    {
        if (strcmp (no -> info, (*inicio) -> info) < 0)
        {
            aux = *inicio;
            *inicio = no; 
        }
        Node* ant = *inicio;
        aux = ant -> prox;
        while (aux && strcmp(no -> info, aux -> info) > 0)
        {
            ant = ant -> prox;
            aux = aux -> prox;
        }
        ant -> prox = no;
    }
    no -> prox = aux;
    return 1;  

}

void lista_print (Node* inicio)
{
    for (Node* aux = inicio; aux != NULL; aux = aux -> prox)
        puts(aux->info);
    return;
}