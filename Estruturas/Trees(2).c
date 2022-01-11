#include <stdlib.h>; 

#define LEFT 1 
#define BAL 0
#define RIGHT -1

typedef struct avl {
  int bal; 
  int key, info; 
  struct avl *left, *right;
} *AVLTree; 

int updateAVL (AVLTree *a, int k, int i) {
  int g, u; 
  
  *a = updateAVLRec (*a, k, i, &g, &u); 
  return u; 
}

AVLTree rotateRight (AVLTree a) {
  AVLTree b = a->left; 
  a->left = b->right; 
  b->right = a; 
  return b; 
}

AVLTree rotateLeft (AVLTree b) {
  AVLTree a = b->right; 
  b->right = a->left; 
  a->left = b; 
  return a; 
}

AVLTree fixRight (AVLTree a) {
  AVLTree b, c; 
  b= a->right; 
  
  if(b->bal == RIGHT) {
    a->bal = b->bal=BAL;
    a = rotateLeft(a);
  }
  else{
    c = c->left; 
    switch(c->bal){ 
      case LEFT: a->bal = BAL;
                 b->bal = RIGHT; 
                 break; 
      
      case RIGHT: a->bal = LEFT; 
                  b->bal = BAL; 
                  break; 
      
      case BAL: a->bal = b->bal = BAL; 
    }
    c->bal = BAL; 
    a->right = rotateRight(b); 
    a = rotateLeft(a); 
  }
  return a; 
}


AVLTree fixLeft (AVLTree a) {
  AVLTree b, c; 
  b = a->left; 
  
  if(b->bal == LEFT){
    a->bal = b->bal = BAL; 
    a = rotateRight(a);
  }
  else {
    c = b->right; 
    switch (c->bal) {
      case LEFT: a->bal = RIGHT; 
                 b->bal = BAL;
                 break; 
      
      case RIGHT : a->bal = BAL; 
                   b->bal = LEFT; 
                   break; 
      
      case BAL: a->bal= b->bal = BAL; 
    }
    c->bal =BAL; 
    a->left = rotateRight(b); 
    a = rotateRight(a); 
  }
  return a; 
}

AVLTree updateAVRec (AVLTree a, int k , int i, int *g, int *u){
  if (a == NULL){
    a = malloc (sizeof(struct avl)); 
    a->key = k; 
    a->info = i; 
    a->bal = BAL; 
    a->left = NULL; 
    a->right = NULL; 
    *g= 0; 
    *u= 1;
  }
  else if (a->key == k) {
    a->info = i; 
    *g=0; 
    *u=1; 
  }
  else if (a->key > k) {
    a->left = updateAVLRec (a->left, k ,i, g, u); 
    if (*g==1) 
      switch (a->bal){
        case LEFT: a=fixLeft(a);
                   *g=0; 
                   break; 
        
        case BAL: a->bal = LEFT;
                    break; 
        
        case RIGHT: a->bal= BAL; 
                    *g=0; 
                    break; 
      }
  }
    
    else {
      a->right = updateAVLRec (a->right, k, i , g, u); 
      if (*g==1)
        switch (a->bal) {
          case RIGHT: a=fixRight(a); 
                      *g=0; 
                      break; 
          
          case BAL: a->bal = RIGHT; 
                    break; 
          
          case LEFT: a->bal = BAL; 
                      *g=0; 
                      break;
        }
    }
    return a; 
  }

    
int main() {

  return 0;
}