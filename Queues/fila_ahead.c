#include <stdio.h>
#include <stdlib.h>
#define ERRO 3141592

typedef struct node Node;
struct node
{
    int info;
    Node* prox;
};

void fila_insere (int n, Node** fila);
void fila_print (Node* fila);
int lista_remove (int n, Node** inicio);

int main (void)
{
    Node* fila = NULL;
    int num;
    char op;
    printf("BEM-VINDO A PILHA\n");
    system ("read -rsp $'Press enter to continue...\n'");
	for(;;)
    {
        system("clear");
		printf("\nMenu:\n i= Inserir\n r= Retirar\n a= apagar a fila\n m= mostrar fila\n q = quantifica elementos da fila (em construção)\n e= sair\n\nopção = ");
        scanf(" %c", &op);
		switch(op)
        {
			case 'i':
				printf("Qual numero sera inserido?: ");
				scanf("%d", &num);
				fila_insere (num, &fila);
				break;
			
			case 'r':
				printf("Elemento(s) %d retirado(s)!\n", lista_remove (3,&fila));
                system ("read -rsp $'Press enter to continue...\n'");
				break;
            
            /*
			case 'a':
			    fila_libera (fila);
			break;
			*/
			case 'm':
			    fila_print (fila);
                getchar ();
                scanf("%*c");
			break;

            //case 'q':
            //    printf("Na pilha há: %d elementos\n", pilha_elementos(topo));
             //   system ("read -rsp $'Press enter to continue...\n'");
             //   break;

			case 'e':
			    exit(1);
			break;
			
			default:
				printf("Comando Invalido\n");
                getchar ();
                scanf("%*c");
                
		}
		
		
	}
    fila_print (fila);
    return 0;
}

void fila_insere (int valor, Node** fila)
{
    Node* novo = (Node*) malloc (sizeof(Node));
    if (novo==NULL) exit (ERRO);
    novo -> info = valor;
    novo -> prox = NULL;
    if (*fila == NULL)
        *fila = novo;
    else
    {
        //Node* ant = *fila;
        Node* aux = *fila;
        while (aux && aux -> prox)
        {
            aux = aux -> prox;
        }
        aux -> prox = novo;
    }
}

void fila_print (Node* fila)
{
    for (Node* aux = fila; aux != NULL; aux = aux -> prox)
        printf("%d\n", aux->info);
}

int lista_remove (int n, Node** inicio) //REMOVE TODAS AS OCORRENCIAS DE n NAS LISTAS
{
    if (!(*inicio)) return ERRO;
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
                //rem = NULL;
            }
            else
                ant = rem;
        }
    }
    return n;
}
