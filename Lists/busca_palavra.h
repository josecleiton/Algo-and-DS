typedef struct node Node;

Node* lista_cria (void);
int lista_insere (char w[], Node** inicio);
int le_arquivo (FILE* palavras, Node** inicio);
//int lista_remove_um (char w[], Node** inicio);
int lista_remove (char w[], Node** inicio); //REMOVE TODAS AS OCORRENCIAS DE n NAS LISTAS
int lista_vazia (Node* inicio);
int lista_libera (Node** inicio);
Node* lista_remove_pares (Node** inicio);
void lista_print (Node* inicio);
void lista_conta (Node* inicio);
int lista_pertence (char w[], Node* inicio);
char *copyString (char *str);
Node* lista_inverte (Node** inicio);
void stack_push (char w[], Node* s);
