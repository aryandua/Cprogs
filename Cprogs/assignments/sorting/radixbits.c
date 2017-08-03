#include <stdio.h> 
#include <math.h>

// define SIZE 
// define NO_OF_PARTS
// ^^ from command line gcc -D 


#define PARTS_SIZE 32/NO_OF_PARTS
#define pwrtwo(x) 1 << x 
#define BUCKETSIZE (pwrtwo(PARTS_SIZE))
#define MASK (BUCKETSIZE-1)

int buckets[BUCKETSIZE][SIZE];
int bucketcount[BUCKETSIZE];
int arr[SIZE];

int main(int argc, char *argv[]) {
  int i;
  FILE *fptr;
  fptr = fopen(argv[1], "r");
  fileread(fptr);
  radixsort();
  // for(i=0;i<SIZE;i++)  
  //printf("%d\n",arr[i]); 
}


int fileread(FILE *fptr) {
  int i;
  for(i=0;i<SIZE;i++) 
    fscanf(fptr, "%d\n",&arr[i]);
}

int radixsort() {
  int i, a,count,k,j;
  for(i=0;i<NO_OF_PARTS;i++) {
    
    for(j=0;j<SIZE;j++) 
      bucketcount[j]=0;
    
    for(j=0;j<BUCKETSIZE;j++) {
      for(k=0;k<SIZE;k++)
	buckets[j][k]=0;
    }
    
    for(j=0;j<SIZE;j++) {
      a=getpart(arr[j],i+1);
      printf("%d:%d\n",arr[j],a);
      buckets[a][bucketcount[a]] = arr[j];
      bucketcount[a]++;
    }

    count=0;

    for(j=0;j<BUCKETSIZE;j++) {
      for(k=0;k<SIZE;k++) {
	if(buckets[j][k]!=0) {
	  arr[count] = buckets[j][k];
	  count++;
	}
      }
    }
  }
  return 0;
}

int getpart(int num, int part) {
return (num >> (part*PARTS_SIZE)) & (MASK); 
}

