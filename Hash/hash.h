typedef struct bucket_list {
   struct bucket_list* next;
   unsigned length;
   char *key, *value;
   unsigned vcapacity;  // value capacity
} BucketList;

typedef struct bucket_hash {
   BucketList** heads;
   unsigned length; // total de buckets alocados
   unsigned size; // total de nós em todos os buckets
} BucketHash;

/*
 * DJB2 hash function
 */
unsigned long hash(const char* in);

/*
 * Inicializa ponteiros para k = length
 */
BucketHash* bucketInit(const int length);

/*
 * Insere par de chave valor
 */
int bucketPush(BucketHash* h, const char* key, const char* value);

/*
 * Remove chave
 */
int bucketPop(BucketHash* h, const char* key);

/*
 * Busca chave
 */
const char* bucketFind(BucketHash* h, const char* key);

/*
 * Libera memória de toda a estrutura de dados
 * Para evitar memory leak,
 * deve ser chamada no fim da utilização
 */
void bucketFree(BucketHash**);

/*
 * Abaixo há funções auxiliares para
 * manipular as listas (buckets),
 * assim como seus nós
 */

int bucketListPush(BucketList** list, const char* key, const char* value);

BucketList* bucketListPop(BucketList** list, const char* key, int* removed);

BucketList* bucketListFree(BucketList* list);

const char* bucketListFind(BucketList* list, const char* key);

void bucketNodeListFree(BucketList*);

