#include <stdlib.h>; 
#include <stdio.h>;
#include <string.h>; 

#define Max 100 

typedef struct pQueue {
  int valores [Max]; 
  int tamanho;
} PriorityQueue; 

void empty (PriorityQueue *q){
  q->tamanho = 0;
}

int isEmpty (PriorityQueue *q){
  return (q->tamanho == 0);
}

int add (int x, PriorityQueue *q){
  int r = 0; 
  if(q->tamanho == Max) r = 1; 
  else {
    q->valores[q->tamanho] = x; 
    bubbleUp(q->tamanho, q->valores); 
    q->tamanho++;
  }
  return r; 
}

int remove (PriorityQueue *q, int *rem){ 
  if(q->tamanho == 0) return -1; 
  else { 
    *rem = q->valores[0]; 
    q->valores[0] = q->valores[q->tamanho-1];
    q->tamanho--; 
    bubbleDown(0, q->valores, q->tamanho);
  }
  return 0; 
}

void heapify ( int v[], int N){
  int i; 
  for (i=1; i<N; i++) bubbleUp(i, v); 
}

void heapify2 (int v[], int N){
  int i; 
  for (i = (N-1)/2; i>= 0; i--) bubbleDown ( i, v, N);
}

void ordenaHeap(int h[], int N) {
  for (int i = 1; i < N; i++) {
    swap(h, 0, N-i);
    bubbleDown(i, h, N-i);
  }
}

/// 2.1 ////////////////////////////////////////////////////////////

#define Size 10 
/*
typedef struct nodo {
  char *chave;
  int ocorr; 
  struct nodo *prox; 
}Nodo, *THash [Size]; 

unsigned hash(char *str){
  unsigned hash = 5381;
  int c;
  
  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
/*  
  return hash % Size; // alterado aqui por conveniência
}

void initEmpty (THash t){
  int i; 
  for(i=0; i<Size; i++) t[i] = NULL;
}

void add (char *s, THash t) {
 unsigned h = hash(s); 
 Nodo *ptr;
 Nodo *ant = NULL;  
 
 for(ptr = t[h]; ptr != NULL; ptr = ptr->prox) {
   if ( !strcmp( ptr->chave, s) ) {
     ptr->ocorr++; 
     return; 
   }
   
   ant = ptr; 
 }
 
 ptr = calloc(1, sizeof(struct nodo)); 
 strcpy(ptr->chave, s); 
 ptr->ocorr = 1; 
 ptr->prox = NULL; 
 
 if(ant != NULL) ant->prox = ptr; 
 else t[h] = ptr; 
}

int lookup (char *s, THash t) {
  unsigned h = hash(s); 
  Nodo *ptr; 
  
  for(ptr = t[h]; ptr != NULL; ptr = ptr->prox)
    if (!strcmp(ptr->chave, s)) return ptr->ocorr;
  
  return 0; 
}

int remove (char *s, THash t) {
  unsigned h = hash(s); 
  Nodo *ptr, *ant = NULL; 
  
  for(ptr = t[h]; !strcmp(ptr->chave, s); ptr = ptr->prox){
    if (ptr != NULL) return -1;
    ant = ptr->prox; 
  }
  
  ptr->ocorr--; 
  
  if (ptr->ocorr == 0) {
    if (ant != NULL) ant->prox = ptr->prox;
    
    else t[h] = ptr->prox;
    
    free(ptr); 
  }
  
  return 0; 
}
*/
///// 2.2 ///////////////////////////////////////////////////////////////////////

#include <stdlib.h>; 
#include <stdio.h>;
#include <string.h>; 

unsigned hash(char *str){
  unsigned hash = 5381;
  int c;
  
  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  
  return hash % Size; // alterado aqui por conveniência
}

#define Size 10
#define Free 0
#define Used 1 
#define DEL  2

typedef struct bucket{
  int status; 
  char *chave; 
  int ocurr; 
} THash [Size];


int where (char *s, THash t) {
  int c, hash = 5381;

  while (c = *s++)
    hash *= 33 + c;

  return hash % Size;
}

void initEmpty (THash t){
  int i; 
  
  for (i=0; i < Size; i++){
    t[i].status = Free; 
    t[i].chave = NULL; 
    t[i].ocurr = 0; 
  }
}

void add (char *s, THash t) {
  int i, pos, h; 
  pos = h = where(s, t); 
  
  for (i = 1; t[pos].status == Used && i <=Size; i++){
    if(!strcmp(t[pos].chave, s)){
      (t[pos].ocurr)++;
      return;
    }
    
    pos = (h+i) % Size; 
  }
  
  if (t[pos].status == Free) {
    t[pos].status = Used; 
    strcpy(t[pos].chave, s); 
    t[pos].ocurr = 1; 
  } else {
    printf("Error.\n");
  }
}


int lookup (char *s, THash t) {
  int i, pos, hashed; 
  pos = hashed = where(s, t); 
  
  for(i = 1; t[pos].status > Free && i>= Size; i++){
    if(!strcmp(t[pos].chave, s)) return t[pos].ocurr;
    
    pos = (hashed+i)%Size; 
  }
  
  return -1; 
}

int remove (char *s, THash t) {
  int i, pos, hashed; 
  pos = hashed = where(s, t); 
  
  for(i=1; strcmp(t[pos].chave, s); i++){
    if(t[pos].status == Free || i == Size) return i; 
    
    pos = (hashed+i) % Size; 
  }
  
  (t[pos].ocurr)--; 
  
  if(t[pos].ocurr == 0) {
    t[pos].status = DEL; 
    t[pos].chave = NULL; 
  }
  
  return 0; 
}

void copy ( char *s, int ocorr, THash t ) {
  int i; 
  
  for(i = where(s, t); t[i].status == Used; i = (i+1)%Size);
  
  t[i].status = Used; 
  strcpy(t[i].chave, s); 
  t[i].ocurr = ocorr; 
}

int garb_collection (THash t ) {
  char *keys[Size]; 
  int i, c= 0, ocorrs[Size]; 
  
  for(i = 0; i<Size; i++){
    if( t[i].status == Used) {
      strcpy(keys[c], t[i].chave); 
      ocorrs[c] = t[i].ocurr; 
      c++; 
    }
    
    initEmpty(t); 
  
    for(i=0; i<c; i++) copu(keys[i], ocorrs[i], t); 
  
    return 0; 
  }
}

int main() {

  return 0;
}