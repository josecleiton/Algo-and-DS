/*
* UMA POSSIVEL ADIÇÃO A BIBLIOTECA ALGORITHM
* PARTITION IF PARTICIONA UM INTERVALO:
*       SE A FUNÇÃO COMP FOR <= ENTÃO
*       PIVOT ESTARÁ NUMA POSIÇÃO ONDE
*           -TODOS A SUA ESQUERDA SÃO MENORES OU IGUAIS PIVOT
*           -TODOS A SUA DIREITA SÃO MAIORES QUE PIVOT
*       NÃO É ESTÁVEL, OU SEJA, NÃO GARANTE QUE:
*       OS INTERVALOS A DIREITA E A ESQUERDA ESTÃO ORDENADOS
* RETORNA: UM ITERATOR PARA O PIVOR
* BY: JOSÉ CLEITON CORREIA (SI - UNEB)
*/

#ifndef _PARTITION_IF_H
#define _PARTITION_IF_H
#include <bits/stl_algobase.h>

template<typename _ForwardIterator, typename _Compare>
_ForwardIterator partition_if(_ForwardIterator __first, _ForwardIterator __last, _ForwardIterator __pivot, _Compare __comp)
{
    if(__first == __last)
        return __first;
    std::iter_swap(__first, __pivot);
    __pivot = __first;
    _ForwardIterator __next = ++__first;
    while(true)
    {
        if(__comp(*__next, *__pivot)){
            if(__first != __next)
                std::iter_swap(__first, __next);
            ++__first;
        }
        if(__next == __last) break;        
        ++__next;
    }
    std::iter_swap(__pivot, --__first);
    return __first;
}

template<typename _ForwardIterator, typename _Compare>
bool is_partitioned_if(_ForwardIterator __first, _ForwardIterator __last, _ForwardIterator __pivot, _Compare __comp)
{
    while(__comp(*__first, *__pivot))
    {
        if(__first == __last)
            return true;
        __first++;
    }
    while(!__comp(*__first, *__pivot))
    {
        if(__first == __last)
            return true;
        __first++;
    }
    return false;
}

#endif //_PARTITION_IF_H
