#define HSIZE 10

typedef struct bucket {
  int probeC; // -1: Free; -2: Deleted 
  int key;
  int value;
} Bucket; 

typedef Bucket HashTable [HSIZE]; 

void initTab (HashTable h){
  int i; 
  
  for(i=0; i<HSIZE; h[i++].probeC = -1);
}

//Linear probing 
int find_probe (HashTable h, int k){
  int p = hash(k, HSIZE); 
  int tmp, count; 
  
  for (count = HSIZE; count > 0 && h[p].probeC >= 0 && h[p].key == k; count--)
    p = (p+1)%HSIZE; 
  
  if (h[p].key != k) {
    if(count == 0 ) p = -1; //table is full
    else {
      tmp = p; 
      while( count > 0 && h[p].probeC < 0 && h[p].key != k) {
        count--; 
        p = (p+1)%HSIZE; 
      }
      
      if ( h[p].key != k) p = tmp; 
    }
  }
  return p; 
}

int lookup (HashTable t, int key, int *value){
 int i = hash(key, HSIZE); 
 int probe = 0; 
 
 while((t[i].probeC >= 0) && (t[i].key != key) && (probe < HSIZE) ){
   i = (i+1)%HSIZE; 
   probe++; 
 }
 
 if(probe == HSIZE) return 2; //overload
 if(t[i].probeC >= 0) {
   *value = t[i].probeC; 
   return 0; 
 }
 return 1; //fail
}

int update (HashTable t, int key, int value){
  int i = hash(key, HSIZE); 
  int probe = 0; 
  
  while((t[i].probeC >= 0) && (t[i].key != key) && (probe < HSIZE)){ 
    i = (i+1)%HSIZE; 
    probe++;
 }
 
 if(probe > HSIZE) return 2; //overload
 if ( t[i].probeC != -1){
   t[i].value = value; 
   return 1; //exists
 }
 t[i].key = key; 
 t[i].probeC = value; 
 t[i].probeC = probe; 
 return 0; //new key
}

int delete (HashTable h, int k) {
  int p = find_probe (h,k); 
  int r = 0; 
  
  if( p > 0 && h[p].probeC >= 0 ) { // key exists 
    h[p].probeC = -2; 
  }
  else r = 1; 
  return r; 
}

int main() {

  return 0;
}