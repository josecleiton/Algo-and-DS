#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>
#include <numeric>
using namespace std;

template <class ValueType>
class TreeNode{
   public:
   TreeNode *left;
   TreeNode *right;
   ValueType key;
   TreeNode(ValueType input):
      key(input), left(nullptr), right(nullptr) {
   }
   TreeNode():
      left(nullptr),
      right(nullptr){}
};

template <class ValueType>
class BinarySearchTree{
private:
   TreeNode<ValueType> *root{}; //{} inicializa a variável com 0
   size_t count{};
public:

    ~BinarySearchTree(){
       Burn();
    }

   void Burn(){
       Clear(root);
       root = nullptr;
    }

    void Insert(TreeNode<ValueType> *&raiz, const ValueType& elementToInsert){
       if(raiz == nullptr){
          raiz = new TreeNode<ValueType>(elementToInsert);
          (this->count)++;
       }
       else if(elementToInsert < raiz->key) Insert(raiz->left, elementToInsert);
       else if(elementToInsert > raiz->key) Insert(raiz->right, elementToInsert);
       else cout << "Já está na árvore\n";
    }

    long long Height(TreeNode<ValueType> *&root){
       if(root == nullptr) return 0;
       return 1+max(Height(root->left), Height(root->right));
    }

    bool IsBalanced(TreeNode<ValueType> *&root){
       if(root == nullptr) return true;
       long long leftHeight = Height(root->left);
       long long rightHeight = Height(root->right);
       
       if ((abs(leftHeight-rightHeight)<=1) and isBalanced(root->left) and isBalanced(root->right))
          return true;
       else return false;
    }

    bool isMirror(TreeNode<ValueType> *&root1, TreeNode<ValueType> *&root2){
       if(root1 == nullptr and root2 == nullptr)
          return true;
       if(root1 != nullptr and root2 != nullptr)
          return isMirror(root1->left, root2->right) and isMirror(root1->right, root2->left);
       
       return false;
    }

    TreeNode<ValueType>* GetRootNode() const{
       return this->root;
    }

    /// Remove o elemento
    bool Remove(const ValueType& elementToRemove);

    /// Busca pelo elemento
    TreeNode<ValueType>*& Search(TreeNode<ValueType> *&root, const ValueType& elementToFind) const{
       if(root != nullptr){
          if(elementToFind < root->key) return Search(root->left, elementToFind);
          else if(elementToFind > root->key) return Search(root->right, elementToFind);
          else return root;
       }
       return root;
    }


    bool IsEmpty() const{
       return !(this->count);
    }

    /// Numero de nós
    size_t Count() const{
       return count;
    }

    void PreOrder(TreeNode<ValueType> *&root) const{
       if(root != nullptr){
          cout << root->key << endl;
          PreOrder(root->left);
          PreOrder(root->right);
       }
    }

    void InOrder(TreeNode<ValueType> *&root) const{
      if(root != nullptr){
         InOrder(root->left);
         cout << root->key << endl;
         InOrder(root->right);
      }
    }
    
    void PostOrder(TreeNode<ValueType> *&root) const{
       if(root != nullptr){
          PostOrder(root-left);
          PostOrder(root->right);
          cout << root->key << endl;
       }
    }

    void InLevel(TreeNode<ValueType> *root) const{
       queue<TreeNode<ValueType> *> q;
       for(q.push(root); q.size(); q.pop()){
          auto FrontQueueNode = q.front();
          if(FrontQueueNode->left != nullptr)
             q.push(FrontQueueNode->left);
          if(FrontQueueNode->right != nullptr)
             q.push(FrontQueueNode->right);
          cout << FrontQueueNode->key << endl;
       }
    }

    void Clear(TreeNode<ValueType> *&root) const{
       if(root != nullptr){
          Clear(root->left);
          Clear(root->right);
          delete root;
       }
    }

};
int main(){
   BinarySearchTree<int> b;
   auto k = b.GetRootNode();
   b.Insert(k, 4);
   b.Insert(k, 5);
   b.Insert(k, 1);

   cout << "Nós na árvore: "<< b.Count()<<'\n';
   cout << "Altura da árvore: " << b.Height(k) << '\n';
   //b.InOrder(k);
   b.InLevel(k);
   return 0;
}
