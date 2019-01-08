#ifndef _BST_HPP
#define _BST_HPP
#include <iostream>
#include <memory>
#include <queue>
#include <algorithm>
using namespace std;

namespace binary_tree{
    
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
      left(nullptr), right(nullptr){
   }
};

template <class ValueType>
class BinarySearchTree{
private:
   TreeNode<ValueType> *root{}; //{} inicializa a variável com 0
   size_t count{};
public:

    ~BinarySearchTree(){ //destructor
       Burn(); //queima a porra toda
    }

   void Burn(){
       Clear(root);
       this->root = nullptr;
    }

    void Insert(TreeNode<ValueType> *&raiz, const ValueType& elementToInsert){
       if(raiz == nullptr){
          raiz = new TreeNode<ValueType>(elementToInsert);
          if(this->count == 0)
            this->root = raiz;
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
       
       if ((abs(leftHeight-rightHeight)<=1) and IsBalanced(root->left) and IsBalanced(root->right))
          return true;
       else return false;
    }

    bool IsMirror(TreeNode<ValueType> *&root1, TreeNode<ValueType> *&root2){
       if(root1 == nullptr and root2 == nullptr)
          return true;
       if(root1 != nullptr and root2 != nullptr)
          return IsMirror(root1->left, root2->right) and IsMirror(root1->right, root2->left);
       
       return false;
    }

    TreeNode<ValueType>* GetRootNode() const{
       return this->root;
    }
    
    TreeNode<ValueType>* MinValue(TreeNode<ValueType> *&root){
        TreeNode<ValueType>* aux = root;
        while(aux->left != nullptr)
            aux = aux->left;
        return aux;
            
    }

    /// Remove o elemento
private:
    bool Remove(TreeNode<ValueType> *&NodeToRemove){
        if(NodeToRemove != nullptr){
            auto AuxNode = NodeToRemove;
            if(NodeToRemove->left == nullptr) NodeToRemove = NodeToRemove->right;
            else if(NodeToRemove->right == nullptr) NodeToRemove = NodeToRemove->left;
            else{
                auto AuxNode = MinValue(NodeToRemove->right);
                NodeToRemove->key = AuxNode->key;
                Remove(AuxNode);
                return true;
            }
            delete AuxNode;
            (this->count)--;
            AuxNode = nullptr;
            return true;
        }
        return false;
    }
    
public:
    TreeNode<ValueType>* FindAndRemove(TreeNode<ValueType> *&NodeToRemove,const ValueType& elementToRemove){
        if(NodeToRemove != nullptr){
                if(elementToRemove < NodeToRemove->key) NodeToRemove->left = FindAndRemove(NodeToRemove->left, elementToRemove);
                else if(elementToRemove > NodeToRemove->key) NodeToRemove->right = FindAndRemove(NodeToRemove->right, elementToRemove);
                else{
                    (this->count)--; //diminui um do numero de nós
                    if(NodeToRemove->left == nullptr){
                        auto AuxNode = NodeToRemove->right;
                        delete NodeToRemove;
                        return AuxNode;
                    }
                    else if(NodeToRemove->right == nullptr){
                        auto AuxNode = NodeToRemove->left;
                        delete NodeToRemove;
                        return AuxNode;
                    }

                    auto AuxNode = MinValue(NodeToRemove->right);
                    NodeToRemove->key = AuxNode->key;
                    NodeToRemove->right = FindAndRemove(NodeToRemove->right, AuxNode->key);
                }
        }
        return nullptr;
    }
        

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
       return this->count;
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

} // namespace binary_tree
#endif