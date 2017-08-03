#include <stdio.h> 
#include <math.h>

// define SIZE 
// ^^ from command line gcc -D 

int buckets[256][SIZE];
int bucketcount[256];
int arr[SIZE];

int main(int argc, char *argv[]) {
  int i;
  FILE *fptr;
  fptr = fopen(argv[1], "r");
  fileread(fptr);
  radixsort();
  for(i=0;i<SIZE;i++) 
    printf("%d\n",arr[i]);
}


int fileread(FILE *fptr) {
  int i;
  for(i=0;i<SIZE;i++) 
    fscanf(fptr, "%d\n",&arr[i]);
}

int radixsort() {
  int i, a,count,k,j;

  for(i=0;i<4;i++) {

    for(j=0;j<SIZE;j++) 
      bucketcount[j]=0;

    for(j=0;j<256;j++) {
      for(k=0;k<SIZE;k++)
	buckets[j][k]=0;
    }

    for(j=0;j<SIZE;j++) {
      a=getpart(arr[j],i+1);
      buckets[a][bucketcount[a]] = arr[j];
      bucketcount[a]++;
    }

    count=0;

    for(j=0;j<256;j++) {
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
  int ret;
  if(part==1) 
    ret = num & 0xff;
  else if(part==2)
    ret = (num >> 8) & 0xff;
  else if(part==3) 
    ret = (num >> 16) & 0xff;
  else if(part==4)
    ret = (num >> 24) & 0xff;
  else 
    printf("Error\n");
 
  return ret;
}
