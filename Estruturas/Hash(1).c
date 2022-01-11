#define STATUS_FREE 0
#define STATUS_USED 1
#define HSIZE 10

typedef struct bucket {
  int status;
  int key;
  int info;
} Bucket; 

typedef Bucket HashTable [HSIZE]; 

void initTab (HashTable h){
  int i; 
  
  for(i=0; i<HSIZE; h[i++].status = STATUS_FREE);
}

//Linear probing 

int find_probe (HashTable h, int k){
  int p = hash(k,HSIZE); 
  int count; 
  
  for(count = HSIZE; count > 0 && h[p].status != STATUS_FREE && h[p].key != k; count--)
    p = (p+1)%HSIZE; 
  if (count == 0) p=-1; // table is full
  return p; 
}

int lookup (HashTable h, int k, int *i){
  int p = find_probe(h, k); 
  int found; 
  
  if(p>=0 && h[p].key == k){
    *i = h[p].info; 
    found = 1; 
  }
  else found = 0;
  return found; 
}

int update (HashTable h, int k, int i){
  int p = find_probe(h,k); 
  int r; 
  
  if(p < 0) { // table is full 
   r = 0; 
  }
  
  else if (h[p].key == k) {
    h[p].info = i; 
    r= 1; 
  }
  
  else { // new key
    h[p].status = STATUS_USED; 
    h[p].key = k; 
    h[p].info = i; 
    r= 2; 
  }
  return r; 
}

// Quadratic probing 

int find_Quad_probe (HashTable h, int k){
  int p = hash(HSIZE, k); 
  int count, d=1; 
  
  for(count = HSIZE; count > 0 && h[p].status !=STATUS_FREE && h[p].key !=k; count --){
    p = (p+d)%HSIZE; 
    d++; 
  }
  if (count == 0) p=-1; 
  return p; 
}
    


int main() {

  return 0;
}