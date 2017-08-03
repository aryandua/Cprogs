#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define BTS 4
int found[SIZE];
int foundcount;
int clusternum[SIZE];

int main() {
  int points[SIZE];
  int clustercount = 0;
  int clusterloopcount = 0;
  FILE *fptr;
  fptr = fopen("a.txt", "r");
  int i,j,k,readbit,loopstop, printon;

  //initializing loop  
  for(i=0;i<SIZE;i++) {
    points[i] = 0;
    clusternum[i] = 0;
    found[i] = 0;
  }

  for(i = 0; i < SIZE; i++) {
    if (i % 5000 < 20)
      printon = 1;
    else
      printon = 0;

    char str[20];
    sprintf(str, "./mydir/%d.txt",i+1);
    FILE *fptemp;
    if(printon)
      fptemp = fopen(str, "w");
    
    for(j=0;j<SIZE;j++) 
          found[j] = 0;
 
    points[i] = 0;
    foundcount = 0;

    /* read the next line of bitstream and store as type int (1) */
    for(j = 0; j < BTS; j++) { 
      fscanf(fptr, "%d",&readbit);
      points[i] = points[i] << 1 | readbit;
    }
    if(printon)
      fprintf(fptemp, "Read = %d\n",points[i]);
    for(k = 0;k < i;k++) {
      if(issamecluster(points[i],points[k])) { 
	if(isnewfound(clusternum[k])) {

	  if(foundcount == 0) 
	    clusternum[i] = clusternum[k];
	  found[foundcount] = k;
	  foundcount++;
	}
      }
    }

    if(printon)  {
      fprintf(fptemp, "foundcount: %d\n",foundcount);
      fprintf(fptemp, "What I have found: ");
      for(k=0;k<foundcount;k++) {
	fprintf(fptemp, "%d, ",points[found[k]]);
      }
      fprintf(fptemp, "\n");

      fprintf(fptemp, "What I have found's cnum (before loops change): ");
      for(k=0;k<foundcount;k++) {
	fprintf(fptemp, "%d, ",clusternum[found[k]]);
      }
      fprintf(fptemp, "\n");
      
    }
    if(foundcount == 0) { 
      clustercount++;
      clusterloopcount++;
      clusternum[i] = clusterloopcount;
    }

    //(3b)
    else {
      for (k = 0; k < i; k++) { 
	int tempk = clusternum[k];
		for (j = 0 ; j < foundcount; j++) {
		  int tempj = clusternum[found[j]];
			if (tempk == tempj)
			  clusternum[k] = clusternum[found[0]];
		}
	}

	clustercount = ((clustercount-foundcount)+1);
    }

    for(k=0;k<foundcount;k++) {
      clusternum[found[k]] = clusternum[found[0]];
    }
    if(printon) {
      fprintf(fptemp, "Cnum of points[i] = %d\n",clusternum[i]);
      fprintf(fptemp, "What I have found's cnum after loops change): ");
      for(k=0;k<foundcount;k++) {
	fprintf(fptemp, "%d, ",clusternum[found[k]]);
      }
      fprintf(fptemp, "\n");
      fprintf(fptemp, "clustercount: %d\n",clustercount);
      fprintf(fptemp, "clusterloopcount: %d\n",clusterloopcount);
      fprintf(fptemp, "lines read: %d\n",i+1);
      fprintf(fptemp, "clusternum: \n");  
      for(k=0;k<SIZE;k++) 
	fprintf(fptemp, "%d\n",clusternum[k]);
    }
    // if(i%30000 == 0)  
    // printf("lines read = %d, clusters made = %d \n",i+1,clustercount);
    if(printon) 
      fclose(fptemp);
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
