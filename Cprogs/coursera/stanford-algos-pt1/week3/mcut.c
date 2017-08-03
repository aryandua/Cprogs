#include <stdio.h>
#include <stdlib.h>
#define COUNT 3
struct elist {
        int number;
        struct elist *next;
};
typedef struct elist t_elist;
 struct node {
	int vno;
	int ecount;
	struct elist *edges;
};
typedef struct node t_node;

int main() {
	t_node graph[COUNT];
	graph[0].vno=1;
	graph[0].ecount=2;
	graph[0].edges->number=2;
	graph[0].edges->next=NULL;
	graph[1].vno=2;
	graph[1].ecount=2;
	graph[1].edges->number=1;
	graph[1].edges->next=NULL;

	graph[2].vno=3;
	graph[2].ecount=2;
	graph[2].edges->number=1;
	graph[2].edges->next=NULL;

/*	FILE* fptr;
	fptr=fopen("graph.txt", "r");
	int i,j,x;
	char c;
	t_elist *temp;
	for(i=0;i<COUNT;i++) {
		fscanf(fptr, " %d",&graph[i].vno);
		(graph[i]).edges=(t_elist*) malloc(sizeof(t_elist));
		temp=(graph[i]).edges;
		fscanf(fptr, " %d",&temp->number);
		graph[i].ecount=1;
		c = fscanf (fptr, "%c", &c);
		while (c != '\n') {
			temp->next=malloc(sizeof(t_elist));
			fscanf(fptr, "%d",&temp->next->number);
			graph[i].ecount++;
			temp=temp->next;
			c = fscanf (fptr, "%c", &c);
		}
		temp->next=NULL;
	}*/
//	for(i=0;i<COUNT;i++)
		//printf ("v = %d , ecount = %d\n", graph[i].vno, graph[i].ecount);
combine(graph[0], graph[2]);
	return;
}

combine(t_node n1, t_node n2) {
	while(n1.edges->next!=NULL) {
	n1.edges=n1.edges->next;
	}
	n1.edges->next=n2.edges;
	n1.ecount+=n2.ecount;
	n2.vno=0;
	return;
}

