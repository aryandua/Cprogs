#include <stdio.h>
#include <stdlib.h>
#define SIZE 9
struct elist {
  int number;
  struct elist *next;
};
typedef struct elist t_elist;
struct node {
  int vno;
  int ecount;
  t_elist *edges;
};
typedef struct node t_node;
t_node graph[SIZE];
t_node graph_inv[SIZE];
t_node graph_new[SIZE];
int explored[SIZE];
int leader[SIZE];
int time[SIZE];
int t;
int s;

int main() {
  read();
  invert();
  loopdfs(graph_inv);
   printf("time : ");
  int i;
  for(i=0;i<SIZE;i++) {
    printf("%d ,",time[i]);
  }
   gnew();
  loopdfs(graph_new);

  printf("graph=\n");
  print(graph);
  printf("\n\n");
  printf("graph_inv\n");
  print(graph_inv);
  printf("\n\n");
  printf("leader : ");
  for(i=0;i<SIZE;i++) {
    printf("%d ,",leader[i]);
  }
  printf("\n\n");
  printf("graph_new: \n");
  print(graph_new);
}
gnew() {
  int i,e;
  t_elist *temp,*temp2;
  for(i=0;i<SIZE;i++) {
    graph_new[i].edges=(t_elist *)malloc(sizeof(t_elist));
    graph_new[i].vno=time[i];
    graph_new[i].ecount=graph[i].ecount;
    temp2=graph_new[i].edges;
    temp=graph[i].edges;
    while(temp!=NULL) {
      e=temp->number;
      temp2->number=time[e-1];
      temp=temp->next;
      if(temp!=NULL) {
	temp2->next=(t_elist *)malloc(sizeof(t_elist));
      }
	temp2=temp2->next;
      
    }
  }
}

read() {

	FILE* fptr;
	int i;
	/* initial the graphs */
	for (i=0; i <SIZE; i++) {
		graph[i].vno = i+1;
		graph[i].ecount = 0;
		graph[i].edges = NULL;

		graph_inv[i].vno = i+1;
		graph_inv[i].ecount = 0;
		graph_inv[i].edges = NULL;

		graph_new[i].vno = i+1;
		graph_new[i].ecount = 0;
		graph_new[i].edges = NULL;
	}

	/* Populate the graph */

	fptr=fopen("a.txt", "r");
	int vcurrent = 0;
	int vread, eread;
	t_elist *temp;
	while (!feof(fptr)) {
		fscanf (fptr, " %d", &vread);
		fscanf (fptr, " %d\n", &eread);
		if (vread != vcurrent) { /*read a new node */
			temp = NULL;
			vcurrent = vread;
			(graph[vread-1]).edges=(t_elist*) malloc(sizeof(t_elist));
			temp = (graph[vread-1]).edges;
			(graph[vread-1]).edges->number = eread;
			graph[vread-1].ecount++;
		}
		else {
			temp->next = (t_elist*) malloc(sizeof(t_elist));
			temp->next->number = eread;
			graph[vread-1].ecount++;
			temp = temp->next;
		}
	}
}
print(t_node *input) {
  t_elist *temp;
  int i;
  for(i=0;i<SIZE;i++){
    temp=input[i].edges;
    printf("vno=%d  ecount=%d edges = ",input[i].vno,input[i].ecount);
    while(temp!=NULL){
      printf("%d, ",temp->number);
      temp=temp->next;
    }
  printf("\n");
  }
}


invert() {
  int i,a;
  t_elist *temp,*temp2;
  for(i=0;i<SIZE;i++) {
    temp=graph[i].edges;
    while(temp!=NULL) {
      a=temp->number;
      temp2=graph_inv[a-1].edges;
      if(temp2!=NULL) {
	while(temp2->next!=NULL) {
	  temp2=temp2->next;
	}
        temp2->next=(t_elist *)malloc(sizeof(t_elist));
	temp2=temp2->next;
        temp2->number=graph[i].vno;
	temp2->next=NULL;
      }
      else {
	graph_inv[a-1].edges=(t_elist *)malloc(sizeof(t_elist));
	graph_inv[a-1].edges->number=graph[i].vno;
	graph_inv[a-1].edges->next=NULL;
      }
      temp=temp->next;
      graph_inv[a-1].ecount++;
    }
  }  
}

int notexplored(int target) {
  return (!explored[target-1]); 
}
loopdfs(t_node *g) {
  int i;
  for(i=0;i<SIZE;i++) {
    explored[i]=0;
  }
  for(i=SIZE;i>0;i--) {
    if(notexplored(i)) {
      s=i;
      dfs(g,i);
    }
  }
}

dfs(t_node *g, int i) {
  explored[i-1]=1;
  leader[i-1]=s;
  int a;
  t_elist *tmp;
  tmp=g[i-1].edges;
  /* do {
    j=tmp->number;
    tmp=tmp->next;
    if(tmp==NULL) break;
    dfs(g,j);
 } while(1);
  */
  while(tmp!=NULL) {
    a=tmp->number;
    tmp=tmp->next;
    if(notexplored(a)){
      dfs(g,a);
    }
  }
  t++;
  time[i-1]=t;
  return;
}
