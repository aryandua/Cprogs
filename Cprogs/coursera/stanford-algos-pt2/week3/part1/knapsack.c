#include <stdio.h>
#include <stdlib.h>


int main() {
  
  int n,W;
  FILE *fptr;
  fptr = fopen("a.txt", "r");
  fscanf(fptr, "%d",&W);
  fscanf(fptr, "%d",&n);

  int weights[n];
  int value[n];
  int i,x;
  int A[n][W];

  for(i=0;i<n;i++) {
    fscanf(fptr, "%d",&value[i]);
    fscanf(fptr, "%d\n",&weights[i]);
  }
  
  for(x=0;x<W;x++) 
    A[0][x] = 0;

  for(i=1;i<n;i++) {
    for(x=0;x<W;x++) {
       if(x-weights[i] > 0) 
	A[i][x] = (max(A[i-1][x], ((A[i-1][x-weights[i]]) + value[i])));
       else 
	A[i][x] = A[i-1][x];
    }
  }
  /*for(i=0;i<n;i++) {
    for(x=0;x<W;x++) {
       printf("%d, ",A[i][x]);
    }
    printf("\n");
  }
  */
  printf("%d\n", A[i-1][x-1]);
}

int max(int a, int b) {
  if(a>b) 
    return a;
  else 
    return b;
}
