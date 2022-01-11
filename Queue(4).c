void swap(int v[], int x, int y)
{
    int temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

void bubbleup(int v[], int i){
  int p = (i-2)/2; //antecessor de i 
  while (i>0 && v[i] < v[p] ){
    swap(v, i, p) ;
    i = p;  // nova posicao do elemento 
    p = (i-1)/2; // antecessor de i
  }
}

void bubbledown(int v[], int N, int i){
  int f = 2*i+1; 
  
  while(f<N){
    if( f+1 <N && v[f+1] < v[f]){
      //o descendente da direita é menor
      f++; 
    }
    if (v[f] > v[i] ) break; 
    swap(v, i, f); 
    i=f; f=2*i+1; 
  }
}

#define MAX 10
typedef struct prQueue{
  int values [MAX]; 
  int size;
} PriorityQ; 

void initPriorityQ (PriorityQ *q){
  q->size = 0; 
}

int isEmpty (PriorityQ *q){
  return (q->size == 0); 
}

int add (PriorityQ *q, int x){
  int r = 0; 
  if(q->size == MAX) r = 1;
  else {
    q->values[q->size] = x; 
    bubbleup(q->values, q->size); 
    q->size++; 
  }
  return r; 
}

int remove (PriorityQ *q, int *x){
  int r = 0; 
  if (q->size == 0) r = 1; 
  else {
    *x = q->values[0];
    q->values[0] = q->values[--q->size]; 
    bubbledown(q->values, q->size, 0); 
  }
}

void heapify(int v[], int N){
  int i; 
  for(i=1; i<N; i++){
    bubbleup(v,i);
  }
}

void heapSort(int v[], int N){
  heapify (v,N);
  while (--N > 0){
    swap(v, 0 ,N);
    bubbledown(v, N, 0); 
  }
}

void heapify2(int v[], int N ) {
  int i; 
  for (i=(N-2)/2; i>=0; i--) bubbledown(v, N, i); 
}


int main() {
  int v[12]={30,26,22,18,16,13,11,8,6,5,4,3};
  
  heapify(v, 12);
  
  
  return 0;
}