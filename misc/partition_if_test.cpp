#include <iostream>
#include <algorithm>
#include <ctime>
#include "partition_if.h"
using namespace std;

void randNumbers(void){
    cout << endl << "RAND INTEGERS TEST" << endl << endl;
    int vet[50];
    int tam = sizeof(vet)/sizeof(*vet);
    // PREENCHENDO VETOR COM NUMEROS ALEATORIOS
    srand(time(NULL));
    for(int i=0; i<tam; i++)
        vet[i] = rand()%500;
        
    //  PIVOT SERÁ 105
    vet[8] = vet[tam-1] = 105;
    cout << "PIVOT: " << vet[8] << endl;
    int index = partition_if(vet, vet+tam-1, vet+8, less_equal<int>()) - vet;
    cout << "Pivot index (after partition_if): " << index << endl;

    // MOSTRANDO O INTERVALO
    for(int i=0; i<tam; i++)
        cout << vet[i] << ' ';
    cout << endl;

    // TESTANDO SE ESTÁ PARTICIONADO
    //cout << is_partitioned(vet, vet+tam-1, [](const int& a){return a <= 105;});
    cout << "Is partitioned? " << is_partitioned_if(vet, vet+tam-1, vet+index, less_equal<int>());
    cout << endl;
}

void strings(void){
    cout << endl << "STRING TEST" << endl << endl;
    string vet[19] = {
        "vertebrado",
        "ave",
        "zebra",
        "mamifero",
        "carnivoro",
        "onivoro",
        "herbivoro",
        "invertebrado",
        "inseto",
        "anelideo",
        "hematofago",
        "pulga",
        "lagarta",
        "aguia",
        "pomba",
        "homem",
        "vaca",
        "sanguessuga",
        "minhoca",
    };
    // escolhendo "zebra" como pivot (2)
    int tam = sizeof(vet)/sizeof(*vet);
    cout << "PIVOT: " << vet[2] << endl;
    int index = partition_if(vet, vet+tam-1, vet+2, less_equal<string>()) - vet;
    cout << "Pivot index (after partition_if): " << index << endl;
    cout << endl << "Range: " << endl;
    for(int i=0; i<tam; i++)
        cout << vet[i] << endl; 
    cout << endl << "Is partitioned? ";
    cout << is_partitioned_if(vet, vet+tam-1, vet+2, less_equal<string>()) << endl;
}

int main(){
    randNumbers();
    strings();
    return 0;
}
