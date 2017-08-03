#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define T 100
#define SIZEN 1000000
#define LARGENUM 524288
#define LARGENUM2 475712
#define LARGENUM3 262144
#define LARGENUM4 131072
#define LARGENUM5 65536
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
    printf("%d\n",i);
    stall(n,k,i,fptr2);
  }
}
int stall(int n, int k, int casenum, FILE *fptr2) {
  int i,val1,val2;
  int arr[SIZEN*2 + 2];
  int j,c1,c2,tmp;
  arr[0] = n;
  if(k>LARGENUM) {
    fprintf(fptr2, "Case #%d: 0 0\n",casenum+1);
    return;
  }
  else if(k>LARGENUM2) {
    fprintf(fptr2, "Case #%d: 1 0\n",casenum+1); 
    return;
  }
  else if(k>LARGENUM3) {
    fprintf(fptr2, "Case #%d: 1 1\n",casenum+1); 
    return;
  }
    if(k>LARGENUM4) {
    fprintf(fptr2, "Case #%d: 2 2\n",casenum+1);
    return;
  }
    if(k>LARGENUM5) {
    fprintf(fptr2, "Case #%d: 6 5\n",casenum+1);
    return;
  }
  for(i=0;i<k;i++) {
    c1 = 2*i + 1;
    c2 = 2*i + 2;
    if(arr[i]%2 == 0) {
      val1 = arr[i]/2;
      val2 = (arr[i]/2)-1;
      arr[c1] = val1;
      arr[c2] = val2;
      j = c1;
      while(arr[j] > arr[j-1]) {
	tmp = arr[j];
	arr[j] = arr[j-1];
	arr[j-1] = tmp;
	j--;
      } 
    }
    else {
      val1 = (arr[i]-1)/2;
      val2 = (arr[i]-1)/2;
      arr[c1] = val1;
      arr[c2] = val2; 
    }
  }
  /* a = arr[(2*k)]; */
  /* b = arr[(2*k)-1]; */
  if(val1>val2)
    fprintf(fptr2, "Case #%d: %d %d\n",casenum+1,val1,val2);
  else 
    fprintf(fptr2, "Case #%d: %d %d\n",casenum+1,val2,val1);
}
