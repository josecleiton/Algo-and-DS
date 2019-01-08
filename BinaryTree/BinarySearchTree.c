#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <memory.h>
#include <errno.h>

typedef struct node {
   int info;
   struct node* left;
   struct node* right;
} Node;

void* alloc(const size_t count, const size_t blockSize){
    void* ptr = calloc(count, blockSize);
    if(! ptr){
      fprintf(stderr, "%s\n", strerror(errno));
      abort();
    }
    return ptr;
}

Node* inserir(Node* root, int info){
   if(!root){
      root = (Node*) alloc(1, sizeof(Node));
      root->info = info;
      return root;
   }
   if(info > root->info) root->right = inserir(root->right, info);
   else if(info < root->info) root->left = inserir(root->left, info);
   else puts("Valor repetido");
}

void print(Node* root){
   if(root){
      print(root->left);
      printf("%d ", root->info);
      print(root->right);
   }
}

bool max(int a, int b){
   return (a>=b)?1:0;
}

int height(Node* root){
   if(!root) return 0;
   return 1 + max(height(root->left), height(root->right));
}

bool isBalanced(Node* root){
   if(!root)
      return 1;
   int lh = height(root->left); 
   int rh = height(root->right);
   
   if(abs(lh-rh) <= 1 && isBalanced(root->left) && isBalanced(root->right))
      return true;

   return false;
}
 
bool isMirror(Node* root1, Node* root2){
   if(root1 == NULL && root2 == NULL)
      return true;
   if(root1 && root2)
      return isMirror(root1->left, root2->right) && isMirror(root1->right, root2->left);

   return false;
}

bool isSymmetric(Node* root){
   return isMirror(root, root);
}

Node* minValueNode(Node* root){
   Node* aux = root;
   while(aux->left)
      aux = aux->left;
   return aux;
}

Node* deleteNode(Node* root, int info){
   if(!root) return NULL;

   if(info < root->info) root->left = deleteNode(root->left, info);
   else if(info > root->info) root->right = deleteNode(root->right, info);
   else{
      if(!(root->left)){
         Node* aux = root->right;
         free(root); 
         return aux;
      }
      else if(!(root->right)){
         Node* aux = root->left;
         free(root);
         return aux;
      }

      Node* temp = minValueNode(root->right);
      root->info = temp->info;
      root->right = deleteNode(root->right, temp->info);
   }

   return root;
}

int isBSTUtil(Node* root, int min, int max){
   if(!root) return 1;

   if(root->info < min || root->info > max) return 0;

   return isBSTUtil(root->left, min, root->info-1) && isBSTUtil(root->right, root->info+1, max);
}

int isBST(Node* root){
   return isBSTUtil(root, INT_MIN, INT_MAX);
}

int treeDistance (Node* root, int info)
{
    if (!root) return -1;
    int distance = -1;
    if (root->info == info || (distance = treeDistance(root->left, info)) >=0 || (distance = treeDistance(root->right, info) >= 0))
        return distance + 1;
    return distance;
}


int main(){
   Node* raiz = NULL;
   int input[] = {32, 33, 34, 5, 35, 2, -1, 321};
   int inputSize = sizeof(input)/sizeof(*input);
   printf("Entrada: ");
   for(int i=0; i < inputSize; i++){
      raiz = inserir(raiz, input[i]);
      printf("%d ", input[i]);
   }
   putchar('\n');
   
   printf("BST: ");
   print(raiz);
   putchar('\n');
   printf("Altura = %d\n", height(raiz));

   puts("\nCaracteristicas da BST: ");
   if(isBalanced(raiz))
      puts("Arvore balanceada!");
   else puts("Não balanceada!");
   //deleteNode(raiz, 321);
   if(isSymmetric(raiz))
      puts("Arvore simétrica!");
   else puts("Não simétrica!");
   return 0;
}
