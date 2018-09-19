#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct node
{
    float info;
    Node* prox;
};

struct fila // ESTRUTURA FIXA
{
    Node* ini; 
    Node* fim;
};

int main (void)
{
    Fila* fila = fila_cria ();
    float num;
    char op;
    printf("BEM-VINDO A PILHA\n");
    system ("read -rsp $'Press enter to continue...\n'");
	for(;;)
    {
        system ("clear");
		printf("\nMenu:\n i= Inserir\n r= Retirar\n a= apagar a fila\n m= mostrar fila\n q = quantifica elementos da fila (em construção)\n e= sair\n\nopção = ");
        scanf(" %c", &op);
		switch(op)
        {
			case 'i':
				printf("Qual numero sera inserido?: ");
				scanf("%f", &num);
				fila_insere (fila, num);
				break;
			
			case 'r':
				printf("Elemento %f retirado!\n", fila_retira (fila));
                system ("read -rsp $'Press enter to continue...\n'");
				break;

			case 'a':
			    fila_libera (fila);
			break;
			
			case 'm':
			    fila_imprime (fila);
                system ("read -rsp $'Press enter to continue...\n'");
			break;

            //case 'q':
            //    printf("Na pilha há: %d elementos\n", pilha_elementos(topo));
             //   system ("read -rsp $'Press enter to continue...\n'");
             //   break;

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


Fila* fila_cria (void)
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f -> ini = f -> fim = NULL;
    return f;
}

int fila_vazia (Fila* f)
{
    return f -> ini == NULL;
}

void fila_insere (Fila* f, float x)
{
    Node* q = (Node*) malloc(sizeof(Node));
    q -> info = x;
    q -> prox = NULL; //NUNCA ESQUEÇA DE LIMPAR O PONTEIRO
    if (fila_vazia(f))
        f -> ini = q; //SE A FILA ESTIVER VAZIA, O q É O PRIMEIRO ELEMENTO 
    else
        f -> fim -> prox = q; //SE A FILA NÃO ESTIVER VAZIA, ENCADEIE A LISTA
    f -> fim = q;
}

float fila_retira (Fila* f)
{
    if (fila_vazia (f))
    {
        printf("FILA VAZIA!\nTerminando o programa...\n");
        exit(-(42*42*42*42*42));
    }
    Node* aux = f -> ini; //UM AUX É NECESSÁRIO, PORQUE SE FIZESSEMOS USANDO F, PERDERÍAMOS TODA A FILA OU TERÍAMOS QUE DEIXAR LIXO NO HEEP
    float n = aux -> info;
    f -> ini = aux -> prox;
    if (f -> ini == NULL) /*ATUALIZA O FIM SE A FILA ESTIVER VAZIA */
        f -> fim = NULL;
    free (aux);
    return n;
}

void fila_libera (Fila* f)
{
    if (fila_vazia(f))
    {
        printf("FILA VAZIA!\nTerminando o programa...\n");
        exit(42*42);
    }
    Node* aux;
    while(aux != NULL)
    {
        Node* temp = aux -> prox;
        free (aux);
        aux = temp;
    }
    free (f);
}

void fila_imprime (Fila* f)
{
    if (fila_vazia(f))
    {
        printf("FILA VAZIA!\nTerminando o programa...\n");
        exit(42);
    }
    for (Node* temp = f -> ini; temp != NULL; temp = temp -> prox)
        printf("%f\n", temp -> info);
}