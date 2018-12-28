#include <iostream>
#include <algorithm>
#include <ctime>
#include "partition_if.h"
using namespace std;

int main(){
    int vet[50];
    int tam = sizeof(vet)/sizeof(*vet);
    // PREENCHENDO VETOR COM NUMEROS ALEATORIOS
    srand(time(NULL));
    for(int i=0; i<tam; i++)
        vet[i] = rand()%500;
        
    //  PIVOT SERÁ 105
    vet[8] = vet[tam-1] = 105;
    cout << "PIVOT: " << vet[8] << endl;
    int index = partition_if(vet, vet+tam-1, vet+8, \
                    [](const int& a, const int& b){return a<=b;}) - vet;
    cout << "Pivot's index: " << index << endl;

    // MOSTRANDO O INTERVALO
    for(int i=0; i<tam; i++)
        cout << vet[i] << ' ';
    cout << endl;

    // TESTANDO SE ESTÁ PARTICIONADO
    //cout << is_partitioned(vet, vet+tam-1, [](const int& a){return a <= 105;});
    cout << "Is partitioned? " << is_partitioned_if(vet, vet+tam-1, vet+index, \
                                    [](const int& a, const int& b){return a<=b;});
    cout << endl;

    return 0;
}
