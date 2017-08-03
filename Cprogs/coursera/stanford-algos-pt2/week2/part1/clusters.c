#include <stdio.h>
#include <stdlib.h>
#define SIZE 500
#define K1 4
struct p {
  int clusternum;
  int edge_cost[SIZE];
};
typedef struct p p_t;
p_t points[SIZE];
int main() {
  init();
  readfile();
  cluster();
  return 0;
}
int init() {
  int i;
  for(i=0;i<SIZE;i++) {
    points[i].clusternum = i+1;
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
    points[node1-1].edge_cost[node2-1] = length;
    points[node2-1].edge_cost[node1-1] = length;
  }
}
int cluster() {
  int a, i,j,k, temp;
  int uniq_clusters = SIZE;
  int prev = SIZE;
  int min,vmin1,vmin2;
  int xx[SIZE];

  for (k = SIZE; k > K1-1; k--) {
//    while (uniq_clusters > 4) {

    for(i=0;i<SIZE;i++)
      xx[i] = 0;
    min=100000;

    for(i=0;i<SIZE;i++) {
      for(j=0;j<SIZE-1;j++) {
	if(points[i].edge_cost[j] < min /* && points[i].edge_cost[j] != 0*/ && points[i].clusternum != points[j].clusternum) {
	  min=points[i].edge_cost[j];
	  vmin1 = i+1;
	  vmin2 = j+1;
	}
      }
    }
    //for(i=0;i<SIZE;i++) {
      //printf (" %d  = %d, ", i+1,points[i].clusternum);
    //   if (i%10 == 0)
        //printf ("\n");
    // }
    //printf ("\n"); 

    printf("merging %d and %d with length %d\n",vmin1,vmin2,min);
    //  printf("vmin1.cluster = %d, vmin1.cluster = %d \n",points[vmin1-1].clusternum, points[vmin2-1].clusternum);
    temp = points[vmin2-1].clusternum;
    for(a=0;a<SIZE;a++) {
      if(points[a].clusternum == temp) {
//	printf("points[%d].clusternum = %d, ",a,points[a].clusternum);
	points[a].clusternum = points[vmin1-1].clusternum;
	points[a].edge_cost[vmin1-1] = 0;
	points[vmin1-1].edge_cost[a] = 0;
      }
    }
    
    for(a=0;a<SIZE;a++) {
     xx[(points[a].clusternum) - 1] = 1;
    }
    prev = uniq_clusters;
    uniq_clusters = 0;
    for(a=0;a<SIZE;a++) {
	if (xx[a] == 1)
		uniq_clusters++;
    }
    printf ("Number of Cluster  = %d\n",uniq_clusters);
    if (prev != uniq_clusters + 1) {
	printf ("prev = %d, uniq_clusters = %d\n", prev, uniq_clusters);
	getchar();
    }
    //for(a=0;a<SIZE;a++) {
     //  printf ("%d, ",points[a].clusternum);
   // }
   // printf ("\n");
   // for(a=0;a<SIZE;a++)
    //  printf ("%d",xx[a]);
   // printf ("\n");
  }
  for(i=0;i<SIZE;i++) printf("%d, ",points[i].clusternum);
}
int merge(int i, int j) {
  points[i].edge_cost[j] = 0;
  points[j].edge_cost[i] = 0;
}
