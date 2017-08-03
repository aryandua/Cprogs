#include <stdio.h>
#include <stdlib.h>
//#define SIZE 9
//use -D
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

int main(int argc, char *argv[]) {
  FILE *fptr=fopen(argv[1], "r");
  if(argc==1 || argc > 2) {
    printf("Usage: rad <filename>\n");
    exit(1);
  }
  readthefile(fptr);
  invert();
  loopdfs(graph_inv);
  print_time();
  gnew();
  loopdfs(graph_new);
  print_all();
  print_max();
}
print_max() {
  int max=0,max2=0,max3=0,max4=0,max5;
  int read;
  int i;
  int arr[SIZE];
  for(i=0;i<SIZE;i++) {
    arr[i]=0;
  }
  for(i=0;i<SIZE;i++) {
    read=leader[i];
    arr[read-1]++;
  }
  for(i=0;i<SIZE;i++) { 
   read = arr[i];
   if(read>max) {
     max5=max4;
     max4=max3;
     max3=max2;
     max2=max;
     max=read;
   }
   else if(read>max2) {
     max5=max4;
     max4=max3;
     max3=max2;
     max2=read;
   }
   else if(read>max3) {
     max5=max4;
     max4=max3;
     max3=read;
   }
   else if(read>max4) {
     max5=max4;
     max4=read;
   }
   else if(read>max5) {
     max5=read;
   }
  }
 printf("\nmax = %d,  max2 = %d, max3 = %d, max4 = %d, max5 = %d\n",max,max2,max3,max4,max5);
}

print_time() {
   printf("time : ");
  int i;
  for(i=0;i<SIZE;i++) {
    printf("%d ,",time[i]);
  }
  printf("\n");
 }
print_all() {
  int i;
  printf("graph=\n");
  print(graph);
  printf("\n");
  printf("graph_inv\n");
  print(graph_inv);
  printf("\n");
  printf("graph_new: \n");
  print(graph_new);
  printf("leader: ");
 for(i=0;i<SIZE;i++) {
    printf("%d ,",leader[i]);
  }
 printf("\n");
     
}
gnew() {
  int i,e,j;
  t_elist *temp,*temp2;
  for(i=0;i<SIZE;i++) {
    j=time[i];
    graph_new[j-1].edges=(t_elist *)malloc(sizeof(t_elist));
    graph_new[j-1].vno=time[i];
    graph_new[j-1].ecount=graph[i].ecount;
    temp2=graph_new[j-1].edges;
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

readthefile(FILE *fptr) {

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
  for(i=0;i<SIZE;i++){
    leader[i]=0;
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
  while(tmp!=NULL) {
    a=tmp->number;
    
    if(notexplored(a)){
      dfs(g,a);
      
    }
    tmp=tmp->next;
  }
  t++;
  time[i-1]=t;
  return;
}