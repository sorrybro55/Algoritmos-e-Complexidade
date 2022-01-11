#define STATUS_FREE 0
#define STATUS_USED 1
#define STATUS_DELETED 2 
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
  int p = hash(k, HSIZE); 
  int tmp, count; 
  
  for (count = HSIZE; count > 0 && h[p].status == STATUS_USED && h[p].key == k; count--)
    p = (p+1)%HSIZE; 
  
  if (h[p].key != k) {
    if(count == 0 ) p = -1; //table is full
    else {
      tmp = p; 
      while( count > 0 && h[p].status != STATUS_FREE && h[p].key != k) {
        count--; 
        p = (p+1)%HSIZE; 
      }
      
      if ( h[p].key != k) p = tmp; 
    }
  
  return p; 
}
}

int lookup (HashTable h, int k, int *i){
  int p = find_probe(h, k); 
  int found; 
  
  if(p>=0 && h[p].key == k && h[p].status == STATUS_USED){
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
    h[p].status = STATUS_USED; 
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

int delete (HashTable h, int k) {
  int p = find_probe (h,k); 
  int r = 0; 
  
  if( p > 0 && h[p].status == STATUS_USED ) { // key exists 
    h[p].status = STATUS_DELETED; 
  }
  else r = 1; 
  return r; 
}

void rehash (int S, Bucket source[S], int T, Bucket target[T]){
  int is, it; 
  
  for (it = 0; it < T; it ++) {
    target[it].status = STATUS_FREE; 
  }
  
  for (is = 0; is < S; is ++) {
    if (source[is].status = STATUS_USED) {
      it = hash(source[is].key , T);
    
      while (target[it].status != STATUS_FREE){
        it = (it+1)%T; 
      }
      
      target[it].status = STATUS_USED; 
      target[it].key = source[is].key; 
      target[it].info = source[is].info; 
      }
  }
}

void garbageC (HashTable h) {
  int idx; 
  
  for (idx = HSIZE-1; idx >= 0 ; idx --) {
    if (h[idx].status == STATUS_DELETED) h[idx].status = STATUS_FREE; 
  }
}
    


int main() {

  return 0;
}