#include <stdio.h>
#include <stdlib.h>
#define INFINITE 10000000
#define NODES 1000
#define E 47978
#define MIN(a, b, c, min) { \ 
  if(a<=b && a<=c) \
    min = a; \
  else if(b<=c && b<=a) \ 
    min = b; \
   else if(c<=a && c<=b) \ 
     min = c; \
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

int a[E][NODES+1];
v_t graph[NODES+1];
int w,cwv;

int main() {
  read_graph();
  create_s();
  Bf(0);
  /*
  recompute();
  djikstra();
  min_short_path();
  undo_formula();
  Bf_from_u(); 
  */
}

read_graph() {
  FILE *fptr;
  fptr=fopen("./g1.txt", "r");
  e_t *temp;
  int i;
  int n1,n2,l;
  for(i=1;i<E+1;i++) {
    fscanf(fptr, "%d",&n1);
    fscanf(fptr, "%d",&n2);
    fscanf(fptr, "%d",&l);
    graph[n1].vno =  n1;
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
  a[0][s] = 0;
  for(i=1;i<NODES+1;i++) 
    a[0][i] = INFINITE;

  for(i=1;i<E;i++) {
     if(i%500 == 0)
      printf("%d\n",i);
    for(v=1;v<NODES+1;v++) {
      //find_w_cwv
      cwv = INFINITE;
      w=0;
      for(k=1;k<NODES;k++) {
	temp = graph[k].edges;
	while(temp != NULL) {
	  if(temp->node == v) {
	    if(temp->length < cwv) {
	      w = graph[k].vno;
	      cwv = temp->length;
	    }
	  }
	  temp=temp->next;
	}
      }

      //take the min into a[i,v]
      MIN(a[i-1][v], a[i-1][w] + cwv, 0, a[i][v]);
    }
  }
    for(i=1;i<NODES+1;i++) {
      if(a[E-2][i] != a[E-1][i]) {
	printf("ALERT!!!! NEGATIVE CYCLE FOUND!!!\n");
	exit(1);
      }
      else {
	graph[i].P = a[E-1][i];
	printf("%d: %d\n",i,graph[i].P);
      }
    }
    
}
int find_w_cwv(int v) {
 
      return 0;
}
