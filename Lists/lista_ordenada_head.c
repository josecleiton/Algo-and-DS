/*
	ALGORITMO DE LISTA AUTO-ORGANIZADA COM CABEÇA
	LEMBRE-SE DE TROCAR TODOOS OS "SYSTEM", SE VOCÊ UTILIZAR WINDOWS
	FEITO POR JOSÉ CLEITON BORGES CORREIA
	UNEB - ED1 2018.1
*/
#include <stdio.h>
#include <stdlib.h>
#include "lista_ordenada_head.h" //CABEÇALHO DAS FUNÇÕES E TYPEDEF
#define ERRO 314152

struct node
{
	int info;
	Node* prox;
};

struct lista
{
	Node* ini;
	Node* fim;
};

int main (void)
{
	Lista* t = ord_cria ();
	Lista* inv;
	int num;
    char op;
    printf("BEM-VINDO A LISTA AUTO-ORGANIZADA\n");
    system ("read -rsp $'Press enter to continue...\n'");
	for(;;)
    {
        system ("clear");
		printf("\nMenu:\n i= Inserir\n r= Retirar\n a= apagar a lista ordenada\n m= mostrar lista ordenada\n q= quantifica elementos da lista ordenada\n p= verifica se elemento pertence a lista\n d= inverte a lista ordenada\n 2= remove pares da lista ordenada\n e= termina o programa\n\nopção = ");
        scanf(" %c", &op);
		switch(op)
        {
			case 'i':
				printf("Qual numero sera inserido?: ");
				scanf("%d", &num);
				ord_insere (num, t);
				break;
			
			case 'r':
				printf("Qual numero sera retirado?: ");
				scanf("%d", &num);
				printf("Elemento(s) %d retirado(s)!\n", ord_remove (num, t));
                system ("read -rsp $'Press enter to continue...\n'");
				break;

			case 'a':
			    ord_libera (t);
			break;
			
			case 'm':
			    ord_print (t);
                system ("read -rsp $'Press enter to continue...\n'");
			break;
			case 'q':
				printf("Há %d elementos na lista!\n", ord_conta (t));
				system ("read -rsp $'Press enter to continue...\n'");
				break;
			case 'p':
				printf("Digite um numero para ser verificado: ");
				scanf("%d", &num);
				if (ord_pertence(num, t))
					printf("Elemento está na lista!\n");
				else
					printf("Elemento não está na lista!\n");
				system ("read -rsp $'Press enter to continue...\n'");
			break;
			case 'd':
				inv = ord_inverte_stack (t);
				printf("A lista em ordem decrescente:\n");
				ord_print (inv);
				ord_libera (inv);
				system ("read -rsp $'Press enter to continue...\n'");
			break;
			case '2':
				inv = ord_remove_pares (t);
				printf("Todos os pares removidos da lista: \n");
				ord_print (inv);
				system ("read -rsp $'Press enter to continue...\n'");
				break;
			case 'e':
				printf("\nTerminando o programa...\n");
				exit (1);
			
			default:
				printf("Comando Invalido\n");
                system ("read -rsp $'Press enter to continue...\n'");
		}
	}
	return 0;
}

Lista* ord_cria (void)
{
	Lista* ord = (Lista*) malloc (sizeof(Lista));
	if (!ord) exit (ERRO); //SE O PONTEIRO NÃO FOI ALOCADO, NÃO HÁ O QUE FAZER.
	ord -> ini = NULL; // IMPORTANTISSIMO PARA EVITAR PROBLEMAS COM QUALQUER ESTRUTURA DE DADOS DINAMICA
	return ord;
}

int ord_insere (int n, Lista* ord)
{
	Node* no = (Node*) malloc (sizeof(Node)); //ALOCAÇÃO DA ESTRUTURA
	if (!no) exit (ERRO); //SE O PONTEIRO NÃO FOI ALOCADO, NÃO HÁ O QUE FAZER.
	no -> info = n; //ATRIBUIÇÃO DO n AO CAMPO info DA ESTRUTURA ALOCADA
	Node* aux; //DECLARAÇÃO DE UM PONTEIRO PARA NÃO PERDERMOS O INICIO DA LISTA ENCADEADA
	if (ord_vazia(ord) || n < ord -> ini -> info) //SE A LISTA ESTÁ VAZIA OU O ELEMENTO INSERIDO É MENOR QUE O INICIO DA LISTA ORDENADA CRESCENTE
	{
		aux = ord -> ini;
		ord -> ini = no;
	}
	else
	{
		Node* ant = ord -> ini;
		aux = ant -> prox;
		while (aux && n > aux -> info) //ENQUANTO O AUX FOR DIFERENTE DE NULO E SEU CONTEUDO FOR MENOR QUE O NUMERO INSERIDO PELO INDIVIDUO DESPROVIDO DE SABEDORIA, AVANCE TANTO ANT QUANTO AUX
		{
			ant = ant -> prox;
			aux = aux -> prox;
		}
		ant -> prox = no;
	}
	no -> prox = aux;
	return 1; //RETORNA VERDADEIRO SE A INSERÇÃO OCORREU
}

int ord_vazia (Lista* ord)
{
	if (!(ord -> ini)) //SE ELA ESTIVER VAZIA, RETORNE O VALOR 1 (VERDADEIRO)
		return 1;	
	else
		return 0; //SENÃO ESTIVER VAZIA, RETORNE O VALOR 0 (FALSO)
}

int ord_remove_um (int n, Lista* ord) //FUNÇÃO PARA A REMOÇÃO DE APENAS UMA OCORRENCIA DE n NA LISTA
{
	if (ord_vazia (ord))
		return (ERRO+ERRO)%ERRO;
	else if (!ord_pertence (n, ord))
	{
		printf("ELEMENTO NÃO ENCONTRADO NA LISTA!\n");
		return (ERRO+5);
	}
	Node* aux;
	//COMO EU REMOVO?
	//TENHO QUE VERIFICAR SE O N TA NO INICIO, NO MEIO OU NO FIM
	if (n == ord -> ini -> info) //SE O ELEMENTO ESTÁ NO INICIO
	{
		aux = ord -> ini;
		ord -> ini = aux -> prox;
	}
	else //SENÃO ELE ESTÁ NO MEIO OU NO FIM
	{
		Node* ant = ord -> ini;
		aux = ant -> prox;
		while (aux && n > aux -> info) //ENQUANTO AUXILIAR FOR DIFERENTE DE NULO
		{
			ant = ant -> prox; //AVANCE ANTERIOR
			aux = aux -> prox; //AVANCE AUXILIAR
		}
		ant -> prox = aux -> prox; //LIGUE O ANTERIOR AO PROX DE AUXILIAR 
	}

	free (aux); //LIBERE O ELEMENTO DESEJADO
	return n;
}

int ord_remove (int n, Lista* ord) //FUNÇÃO PARA A REMOÇÃO DA OCORRENCIA DE TODOS OS n NA LISTA
{
	if (ord_vazia (ord))
		return (ERRO+ERRO)%ERRO;
	else if (!ord_pertence (n, ord))
	{
		printf("ELEMENTO NÃO ENCONTRADO NA LISTA!\n");
		return (ERRO+5);
	}
	Node *aux, *rem, *ant; // PRECISA-SE DE 3 PONTEIROS, SENÃO PERDERIAMOS A LISTA
	aux = ord -> ini;
	ant = NULL;
	while (aux)
	{
		rem = aux;
		aux = aux -> prox;
		if (n == ord -> ini -> info) //SE O n ESTÁ NO INÍCIO DA LISTA
		{
			ord -> ini = aux;
			free (rem);
		}
		else //SE n ESTÁ NO MEIO OU NO FIM DA LISTA
		{
			if (rem && n == rem -> info) //SE REM FOR DIFERENTE DE NULO E O n FOR IGUAL AO ELEMENTO DE REM, REMOVA-O 
			{
				ant -> prox = aux;
				free (rem);
				rem = NULL;
			}
			else
				ant = rem;
		}
	}
	return n;
}

Lista* ord_remove_pares (Lista* ord) //FUNÇÃO QUE REMOVE OS PARES DA LISTA ORDENADA E RETORNA UM PONTEIRO PARA PILHA DESSES PARES REMOVIDOS
{
	if (ord_vazia (ord))
	{
		printf("LISTA VAZIA!\nIMPOSSÍVEL REMOÇÃO DE PARES!\n");
		return NULL;
	}
	Node *ant, *aux, *rem;
	Lista* pares = ord_cria ();
	ant = NULL;
	aux = ord -> ini;
	while (aux)
	{
		rem = aux;
		aux = aux -> prox;
		if (!(rem -> info % 2))
		{
			if (rem == ord -> ini) //VERIFICANDO SE O ELEMENTO PAR ESTÁ NO INICIO
				ord -> ini = aux;
			else
				ant -> prox = aux;
			stack_push (rem->info, pares);
			free (rem);
		}
		else
			ant = rem;	
	}
	return pares;
}

int ord_pertence (int n, Lista* ord)
{
	Node* aux = ord -> ini;
	while (aux)
	{
		if (aux -> info == n) //SE O ELEMENTO DA LISTA FOR IGUAL AO ELEMENTO INSERIDO (n), RETORNE VERDADEIRO PARA A FUNÇÃO PERTENCE
			return 1;
		aux = aux -> prox; //AVANCE POR TODA A LISTA, ATÉ QUE ENCONTRE O ULTIMO ELEMENTO (aux == NULL)
	}
	return 0; //RETORNE FALSO PARA A FUNÇÃO "PERTENCE A LISTA", PORQUE APÓS VERIFICARMOS TODA ELA (COM O WHILE), NÃO ACHAMOS O ELEMENTO NA MESMA
}

int ord_libera (Lista* ord)
{
	Node* aux = ord -> ini;
	int op = 0;
	while (aux)
	{
		Node* temp = aux -> prox;
		free (aux);
		aux = temp;
		op = 1;
	}
	free (ord);
	ord -> ini = NULL;
	return op;
}

void ord_print (Lista* ord)
{
	if (ord_vazia(ord))
	{
		printf("LISTA VAZIA!\nIMPRESSÃO IMPOSSÍVEL!\n");
		return;
	}
	
	for (Node* aux = ord -> ini; aux != NULL; aux = aux -> prox)
		printf("%d\n", aux -> info);
	return;
}

int ord_conta (Lista* ord)
{
	if (ord_vazia(ord))
		return 0;
	int n = 0;
	for (Node* aux = ord -> ini; aux != NULL; aux = aux -> prox)
		n++;
	return n;
}

/*
 * FUNÇÕES PARA INVERTER A LISTA ORDENADA
*/
Lista* ord_inverte_queue (Lista* ord) //ESSA FUNÇÃO E A USA A FILA PARA A INVERSÃO (NÃO EFICIENTE)
{
	Lista* i = ord_cria();
	int n = ord_inverte_queue_retira (ord);
	while (n != ERRO)
	{
		Node* aux = (Node*) malloc (sizeof(Node));
		aux -> info = n;
		aux -> prox = NULL;
		if (ord_vazia(i))
			i -> ini = aux;
		else
			i -> fim -> prox = aux;
		i -> fim = aux;
		n = ord_inverte_queue_retira (ord);
	}
	return i;
}

int ord_inverte_queue_retira (Lista* ord)  //ESSA FUNÇÃO E A USA A FILA PARA A INVERSÃO (NÃO EFICIENTE)
{
	if (ord_vazia (ord))
	{
		free (ord);
		return ERRO;
	}
	Node* ant = ord -> ini;
	Node* aux = ant -> prox;
	Node* temp = NULL;
	int n;
	if (aux)
	{
		temp = aux -> prox;
		while (temp)
		{
			ant = ant -> prox;
			aux = aux -> prox;
			temp = temp -> prox;
		}
		n = aux -> info;
		ant -> prox = aux -> prox;
		free (aux);
	}
	else
	{
		n = ant -> info;
		free (ant);
		ord -> ini = NULL;
	}
	return n;
}

Lista* ord_inverte_stack (Lista* ord) //ESSA USA A PILHA PARA A INVERSÃO (MAIS EFICIENTE)
{
	Lista* stack = ord_cria();
	Node* aux = ord -> ini;
	while (aux)
	{
		stack_push (aux -> info, stack);
		aux = aux -> prox;
	}
	return stack;
}

void stack_push (int n, Lista* s)
{
	Node* no = (Node*) malloc (sizeof(Node));
	if (!no) exit (ERRO);
	no -> info = n;
	no -> prox = s -> ini;
	s -> ini = no;
}