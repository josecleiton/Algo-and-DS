#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#define MAX 1000000000
using namespace std;

/*
   COMPARAÇÃO ENTRE:
      O NTH_ELEMENT O(N) STL ALGORITHM PARA ACHAR A MEDIANA
      METODO SORT O(NLOGN) STL ALGORITHM E PEGAR O ELEMENTO DO MEIO 
*/

int main(){ 
   vector<int> vet(MAX);
   srand(time(NULL));
   for(int i=0; i<MAX; i++) vet[i] = rand();
   float timeA, timeB;
   clock_t clk = clock();
   nth_element(vet.begin(), vet.begin()+MAX/2, vet.end());
   clk = clock()-clk;
   timeA = ((float)clk)/CLOCKS_PER_SEC;
   printf("MEDIAN: %d\nFirst method took %f seconds to run.\n", vet[MAX/2],timeA);

   clk = clock();
   sort(vet.begin(), vet.end());
   clk = clock()-clk;
   timeB = ((float)clk)/CLOCKS_PER_SEC;
   printf("MEDIAN: %d\nSecond method took %f seconds to run.\n", vet[MAX/2], timeB);
   if(timeA < timeB)
      puts("First method is faster.");
   else if(timeA > timeB)
      puts("Second method is faster.");
   else
      puts("Same run time.");
   return 0;
}
