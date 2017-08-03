#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define T 100
int main() {
  read_it();
}

int read_it() {
  FILE *fptr;
  FILE *fptr2;
  fptr2 = fopen("./output.txt", "w");
  fptr = fopen("./a.txt", "r");
  int i,n,k,check;
  fscanf(fptr, "%d",&check);
  if(check != T) {
    printf("ERROR\n");
    exit(1);
  }
  for(i=0;i<T;i++) {
    fscanf(fptr, "%d", &n);
    fscanf(fptr, "%d", &k);
    if(k>n) {
      printf("ERROR k greater than n\n");
    }
    stall(n,k,i,fptr2);
  }
}
int stall(int n, int k, int casenum, FILE *fptr2) {
  int a,b,c;
  a = log2(k);
  b = pow(2, a);
  c = n/(2*b);
  fprintf(fptr2, "Case #%d: %d %d\n",casenum+1,c,c-1);
}
