#include "BinarySearchTree.hpp"
#include "Heap.hpp"
using namespace binary_tree;

void test_bst(void){
   BinarySearchTree<int> BST;
   auto k = BST.GetRootNode();
   BST.Insert(k, 4);
   BST.Insert(k, 5);
   BST.Insert(k, 3);
   BST.Insert(k, 2);
   BST.Insert(k, 1);
   BST.FindAndRemove(k, 4);
   cout << "\tBINARY SEARCH TREE!" << endl;
   cout << "Nós na árvore: " << BST.Count() << endl;
   cout << "Altura da árvore: " << BST.Height(k) << endl;
   cout << "Arvore Balanceada: ";
   if(BST.IsBalanced(k)) cout << "True\n";
   else cout << "False\n";
   //b.InOrder(k);
   BST.InLevel(k);
}

bool compare(const int& a, const int& b){ return a > b; }

void test_heap(){
   Heap<int> hp;
   int vet[] = {41, 39, 33, 18, 27, 12};
   const int vetTam = sizeof(vet)/sizeof(*vet);
   for(int i=0; i<vetTam; i++)
      hp.push(vet[i]);
   hp.push(55);
   cout << "\tBINARY MAX HEAP!" << endl;
   hp.print();
   hp.pop();
   cout << endl;
   cout << "Depois da remoção da raiz: " << endl;
   hp.print();
}

int main(){
   test_bst();
   scanf("%*c");
   test_heap();
   return 0;
}
