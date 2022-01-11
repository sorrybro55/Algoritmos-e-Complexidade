#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NV 5 
#define NE 0

typedef int GraphMat [NV][NE];

typedef struct edge {
  int dest; //destino da aresta
  int cost; //peso da aresta 
  struct edge *next; 
} *EList; 
typedef EList Graph [NV]; 

void mat2list (GraphMat go, Graph gd) {
  int i, j; 
  EList tmp; 
  for(i=0; i<NV; i++){
    gd[i]=NULL; 
    for (j=NV-1; j>0; j--){
      tmp = malloc (sizeof(struct edge)); 
      tmp->dest = j; 
      tmp->cost = go[i][j]; 
      tmp->next = gd[i]; 
      gd[i] = tmp; 
    }
  }
}

void list2mat (Graph go, GraphMat gd) {
  int i, j; 
  EList tmp; 
  
  for(i=0; i<NV; i++){
    for(tmp = go[i]; tmp != NULL; tmp = tmp->next)
      j = tmp->dest; 
      gd[i][j] = go[i]->cost; 
  }
}
//Complexidade prcura em Matrizes de Adjacencias Θ(V²) 

int nArestas (Graph g) {
  int r = 0; 
  int i; 
  EList it; // para percorrer listas 
  
  for (i=0; i<NV; i++){ // para percorrer os adjacentes 
    for (it = g[i]; it != NULL; it = it->next) r++;
  }
  return r;
}
 //Complexidade procura em Listas de Adjacencia TnArestas(V, E) = Θ(V + E)     

 #define NEd 0

typedef struct edgeV { 
  int dest; 
  int cost; 
}EdgeV; 
typedef struct {
  int vertices [NV+1]; 
  EdgeV edges [NEd]; 
} GraphVect; 

void list2Vect (Graph go, GraphVect *gd){
  int i,k; 
  EList it; 
  
  for( i=k=0; i<NV; i++){
    gd->vertices[i] = k; 
    for (it = go[i]; it != NULL; it = it->next){
      gd->edges[k].dest = it->dest; 
      gd->edges[k].cost = it->cost; 
      k++; 
    }
  }
  gd->vertices[i] = k; 
}

void vect2List (GraphVect *go, Graph gd) {
  int i, k; 
  EList tmp; 
  
  for(i=0; i<NV; i++){
    gd[i] = NULL; 
    for(k=go->vertices[i+1]-1; k>= go->vertices[i]; k--){
      tmp = malloc(sizeof(struct edge)); 
      tmp->dest = go->edges[k].dest; 
      tmp->cost = go->edges[k].cost; 
      tmp->next = gd[i]; 
      gd[i]=tmp; 
    }
  }
}


int edgeWMat (GraphMat g, int o, int d, int *w){
  *w = g[o][d]; 
  return (*w != NE); 
}

int edgeW (Graph g, int o, int d, int *w){
    EList it; 
    int found = 0; 
    for(it = g[o]; (it != NULL) && !found; it = it->next)
        found = (it->dest == d);
    if (found) *w = it->cost; 
    return found; 
} // PIOR CASO ----> O( V )                 MELHOR CASO ----> O( 1 )

int edgeWVect (GraphVect *g, int o, int d, int *w){
    int k; 
    int found = 0; 
    for(k = g->vertices[o]; (k< g->vertices[o+1]) && !found; k++) found = (g->edges[k].dest == d); 
    
    if (found) *w = g->edges[o].cost; 
    return found; 
}


int indegreeMat (GraphMat g, int v){
    int i,r; 

    for(i=r=0; i<NE; i++){
        if(g[i][v] != NE) r++; 
    }
    return r; 
}

int outdegreeMat (GraphMat g, int v){
    int i,r; 

    for(i=r=0; i<NE; i++){
        if(g[v][i] != NE) r++; 
    }
    return r; 
}

//Complexidade das duas funcoes acima é linear: O( V )

int outdegree (Graph g, int v){
    int r=0; 
    EList it; 

    for(it=g[v]; it != NULL ; it = it->next) r++; 
    return r; 
}

int indegree (Graph g, int v){
    int r, i; 
    EList it; 

    for(i=r=0; i<NV; i++){
        for (it = g[i]; it != NULL; it = it->next)
            if (it->dest == v) r++; 
    }
    return r; 
} // O ( V+E )

int outdegreeVect (GraphVect *g, int v){
    return (g->vertices[v+1] - g->vertices[v]);
}

int indegreeVect (GraphVect *g, int v){
    int r, i; 
    EList it; 

    for(i=r=0; i<NE; i++)
        if (g->edges[i].dest == v) r++; 
    return r; 
}

//Depth First 

int procura (Graph g, int o, int d ){
  int found = 0; 
  EList it; 
  if (o==d) found = 1; 
  else 
    for (it = g[o]; it != NULL && !found; it = it->next)
      found = procura(g, it->dest, d);
  return found; 
}
// Pode ficar em ciclo caso o grafo seja ciclico, uma possivel forma de contornar este problema é construir um array que guarde os vertices por onde passamos 

int procura (Graph g, int o, int d){
  int visitados [NE]; 
  int i; 
  for(i=0; i<NV; i++){
    visitados[i] = 0; 
  }
  return (procuraRec (g,o,d,visitados));
}

int procuraRec (Graph g, int o, int d, int v[]){
  int found = 0; 
  EList it; 
  v[o] = 1; 
  if (o == d) found = 1; 
  else 
    for (it = g[o]; it != NULL && !found; it = it->next)
      if ( !v[it->dest]) found = procuraRec (g, it->dest, d, v);
  return found; 
}

// Travessia Depth-first 

int travessiaDF (Graph g, int o){
  int visitados [NV]; 
  int i; 
  for (i=0; i<NV; i++) visitados[i] = 0; 

  return (DFRec (g, o, visitados));
}

int DFRec (Graph g, int o, int v[]){
  int count = 1; 

  EList it; 
  v[o] = 1; 
  for (it = g[o]; it != NULL; it = it->next)
    if (! v[it->dest]) count += DFRec (g, it->dest, v);
  return count; 
}

int maiorCL (Graph g){
  int visitados[NV]; 
  int i, c; 
  int max = 0; 
  for (i =0; i <NV; i++)
    visitados[i] = 0; 

  for(i=0; i<NV; i++){
    if( visitados[i] == 0) {
      c = DFRec (g, i, visitados);
      if (c > max) max = c; 
    }
  }

  return max; 
}

int biPartite (Graph g){
  int visitados[NV]; 
  int i, c=1, r; 

  for (i=0; i<NV; i++) visitados [i] = 0; 

  r = DFRec_group (g, 0, visitados, c); 

  return r; 
}

int DFRec_group (Graph g, int o, int v[], int group){
  int r = 1; 

  EList it; 
  if (v[o] == 0 && group == 1) {
    v[o] = group; 
    group = 2;
  }
  else if (v[o] == 0 && group == 2) {
    v[o] = group; 
    group = 1;
  }
  else r = 0;


  for (it = g[o]; it != NULL; it = it->next)
    if (! v[it->dest]) r = r || DFRec_group (g, it->dest, v, group);
  return r; 
}

// Travessia Depth-First incorporando a construcao de uma arvore, onde v[i] representa o antecessor de i; 

int travessiaDF2 (Graph g, int o, int p[]){
  int visitados [NV]; 
  int i; 

  for (i = 0; i< NV; i++){
    visitados[i] = 0; 
    p[i] = -2; // partindo do principio que o grafo nao aceita valores negativos 
  }
  p[0] = -1; 
  return (DFRec2 (g, o, visitados, p)); 
}

int DFRec2 (Graph g, int o, int v[], int p[]){
  int count = 1; 
  EList it; 
  v[o] = 1; 
  for(it = g[o]; it != NULL ; it = it->next){
    if (!v[it->dest]) {
      p[it->dest] = 0; 
      count += DFRec2 (g, it->dest, v, p);
    }

    return count; 
  }
}

/* Podemos reescrever a definicao acima sem recorrer ao array visitados

int travessiaDF2(Graph g, int o, int p[]){
  int i; 
  for(i = 0; i<NV; i++){
    p[i] = -2; 
  }
  p[o] = -1; 
  return (DFRec2 (g, o, p));
}

int DFRec2 (Graph g, int o, int p[]){
  int count = 1; 
  EList it; 

  for (it = g[o]; it != NULL; it = it->next){
    if (p[it->dest] == -2){
      p[it->dest] = o; 
      count += DFRec2 (g, it->dest,p); 
    }
  }
  return count; 
}
*/

//Breadth-First 

/*
typedef struct queue{
  int valor[10]; 
  int inicio, tamanho; 
} Queue;

Queue emptyQueue(){
  Queue nova; 
  nova.inicio = 0;
  nova.tamanho = 0;
  return nova ;
}

void enqueue (Queue q, int x){
  if( q.tamanho < 10){
    q.valor[q.tamanho + q.inicio] = x; 
    q.tamanho++;
  }
}

void dequeue (Queue q, int *x){
  if(q.tamanho > 0){
    *x = q.valor[q->inicio]; 
    q->inicio++; 
    q->tamanho--; 
  }
}

int empty(Queue q){
  return (q.tamanho == 0);
}

int travessiaBF (Graph g, int o){
  int visitados[NV]; 
  Queue q; 
  int count = 0; 
  EList it; 

  q = emptyQueue(); 
  enqueue (q,o); 
  visitados[o] = 1; 

  while ( ! empty(q)){
    dequeue(q,o);
    count++; 
    for (it = g[o]; it != NULL; it = it->next)
      if(!visitados[it->dest]) enqueue(q,it->dest);
  }

  return count; 
}

*/

int travessiaBF (Graph g, int o){
  int visitados[NV]; 
  int q[NV]; 
  int inicio, fim; 
  int count = 0; 
  EList it; 

  inicio = fim = 0; 
  q[fim++] = o; 
  visitados[o] = 1; 
  while (inicio < fim){
    o = q[inicio++];
    count++; 
    for (it = g[o]; it != NULL; it = it->next){
      if (! visitados[it->dest])
        q[fim++] = it->dest; 
    }
    return count;
  }
}

int travessiaBFTree (Graph g, int o, int ant[]){
  int q[NV]; 
  int inicio, fim, i; 
  int count = 0; 
  EList it; 

  for(i=0; i<NV; i++) ant[i] = -2; 
  inicio = fim = 0; 
  q[fim++] = o; 
  ant[o] = -1; 
  while(inicio < fim ){
    o = q[inicio++];
    count++; 
    for (it = g[o]; it!=NULL; it = it->next){
      if (ant[it->dest] == -2){
        ant[it->dest] = o; 
        q[fim++] = it->dest;
      }
    }
  }

  return count; 
}

// Algoritmo Khan

int khanTS (Graph g, int seq[]){
  EList it; 
  int v, inicio, fim; 
  int nant[NV]; 
  
  for(v = 0; v <NV; v++) nant[v] = 0; 
  for(v=0; v<NV; v++)
    for(it = g[v]; it!=NULL; it = it->next){
      nant[it->dest]++;
    }
  
  inicio = fim = 0; 
  for(v=0; v<NV; v++){
    if (nant[v] == 0)
      seq[inicio++] = v; 
  }

  while(inicio < fim){
    v = seq[inicio++];
    for(it = g[v]; it != NULL; it = it->next){
      nant[it->dest]--; 
      if(nant[it->dest] == 0)
        seq[fim++] = it->dest;
    }
  }
  return inicio; 
}

// Algoritmo Tarjan

int tarjanTS (Graph g, int seq[]){
  int color[NV];
  int v,j,t,r; 
  for(v=0; v<NV; v++) color[v] = 0; //WHITE

  r=1; 
  t=0; 
  for(v=0; v<NV; v++){
    if(color[v] == 0) t+= dfirstTopSort (g, v, color, &r, seq+t);
  }

  for(v=0, j = t; v<j; v++, j--) swap(seq, v, j);

  return r;
}

int dfirstTopSort (Graph g, int o, int color[], int *success, int seq[]){
  int t; 
  EList it; 

  color[o] = 1; //GREY 
  t=0; 

  for(it=g[o]; it!=NULL; it = it->next)
    if (color[it->dest] == 0) t+= dfirstTopSort(g,it->dest, color, success, seq+t);
    else if (color[it->dest] == 1) *success = 0; 

  seq[t++] = o; 
  color[0] = 2; //BLACK
  return t;
}

// Componentes fortemente ligadas

int tarjanSCC (Graph g){
  int color [NV], tIn [NV], mtIn [NV];
  int i; 
  int tStamp = 0; 
  int r = 0; 

  for (i=0; i<NV; i++) color[i] =  0; // WHITE

  for (i=0; i<NV; i++) 
    if(color [i] == 0) r+= sccRec (g, &tStamp, i, color, tIn, mtIn);

  return r; 
}

int sccRec (Graph g, int *tStamp, int v, int color[], int t[], int M[]){
  EList it; 
  int r = 0; 
  color[v] = 1; //GREY
  M[v] = t[v]  =*tStamp++;

  for(it = g[v]; it != NULL; it = it->next){
    if (color[it->dest] != 2 ){ // not BLACK
      if (color[it->dest] == 0) r+= sccRec(g,tStamp, it->dest, color, t, M);
      if (M[it->dest] < M[v]) M[v] = M[it->dest]; 
    }

    if (M[v] == t[v]) r++; 
    color[v] = 2; 
    return r; 
  }

}

//Fecho transitivo 

void tclosure (Graph g, GraphMat gp){
  int v, i; 

  for(v=0; v<NV; v++){
    for (i=0; i < NV; i++) gp[v][i] = 0; 

    DFRec (g,v,gp[v]);
  }
}

// Custo Ttclosure(V, E) = Θ(V ∗ (V + E)), no caso de grafos pouco densos onde E = Θ(V) o custo é de (Θ(V²))
// Caso o grafo seja mais denso E = Θ(V²) o custo é de (Θ(V³))


// Algoritmo Warshall 


void warshall (Graph g, GraphMat gp) {
  EList it; 
  int u, v, x; 

  for(u=0; u <NV; u++){
    for (v = 0; v<NV; v++){
      gp[u][v] = NE; 
    }
    for(it = g[u]; it !=NULL; it = it->next) gp[v][it->dest] = 1;
  }

  for(x=0; x<NV; x++)
    for(u=0; u<NV; u++)
      if (gp[u][x])
      for(v=0; v<NV; v++) 
        if(gp[x][v]) gp[u][v] = 1;
}

// Os tres ciclos (aninhados) no final da funcao fazem com que a sua complexidade seja O(V³)


//Arvore geradora de custo minimo

// Algoritmo de Prim 













int main() {

  return 0;
}