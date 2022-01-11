#define MAX 10
typedef struct queue{
  int values[MAX]; 
  int inicio, tamanho; 
} Queue; 



void initQueue (Queue *q){
  q->inicio = 0; 
  q->tamanho = 0; 
}

int isEmpty(Queue *q){
  return (q->tamanho == 0);
}

int enqueue( Queue *q, int x) {
  int r=0; 
  if (q->tamanho == MAX) r = 1;
  else 
    q->values[q->inicio + q->tamanho++] = x;
  return r; 
}

int dequeue( Queue *q, int *x){
  int r = 0; 
  if (q->tamanho == 0 ) r = 1;
  else{
    *x = q->values[q->inicio]; 
    q->inicio = (q->inicio + 1) % MAX; 
    q->tamanho--; 
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