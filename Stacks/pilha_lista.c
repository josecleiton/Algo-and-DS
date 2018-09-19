/*
    PILHA DINAMICA COM LISTAS ENCADEADAS
    BY JOSÉ CLEITON
    CREDITOS DO MENU AO NIILISTA OTACO
*/

#include <stdio.h>
#include <stdlib.h>
#include "pilha_lista.h"

struct nodo
{
    int info;
    Nodo* prox;
};

struct pilha
{
    Nodo* prim;
};

int main (void)
{
    Pilha* topo = pilha_cria ();
    int num;
    char op;
    printf("BEM-VINDO A PILHA\n");
    system ("read -rsp $'Press enter to continue...\n'");
	for(;;)
    {
		system("clear");
		printf("\nMenu:\n i= Inserir\n r= Retirar\n a= apagar a fila\n m= mostrar fila\n q = quantifica elementos da fila\n e= sair\n\nopção = ");
        scanf(" %c", &op);
		switch(op)
        {
			case 'i':
				printf("Qual numero sera inserido?: ");
				scanf("%d", &num);
				pilha_push (topo, num);
				break;
			
			case 'r':
				printf("Elemento %d retirado!\n", pilha_pop (topo));
                system ("read -rsp $'Press enter to continue...\n'");
				break;

			case 'a':
			    pilha_libera (topo);
			break;
			
			case 'm':
			    pilha_imprime (topo);
                system ("read -rsp $'Press enter to continue...\n'");
			break;

            case 'q':
                printf("Na pilha há: %d elementos\n", pilha_elementos(topo));
                system ("read -rsp $'Press enter to continue...\n'");
                break;

			case 'e':
			    exit(num*num*num);
			break;
			
			default:
				printf("Comando Invalido\n");
                system ("read -rsp $'Press enter to continue...\n'");
		}
		
		
	}
    return 0;
}

Pilha* pilha_cria (void)
{
    Pilha* p = (Pilha*) malloc (sizeof(Pilha));
    p -> prim = NULL;
    return p;
}

void pilha_push (Pilha* p, int v)
{
    Nodo* no = (Nodo*) malloc (sizeof(Nodo));
    no -> info = v;
    no -> prox = p -> prim;
    p -> prim = no;
}

int pilha_pop (Pilha* p)
{
    if(pilha_vazia(p))
    {
        printf("A PILHA ESTÁ VAZIA, IMPOSSÍVEL RETIRAR ALGUM ELEMENTO!\nTerminando o programa...\n");
        exit (-69);
    }
    Nodo* aux = p -> prim;
    int v = aux -> info;
    p -> prim = aux -> prox;
    free (aux);
    return v;
}

int pilha_vazia (Pilha* p)
{
    return (p -> prim == NULL);
}

void pilha_libera (Pilha* p)
{
    if (pilha_vazia(p))
    {
        printf("PILHA VAZIA!\nTerminando o programa...\n");
        exit(69*69);
    }
    Nodo* aux = p -> prim;
    while (aux != NULL)
    {
        Nodo* temp = aux -> prox;
        free (aux);
        aux = temp;
    }
    free (p);
    pilha_pop (p);
}

void pilha_imprime (Pilha* p)
{
    if(pilha_vazia(p))
    {
        printf("PILHA VAZIA!\nTerminando o programa...\n");
        exit(69);
    }
    Nodo* aux;
    for (aux = p -> prim; aux != NULL; aux = aux -> prox)
        printf("%d\n", aux -> info);
}

int pilha_elementos (Pilha* p)
{
    if(pilha_vazia(p))
    {
        printf("A PILHA ESTÁ VAZIA, IMPOSSÍVEL MOSTRAR A PILHA!\nTerminando o programa...\n");
        exit (69);
    }
    Nodo* aux;
    int n = 0;
    for (aux = p -> prim; aux != NULL; aux = aux -> prox)
        n++;
    return n;
}