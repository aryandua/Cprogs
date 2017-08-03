#include <stdio.h>
#include <stdlib.h>
#define INFINITE 10000000
#define NODES 1000
#define E 47978

void calfsp(int orginal_t, int s, int t);

#define MIN(v, w, min) { \
  if(v<w && v<0) \
    min =v; \
  else if(w<=v && w<=0) \
    min = w; \
   else  \
     min = 0; \
}
struct e {
  int node;
  int length;
  struct e *next;
};
typedef struct e e_t; 
struct v {
  int vno;
  int P;
  e_t *edges;
  
};
typedef struct v v_t;

//a[x][y] denotes shortest path from s to y using x edges
int a[NODES+1][NODES+1];
int X[NODES][NODES];
int D[NODES][NODES];
int SP[NODES];
int revsp[NODES];
int sp_count=0;
int FSP[NODES][NODES];
v_t graph[NODES+1];
int w,cwv;

int main() {
  read_graph();
  create_s();
  Bf(0);
  recompute();
  remove_s();
  djikstra();
  undo_recompute();
  calculate_sp();
  print_final_min_shortest_path();
}

read_graph() {
  FILE *fptr;
  fptr=fopen("./files/g3.txt", "r");
  e_t *temp;
  int i;
  int n1,n2,l;
  for(i=1;i<NODES+1;i++) 
    graph[i].vno = i;
  for(i=1;i<E+1;i++) {
    fscanf(fptr, "%d",&n1);
    fscanf(fptr, "%d",&n2);
    fscanf(fptr, "%d",&l);
    temp=graph[n1].edges;

    if(temp != NULL) {
      while(temp->next != NULL) 
	temp=temp->next;  
      temp->next=malloc(sizeof(e_t));
      temp=temp->next;
    }
   
    else {
      graph[n1].edges=malloc(sizeof(e_t));
      temp = graph[n1].edges;
    }
    
    temp->node = n2;
    temp->length = l;
    temp->next = NULL;
  }
  fclose(fptr);
}

create_s() {
  int i;
  e_t *temp;
  graph[0].vno=0; //s
  graph[0].edges=malloc(sizeof(e_t));
  temp=graph[0].edges;
  for(i=0;i<E;i++) {
    temp->node = i+1;
    temp->length = 0;
    temp->next = malloc(sizeof(e_t)); 
    temp=temp->next;
  }
  temp->next = NULL;
  
}

Bf(int s) {
  e_t *temp;
  int i,v,k;
  FILE *fptr2;
  fptr2=fopen("allps", "w");
  a[0][s] = 0;
  for(i=1;i<NODES+1;i++) 
    a[0][i] = INFINITE;

  for(i=1;i<NODES+1;i++) {
    printf("RUNNING Bf %d\n", i);
    // if(i%500 == 0)
    //printf("%d\n",i);
    for(v=1;v<NODES+1;v++) {
      //find_w_cwv
      cwv = INFINITE;
      w=0;
      for(k=1;k<NODES;k++) {
	temp = graph[k].edges;
	while(temp != NULL) {
	  if(temp->node == v) {
	    // if(temp->length < cwv) {
	    if(a[i-1][graph[k].vno] + temp->length < a[i-1][w] + cwv) {
	      w = graph[k].vno;
	      cwv = temp->length;
	    }
	  }
	  temp=temp->next;
	}
      }

      //take the min into a[i,v] CHECK MACRO FOR INFO
      MIN(a[i-1][v], a[i-1][w] + cwv, a[i][v]);
    }
  }
    for(i=1;i<NODES+1;i++) {
      if(a[NODES][i] != a[NODES-1][i]) {
	printf("ALERT!!!! NEGATIVE CYCLE FOUND!!!\n");
	exit(1);
      }
      else {
	graph[i].P = a[NODES-1][i];
	//printf("%d: %d\n",i,graph[i].P);
      }
    }
    for(i=1;i<NODES+1;i++) {
      fprintf(fptr2, "%d\n",graph[i].P);
    }
    
    fclose(fptr2);
}


recompute() {
  int i;
  e_t *temp;
  FILE *fp3;
  fp3 = fopen("Ce", "w");
  for(i=1;i<NODES+1;i++) {
    temp = graph[i].edges;
    while(temp != NULL) {
      fprintf(fp3, "%d = ",temp->length);
      fprintf(fp3, "%d + ",temp->length);
      fprintf(fp3, "%d - ",graph[i].P);
      fprintf(fp3, "%d...",graph[temp->node].P);

      //  Ce =            Ce          Pu               Pv
      temp->length = temp->length + graph[i].P - graph[temp->node].P;
      fprintf(fp3, "%d... ",temp->length);
      fprintf(fp3, "FOR ARC FROM %d to %d\n",graph[i].vno,graph[temp->node].vno);
      //     if(temp->length < 0)
	//	printf("%d:%d\n",i+1,temp->length);
      temp=temp->next;
    }
  }
  fclose(fp3);
}
remove_s() {
  int i;
  
  for(i=1;i<NODES+1;i++) {
    graph[i-1].vno = graph[i].vno;
    graph[i-1].P = graph[i].P;
    graph[i-1].edges = graph[i].edges;
  }
  graph[i-1].vno=0;
  graph[i-1].P=0;
  graph[i-1].edges = NULL;
}

djikstra() {
  printf("RUNNING DJIKSTRA!!!\n");
  int i,j;
  for(i=0;i<NODES;i++) {
    for(j=0;j<NODES;j++) {
      X[i][j] = INFINITE;
    }
  }
  for(i=0;i<NODES;i++) 
    X[i][i] = 0;
  for(i=0;i<NODES;i++) {
    //printf("from %d...\n",i);
    djikstra_main(i);
  }
}

djikstra_main(int s) {

  //DECLARATION
  int i,j,V,U;
  int min;
  int gone_once;
  int inmold[NODES]; //1=in mold. 0 = not in mold
  e_t *temp;
  //INITIALIZING
  for(i=0;i<NODES;i++) {
    inmold[i] = 0;
    D[s][i] = INFINITE;
  }
  inmold[s] = 1;
  D[s][s] = 0;
  
  //MAIN LOOP
  for(i=0;i<NODES;i++) { 
    gone_once = 0;
    //PICK MIN EDGE FROM IN MOLD TO NOT IN MOLD
    min = INFINITE;
    for(j=0;j<NODES;j++) {
      temp=graph[j].edges;
      while(temp != NULL) {
	if(inmold[graph[j].vno-1]) { //U in mold
	  if(!(inmold[(temp->node)-1])) { //V not in mold
	    if(temp->length < min) { //It is the minimum edge from mold to not in mold
	      gone_once = 1;
	      V  = temp->node;
	      U=graph[j].vno;
	      min = temp->length;
	    }
	  }
	}
	temp=temp->next;
      }
    }
    if(gone_once) {
      D[s][V-1] = D[s][U-1] + min;
      X[s][V-1] = graph[U-1].vno;
      inmold[V-1] = 1;
    }
  }
  // for(i=0;i<NODES;i++) 
  //  printf("%d: %d = %d\n",s+1,i+1,D[s][i]);
}


calculate_sp() {
  int s,t,i;
  for(s=0;s<NODES;s++) {
    for(t=0;t<NODES;t++) {
      for(i=0;i<NODES;i++) 
	SP[i] = 0;
      sp_count = 0;

      calfsp(t,s,t);
    }
  }
}

void calfsp(int original_t, int s, int t) {
  int i,j,length_spi_spj;
  e_t *temp;
  temp=graph[s].edges;

  SP[sp_count] = t;
  sp_count++;
  if(s != t) {
    if(X[s][t] != INFINITE) 
      calfsp(original_t,s,(X[s][t]-1));
  }
  else {
    reverse_sp();
    for(i=0;i<sp_count-1;i++) {
      temp = graph[SP[i]].edges;
      j=i+1;
      length_spi_spj = INFINITE;
	while(temp!=NULL) {
	  if(temp->node == graph[SP[j]].vno) {
	    length_spi_spj = temp->length;
	  }
	  temp=temp->next;
	}
	FSP[s][original_t] += length_spi_spj;
      }
    }
}

reverse_sp()  {
  int i;
  for(i=0;i<sp_count;i++) {
    revsp[i] = SP[sp_count-(i+1)];
  }
  for(i=0;i<sp_count+1;i++) {
    SP[i] = revsp[i];
  }
}

print_final_min_shortest_path() {
  int i,j,a,b,min;
  min = INFINITE;
  for(i=0;i<NODES;i++) {
    for(j=0;j<NODES;j++) {
      if(FSP[i][j]<min) {
	a = i+1;
	b = j+1;
	min = FSP[i][j];
      }
    }
  }
  printf("THE MINIMUM SHORTEST PATH GOES FROM %d to %d WITH LENGTH %d\n",a,b,min);
}

undo_recompute() {
 int i;
  e_t *temp;
  for(i=0;i<NODES;i++) {
    temp = graph[i].edges;
    while(temp != NULL) {
      //  Ce =            Ce          Pu               Pv
      temp->length = temp->length - graph[i].P + graph[temp->node-1].P;
      printf("%d\n",temp->length);
      temp=temp->next;
    }
  }

}
