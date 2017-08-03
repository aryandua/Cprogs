#include <stdio.h>
#define SIZE 200000 
#define BTS 24
int found[SIZE];
int foundcount;
int clusternum[SIZE];

int main() {

  int points[SIZE];
  int clustercount = 0;
  int clusterloopcount = 0;
  FILE *fptr;
  fptr = fopen("a.txt", "r");
  int i,j,k,readbit,loopstop;

  //initializing loop  
  for(i=0;i<SIZE;i++) {
    points[i] = 0;
    clusternum[i] = 0;
    found[i] = 0;
  }

  //main loop iterates over all nodes, reads them (1), checks if it belongs to any of the number (2), if it doesn't then allocates new node (3a),  else does neccessary actions to merge points[i] with found node/cluster(3b).
  for(i = 0; i < SIZE; i++) {
    //inits found every time
    for(j=0;j<SIZE;j++) 
          found[j] = 0;
    //other inits
    points[i] = 0;
    foundcount = 0;

    /* read the next line of bitstream and store as type int (1) */
    for(j = 0; j < BTS; j++) { 
      fscanf(fptr, "%d",&readbit);
      points[i] = points[i] << 1 | readbit;
    }
    //checks if node points[i] is in the same cluster as any of the yet made clusters (2)
    for(k = 0;k < i;k++) {
      if(issamecluster(points[i],points[k])) { 
/* function issamecluster takes two integer values, xors them, and return 1 if they have 2 or less bits in common, else return 0 */
	if(isnewfound(clusternum[k])) {
 /* function isnewfound, takes one integer clusternum[k], and check if that number already is in array found. TO AVOID FINDING MATCHES OF POINTS[I] TO THE SAME CLUSTER*/
	  if(foundcount == 0) 
	    clusternum[i] = clusternum[k];
	  found[foundcount] = k;
	  //k is added to found, to avoid merging points[i] with the same cluster. Check previous comment for more details.
	  foundcount++;
	  //also this means that we have found a new match for points[i], which needs an increment to foundcount
	}
      }
    }
    // (3a)
    if(foundcount == 0) { /* this means NO MATCH WAS FOUND for points[i] (MAKE A NEW CLUSTER) */
      clustercount++;
      //increment clustercount, since a new cluster is being allocated 
      clusterloopcount++;
      //clusterloopcount is made because the cluster names were getting mixed up when subtracting clustercount w/ foundcount+1. So, we need a variable that doesn't get -foundcoun+1. but still ++ when foundcount==0
      clusternum[i] = clusterloopcount;
      //obvious as it seems, we give clusternum[i] the calue of clusterloopcount
    }

    //(3b)
    else {
      for (k = 0; k < i; k++) { /*iterate through every node and and every foundcount, and see if any pair matches. if it does then set the found one to clusternum[found[0]] which is what we are setting every node in found cluster and new node to */
		for (j = 0 ; j < foundcount; j++) {
		  //just doing what is said in above comment:
			if (clusternum[k] == clusternum[found[j]])
			clusternum[k] = clusternum[found[0]];
		}
	}
      /*if there is only 1 foundcount. clustercount remains same. Since, a new cluster is not being allcated but neither is there one cluster merged with another cluster (therefore the +1). else foundcount>2, we need to subtract clustercount by foundcount +1 because if fondcount==2 then only one cluster is being subtracted. NOT 2, ONE */
	clustercount = ((clustercount-foundcount)+1);
    }
    //iterate through all foundcounts, go to their clusternum and set them to clusternum[found[0]], which is what we decided we are gonna change everything to
    for(k=0;k<foundcount;k++) {
      clusternum[found[k]] = clusternum[found[0]];
    }
    // if(i%30000 == 0)  
    printf("lines read = %d, clusters made = %d \n",i+1,clustercount);
      /* if(clustercount==2 || clustercount==3) {
        printf("\n");
	for(k=0;k<SIZE;k++) 
	  printf("%d, ",clusternum[k]);
	// }
      //if(i%30000 == 0)  
      printf("\n");
      */
  }
  FILE *fp2;
  fp2 = fopen("./result.txt", "w");
  for(i=0;i<SIZE;i++) fprintf(fp2, "%d\n",clusternum[i]);
}

int issamecluster(int a, int b) {
  int bit,l;
  int xor = a ^ b;
  int count = 0;
  for(l=0;l<BTS;l++) {
    bit = (xor & (1 << l)) >> l;
    if(bit == 1) 
      count++;
    if(count > 2) 
      return 0;
  }  
  return 1;
}

int isnewfound(int a) {
  int i;
  for(i=0;i<foundcount;i++) {
    if(clusternum[found[i]] == a) {
      return 0;
    }
  }
  return 1;
}
