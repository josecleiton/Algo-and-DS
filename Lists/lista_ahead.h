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
//char *copyString (char *str);
//int le_arquivo (FILE* palavras, Node** inicio);