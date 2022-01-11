#include <stdlib.h>;

#define MAX 10

typedef struct queue{
  int size; 
  int *values; 
  int inicio, tamanho; 
} Queue; 

void initQueue (Queue *q){
  q->size = MAX; 
  q->values = malloc ( sizeof(q->size)); 
  q-> inicio = 0; 
  q->tamanho = 0;   
}

int isEmpty(Queue *q){
  return (q->tamanho == 0);
}

int enqueue( Queue *q, int x) {
  int r=0;  
 
  if ( q->tamanho == q->size) {
    q->size = q->size * 2; 
    if (realloc(q->values, sizeof(q->size)) != NULL) q->values = realloc (q->values,sizeof(q->size)); 
    else r = 1; 
    q->values[q->tamanho++] = x;
  }
  else q->values[q->tamanho++] = x; 
  return r; 
}

int dequeue( Queue *q, int *x){
  int r = 0; 
  if (q->tamanho == 0) r = 1; 
  else{
    *x = q->values[q->inicio++];
  }
  return r; 
}


int main() {
  Queue q; 
  int valor, r;
  
  initQueue(&q); 
  r = isEmpty(&q); 
  
  enqueue(&q, 23);
  enqueue(&q, 2);
  enqueue(&q, 14);
  
  r = isEmpty(&q);
  dequeue(&q, &valor);
  dequeue(&q, &valor);

  return 0;
}