#include <stdio.h>
#include <stdlib.h>
#define SIZE 500
#define K1 4
struct p {
  int vno;
  int noe;
  int belongtocluster;
  int edges[SIZE-1];
  int edge_cost[SIZE-1];
};
typedef struct p p_t;

struct c {
  int vno;
  int main;
  struct c *next;
};
typedef struct c c_t;

c_t clusters[K1];
p_t points[SIZE];
int haveedge[SIZE][SIZE];
int belongs[SIZE];
int clustersval=0;
int main() {
  init();
  readfile();
  cluster();
  findmaxspace();
  printall();
  return 0;
}
int init() {
  int i,j;
  for(i=0;i<SIZE;i++) {
    for(j=0;j<SIZE;j++) {
      haveedge[i][j] = 1;
    }
  }
  for(i=0;i<SIZE;i++){
    points[i].belongtocluster = i+1;
    belongs[i] = 0;
  }
}

int readfile() {
  int i,node1, node2,length, useless;
  FILE *fptr;
  fptr=fopen("./a.txt", "r");
  fscanf(fptr,"%d",&useless);
  for(i=0;i<((SIZE*(SIZE-1))/2);i++) {
    fscanf(fptr,"%d",&node1);
    fscanf(fptr, "%d",&node2);
    fscanf(fptr, "%d\n",&length);

    points[node1-1].edges[points[node1-1].noe] = node2;
    points[node1-1].edge_cost[points[node1-1].noe] = length;
    points[node1-1].noe++;

    points[node2-1].edges[points[node2-1].noe] = node1;
    points[node2-1].edge_cost[points[node2-1].noe] = length;
    points[node2-1].noe++;
  }
  for(i=1;i<=SIZE;i++) points[i-1].vno = i;
}

int cluster() {
  int i,j, k=SIZE;
  int min=1000000,vmin1,vmin2;
  while(k!=K1) {
    for(i=0;i<SIZE;i++) {
      for(j=0;j<SIZE-1;j++) {
	if(points[i].edge_cost[j] < min && have_edge(points[i].vno,points[i].edges[j])) {
	  min=points[i].edge_cost[j];
	  vmin1 = points[i].vno;
	  vmin2 = points[i].edges[j];
	}
      }
    }
    printf("merging %d and %d\n",vmin1,vmin2);
    if(belongs[vmin1-1]) {
      belongs[vmin2-1] = 1;
      points[vmin2-1].belongtocluster = points[vmin1-1].belongtocluster;
    }
    else if(belongs[vmin2-1]) {
      belongs[vmin1-1] = 1;
      points[vmin1-1].belongtocluster = points[vmin2-1].belongtocluster;
    }
    else {
      belongs[vmin1-1] = 1;
      belongs[vmin2-1] = 1;
      points[vmin2-1].belongtocluster = vmin1;
    }
    merge(vmin1, vmin2);
    min=100000;
    k--;
  }
  for(i=0;i<SIZE;i++) printf("%d, ",points[i].belongtocluster);
  printf("\n");
}

int have_edge(int v1, int v2) {
  return haveedge[v1-1][v2-1];
}

int merge(int i, int j) {
  haveedge[i-1][j-1] = 0;
  haveedge[j-1][i-1] = 0;
}

int findmaxspace() {
  c_t *temp;
  int i,j;
  int leaders[K1];
  int known[K1];
  int knownval = 0;
  for(i=0;i<K1;i++) known[i] = 0;
  temp = (c_t*) malloc(sizeof(c_t));
  for(i=0;i<SIZE;i++) {
    if(hasit(known,K1,points[i].belongtocluster)) {
      for(j=0;j<K1;j++) {
	if(clusters[j].main == points[i].belongtocluster) {
	  temp=&clusters[j];
	  while(temp->next != NULL) {
	    temp=temp->next;
          }
	  temp->next = (c_t*) malloc(sizeof(c_t));
	  temp=temp->next;
	  temp->main=points[i].belongtocluster;
	  temp->vno = points[i].vno;
	  temp->next = NULL;
	}
      }
    }
    else {
      temp = &clusters[clustersval];
      temp->main = points[i].belongtocluster;
      temp->vno = points[i].vno;
      clustersval++;
      known[knownval] = points[i].belongtocluster;
      knownval++;
      temp->next = NULL;
    }
    temp->next = NULL;
  }
}

int hasit(int *arr, int s, int t) {
  int i;
  for(i=0;i<s;i++) {
    if(arr[i] == t) {
      return 1;
    }
  }
  return 0;
}

int printall() {
  c_t *temp;
  int i;
  for(i=0;i<K1;i++) {
    printf("Cluster %d: ",i+1);
    temp =  (c_t*) malloc(sizeof(c_t));
    temp = &clusters[i];
    while(temp != NULL) {
      printf("%d, ",temp->vno);
      temp=temp->next;
    }
    printf("\n");
  }
}
