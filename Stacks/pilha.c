#include <stdio.h>
#include <stdlib.h>
#define REP 10

typedef struct listano ListaNo;
typedef struct pilha Pilha;
struct listano
{
    float info;
    ListaNo* prox;
};

struct pilha
{
    ListaNo* prim;
};

Pilha* pilha_cria (void)
{
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p -> prim = NULL;
    return p;
}

void pilha_push (Pilha* p, float v)
{
    ListaNo* n = (ListaNo*) malloc(sizeof(ListaNo));
    n -> info = v;
    n -> prox = p -> prim;
    p -> prim = n;
}

float pilha_pop (Pilha* p)
{
    ListaNo* t = p -> prim;
    float v = t -> info;
    p -> prim = t -> prox;
    free (t);
    return v;
}

int pilha_vazia (Pilha* p)
{
    return (p -> prim == NULL);
}

void pilha_libera (Pilha* p)
{
    ListaNo* q = p -> prim;
    while (q != NULL)
    {
        ListaNo* t = q -> prox;
        free (q);
        q = t;
    }
    free (p);
}

void pilha_imprime (Pilha* p)
{
    if(pilha_vazia(p))
        exit(-69);
    for (ListaNo* q = p -> prim; q != NULL; q = q -> prox)
        printf("%f\n", q -> info);
}

int pilha_elementos (Pilha* p)
{
    if(pilha_vazia(p))
    {
        printf("A PILHA ESTÁ VAZIA, IMPOSSÍVEL MOSTRAR A PILHA!\nTerminando o programa...\n");
        exit (69);
    }
    ListaNo* aux = p -> prim;
    int n = 0;
    while (aux != NULL)
    {
        aux = aux -> prox;
        n++;
    }
    return n;
}

int main (void)
{
    Pilha* topo = pilha_cria ();
    int num;
    char op;
    printf("BEM-VINDO A PILHA\n");
    system ("pause");
	for(;;)
    {
		system("cls");
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
				pilha_pop (topo);
				break;

			case 'a':
			    pilha_libera (topo);
			break;

			case 'm':
			    pilha_imprime (topo);
                system ("pause");
			break;

            case 'q':
                printf("Na pilha há: %d elementos\n", pilha_elementos(topo));
                system ("pause");
                break;

			case 'e':
			    exit(num*num*num);
			break;

			default:
				printf("Comando Invalido\n");
                system ("pause");
		}


	}
    return 0;
}
