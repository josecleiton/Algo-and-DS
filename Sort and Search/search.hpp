#ifndef _SEARCH_H
#define _SEARCH_H

#include <iostream>
#include <vector>

using namespace std;
template <class ValueType>
/*
    AS FUNÇÕES PARTEM DO PRESSUPOSTO QUE
    OS OPERADORES <, > E == JÁ FORAM IMPLEMENTADOS
    PARA O VALUETYPE EM QUESTÃO
*/
class searching{
public:
    typedef intmax_t (searching<ValueType>::*searchFunc_t)(vector<ValueType>, ValueType);

    intmax_t binary(vector<ValueType> vet, ValueType K){ // RETORNA O INDICE
        size_t left = 0, right = vet.size()-1, middle;
        while(left <= right){
            middle = (left+right)/2;
            if(K < vet[middle])
                right = middle-1;
            else if(K > vet[middle])
                left = middle+1;
            else
                return middle;
        }
        return -1;
    }

    intmax_t linear(vector<ValueType> vet, ValueType K){
        size_t index = 0;
        while(index < vet.size())
            if(vet[index++] == K)
                return --index;
        return -1;
    }

    void compare(searchFunc_t A, searchFunc_t B, vector<ValueType> vet, ValueType K){
        intmax_t result;
        float timeA, timeB;
        clock_t clk = clock();
        result = (this->*A)(vet, K);
        clk = clock()-clk;
        timeA = ((float)clk)/CLOCKS_PER_SEC;
        printf("First method took %f seconds to run.\n", timeA);

        clk = clock();
        result = (this->*B)(vet, K);
        clk = clock()-clk;
        timeB = ((float)clk)/CLOCKS_PER_SEC;
        printf("Second method took %f seconds to run.\n", timeB);
    }
};

#endif