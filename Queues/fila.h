typedef struct fila Fila;
typedef struct node Node;

Fila* fila_cria (void);
void fila_insere (Fila* f, float x);
float fila_retira (Fila* f);
int fila_vazia (Fila*f );
void fila_libera (Fila* f);
void fila_imprime (Fila* f);