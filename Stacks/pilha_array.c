#include <stdlib.h>
#include <stdio.h>
#include "pilha_array.h"

struct pilha
{
    int topo;
    int dim;
    float* vet;
};

int main (void)
{
    float v = 12, z = 13;

    Pilha* p = pilha_cria ();
    pilha_push (p, v);
    pilha_push (p, z);
    pilha_push (p, -5789);
    pilha_push (p, 23547);
    pilha_push (p, 57);

    for (int i = p -> topo-1; i>=0; i--)
        printf("%0.2f\n", p -> vet[i]);

    pilha_libera (p);


    return 0;
}

Pilha* pilha_cria (void)
{
    Pilha* p = (Pilha*) malloc (sizeof(Pilha));
    p -> dim = 2;
    p -> vet = (float*) malloc (p -> dim * sizeof(float));
    p -> topo = 0;
    return p;
}

void pilha_push (Pilha* p, float v)
{
    if (p -> topo == p -> dim) //verifica se a pilha está com capacidade máxima
    {
        p -> dim *= 2;
        p -> vet = (float*) realloc (p -> vet, p->dim * sizeof(float)); //realoca o vetor
    }
    /* insere elemento na proxima posição livre */

    p -> vet[p -> topo++] = v;
}

float pilha_pop (Pilha* p)
{
    float v = p -> vet[--p -> topo];
    return v;
}

int pilha_vazia (Pilha* p)
{
    return (p -> topo == 0);
}

void pilha_libera (Pilha* p)
{
    free (p -> vet);
    free (p);
}