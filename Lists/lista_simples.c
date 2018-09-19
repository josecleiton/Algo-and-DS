#include <stdio.h>
#include <stdlib.h>
#include "lista_simples.h"

struct lista
{
	ListaNo* prim;
};

struct listano
{
	int info;
	ListaNo* prox;
};

int main (void)
{
	return 0;
}

Lista* lst_cria (void)
{
	Lista* l = (Lista*) malloc(sizeof(Lista));
	l -> prim = NULL;
	return 0;
}

void lst_insere (Lista* l, int v)
{
	ListaNo* novo = (ListaNo*) malloc(sizeof(ListaNo));
	novo -> info = v;
	novo -> prox = l -> prim;
	l -> prim = novo;
}

void lst_imprime (Lista* l)
{
	for (ListaNo* p=l->prim; p!=NULL; p=p->prox)
		printf("infor = %d\n", p->info);
}