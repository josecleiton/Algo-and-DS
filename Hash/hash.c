#include "hash.h"

#include <stdlib.h>
#include <string.h>

#include "alloc.h"

unsigned long hash(const char* in) {
   unsigned long hash = 5381;
   char* str = (char*)in;
   unsigned c;
   while ((c = *str++)) {
       /* hash * 33 + c */
      hash = ((hash << 5) + hash) + c;
   }
   return hash;
}

BucketHash* bucketInit(const int length) {
   BucketHash* h = (BucketHash*)alloc(1, sizeof(BucketHash));
   h->heads = (BucketList**)alloc(length, sizeof(BucketList*));
   h->length = length;
   return h;
}

int bucketPush(BucketHash* h, const char* key, const char* value) {
   int idx = hash(key) % h->length;
   return (h->size += bucketListPush(&h->heads[idx], key, value));
}

int bucketListPush(BucketList** l, const char* key, const char* value) {
   BucketList* list = *l;
   if (list) {
      if (!strcmp(list->key, key)) {
         const unsigned vcapacity = strlen(value) + 1;
         if (list->vcapacity < vcapacity) {
            list->vcapacity = vcapacity << 1;
            list->value = (char*)realloc(list->value, list->vcapacity);
            if (!list->value) {
               abortWithLog(1);
            }
         }
         strcpy(list->value, value);
         return 0;
      }
      return bucketListPush(&list->next, key, value);
   }
   list = *l = (BucketList*)alloc(1, sizeof(BucketList));
   list->key = (char*)alloc(strlen(key) + 1, sizeof(char));
   list->vcapacity = strlen(value) + 1;
   list->value = (char*)alloc(list->vcapacity, sizeof(char));
   strcpy(list->key, key);
   strcpy(list->value, value);
   return 1;
}

int bucketPop(BucketHash* h, const char* key) {
   int idx = hash(key) % h->length;
   int removed = 0;
   h->heads[idx] = bucketListPop(&h->heads[idx], key, &removed);
   return (h->size -= removed);
}

BucketList* bucketListPop(BucketList** l, const char* key, int* removed) {
   BucketList* list = *l;
   if (list) {
      if (!strcmp(list->key, key)) {
         /* achou */
         BucketList* nextPtr = list->next;
         bucketNodeListFree(list);
         *removed = 1;
         return nextPtr;
      } else {
         list->next = bucketListPop(&list->next, key, removed);
         return list;
      }
   }
   return NULL;
}

void bucketFree(BucketHash** h) {
   BucketHash* hash = *h;
   for (unsigned i = 0; i < hash->length; i++) {
      hash->heads[i] = bucketListFree(hash->heads[i]);
   }
   free(hash->heads);
   free(hash);
   *h = NULL;
}

BucketList* bucketListFree(BucketList* l) {
   if (l) {
      l->next = bucketListFree(l->next);
      bucketNodeListFree(l);
   }
   return NULL;
}

const char* bucketFind(BucketHash* h, const char* key) {
   int idx = hash(key) % h->length;
   return bucketListFind(h->heads[idx], key);
}

const char* bucketListFind(BucketList* list, const char* key) {
   if (list) {
      if (!strcmp(list->key, key)) {
         return list->value;
      }
      return bucketListFind(list->next, key);
   }
   return NULL;
}

void bucketNodeListFree(BucketList* l) {
   free(l->key);
   free(l->value);
   free(l);
}

/* int main() { */
/*    BucketHash* h= bucketInit(10); */
/*    bucketPush(h, "test", "treme"); */
/*    bucketPush(h, "italo", "treme"); */
/*    bucketPush(h, "italo sergio", "treme"); */
/*    bucketPush(h, "Rita", "burra"); */
/*    bucketPush(h, "milena", "burra"); */
/*    bucketPush(h, "milena", "inteligente"); */
/*    bucketPop(h, "Rita"); */
/*    bucketPop(h, "italo sergio"); */
/*    bucketPush(h, "test", "gotcha"); */
/*    bucketPop(h, "milena"); */
/*    const char* r = bucketFind(h, "milena"); */
/*    if(r) { */
/*       printf("milena = %s\n", r); */
/*    } else { */
/*       puts("milena não está no dat"); */
/*    } */
/*    bucketFree(&h); */
/* } */
