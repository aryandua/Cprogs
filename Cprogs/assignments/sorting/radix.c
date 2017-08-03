#include <stdio.h> 
#include <math.h>

// define SIZE from command line gcc -D 

int buckets[10][SIZE];
int bucketcount[10];
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
  int i, digits,a,count,k,j;
  digits = getmaxdigits(arr);

  for(i=0;i<digits;i++) {
    for(j=0;j<SIZE;j++) 
      bucketcount[j]=0;
    for(j=0;j<10;j++) {
      for(k=0;k<SIZE;k++)
	buckets[j][k]=0;
    }
    for(j=0;j<SIZE;j++) {
      a=getdig(arr[j],i+1);
      buckets[a][bucketcount[a]] = arr[j];
      bucketcount[a]++;
    }

    count=0;

    for(j=0;j<10;j++) {
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

int getdig(int num, int digit) {
  int val=(num / pow(10, digit - 1));
  return val%10;
}


int getmaxdigits(int *arr) {
  int i,count,n,max=0;
  for(i=0;i<SIZE;i++) {
    n=arr[i];
    count=0;
    while(n != 0) {
      n/=10;
      count++;
    }
    if(count > max)
      max=count;
  }
  return max;
}
