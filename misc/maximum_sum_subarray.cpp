#include <iostream>
#include <vector>
using namespace std;

int max_sum(vector<int>& vet){
   int max_atual = vet[0], max_global = vet[0];
   for(int i=1; i<vet.size(); i++){
      max_atual = max(vet[i], max_atual + vet[i]);
      max_global = max(max_global, max_atual);
   }
   return max_global;
}

int main() {
   vector<int> v {3, 2, 1, -2, 32, 21, 33, 0, 2, 232};
   cout << max_sum(v) << endl;
   return 0;
}
