#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COUNT 200
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

void combine(t_node *n1, t_node *n2);

t_node graph[COUNT];

int main() {

	FILE* fptr;
	fptr=fopen("graph.txt", "r");
	int i,j,x;
	char c;
	t_elist *temp;
	for(i=0;i<COUNT;i++) {
		fscanf(fptr, " %d",&graph[i].vno);
		graph[i].ecount=0;
		(graph[i]).edges=(t_elist*) malloc(sizeof(t_elist));
		temp=(graph[i]).edges;

		fscanf(fptr, " %d",&x);
		temp->number = x;
		graph[i].ecount++;
		fscanf (fptr, " %d", &x);
		while (x != -100) {
			temp->next=malloc(sizeof(t_elist));
			graph[i].ecount++;
			temp->next->number = x;
			temp=temp->next;
			fscanf (fptr, " %d", &x);
		} 
		temp->next=NULL;
	}
//	for(i=0;i<COUNT;i++)
//		printf ("v = %d , ecount = %d\n", graph[i].vno, graph[i].ecount);
	int loop = 0;

	int track[COUNT];
	int vertex_remaining = COUNT;
	time_t t;

	for (loop = 0 ; loop < COUNT; loop++)
		track[loop] = 0;

	srand ((unsigned)time(&t));
	while (vertex_remaining > 2) {
		i = rand() % 200;
		if (track[i] != 1) {
			j = graph[i].edges->number;
//			printf ("Vertex remaining = %d\n", vertex_remaining);
			combine(&graph[i], &graph[j-1]);
			track[j-1] = 1;
			vertex_remaining--;
		}
		else {
//			printf ("vertex %d is already combined\n",i);
		}
	}

	for (i = 0 ; i < COUNT; i++) {
		if(track[i] == 0) {
			printf ("v = %d , ecount = %d\n", graph[i].vno, graph[i].ecount);
		}
	}
	printf ("---\n");
/*
	for(i=0;i<COUNT;i++) {
		printf ("v = %d , ecount = %d\n", graph[i].vno, graph[i].ecount);
		temp = graph[i].edges;
		printf ("  edges = ");
		while (temp != NULL) {
			printf (" %d, ",temp->number);
			temp = temp->next;
		}
		printf ("\n");
	}
*/
	return;
}


/*
This function :
	combines n1 and n2 into n1.
	remove any self loops
	update the list of n2 edges to now point to n1 instead of n2
	nullifies n2 node after it has been combined into n1
*/
void combine(t_node *n1, t_node *n2) {
	t_elist *temp, *delnode, *temp2;
//	printf ("Combining %d and %d\n",n1->vno, n2->vno);

	/* Go to the end of n1 edges list and append n2 edge list to it */
	temp = n1->edges;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=n2->edges;
	while ((n2->edges != NULL) && (n2->edges->number == n1->vno)) {
	/* This will get deleted during self loop removal
	   and then when we do the update of n2 edge list to point n2 to n1
	   will crash. So, let's take care of it now */
		n2->edges = n2->edges->next;
	}

	n1->ecount+=n2->ecount; // increment the count of combined node

	/* remove self loops
	  i.e. get rid of edge whose number is vno of n1 & n2. */
	temp = n1->edges;
	while((temp->number ==n1->vno) || (temp->number == n2->vno)) {
		delnode = n1->edges;
		n1->edges = temp->next;
		n1->ecount--; //decrement the count
		free (delnode);
		temp = temp->next;
	}
	while (temp->next != NULL) {
		if((temp->next->number == n1->vno) || (temp->next->number == n2->vno)) {
			delnode = temp->next;
			temp->next = temp->next->next;
			free (delnode);
			n1->ecount--; //decrement the count
		}	
		else
			temp=temp->next;
	}

	/* update the list of n2 edges to now point to n1 instead of n2 */
	temp = n2->edges;
	while (temp != NULL) {
		int i;
		i = temp->number;
		if (i == n1->vno)
			continue;
		temp2 = graph[i-1].edges;
		while (temp2->number != n2->vno)
			temp2 = temp2->next;
		temp2->number = n1->vno;
	
		temp = temp->next;
	}
	
	/* Finally, nullify the n2 node that is now combined into n1 */
//	n2->vno=0;
	n2->ecount = 0;
	n2->edges = NULL; /*ideally free it */

	return;
}

