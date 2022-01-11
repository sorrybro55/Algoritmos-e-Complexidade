#include <stdlib.h>; 

typedef struct bst {
  int key, info; 
  struct bst *left, *right; 
} *BST; 

int update ( BST *a, int k, int i) {
  int u = 0; 
  
  while (*a != NULL && (*a)->key!=k)
    if ((*a)->key > k) a = &((*a)->left);
    else a = &((*a)->right); 
    
  if (*a == NULL) {
    *a = (BST) malloc (sizeof( struct bst)); 
    (*a)->key = k; 
    (*a)->info = i; 
    (*a)->left = (*a)->right = NULL; 
    u=1; 
  }
  else (*a)->info =i; 
  return u; 
}

int lookup (BST a, int k, int *i){
  int found = 1; 
  while (a != NULL && a->key != k) {
    if (a->key > k) a = a->left; 
    else a = a->right; 
  }
  if (a!=NULL) *i = a->info; 
  else found = 0; 
  return found; 
}

    
int main() {

  return 0;
}