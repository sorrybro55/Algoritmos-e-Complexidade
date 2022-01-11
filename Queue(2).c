#include <stdlib.h>;

typedef struct celula{
  int value;
  struct celula *p; 
} Celula;

typedef struct queue{
  struct celula *inicio, *fim; 
} Queue; 

void initQueue (Queue *q){
  q->inicio = q->fim = NULL; 
}

int isEmpty(Queue *q){
  return (q->inicio == NULL);
}

int enqueue( Queue *q, int x) {
  int r=0; 
  Celula *n; 
  
  n = malloc(sizeof(Celula)); 
  if (n == NULL) r = 1; 
  else{
    n->value = x; 
    n->p = NULL; 
    q->fim->p = n; 
    q->fim = n; 
    if (q->inicio == NULL) q->inicio = n;
  }
  return r; 
}

int dequeue( Queue *q, int *x){
  int r = 0; 
  Celula *temp; 
  if (q->inicio == NULL) r = 1; 
  else{
    *x = q->inicio->value; 
    temp = q->inicio; 
    q->inicio = q->inicio->p; 
    if(q->inicio ==NULL ) q->fim = NULL; 
    free(temp); 
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