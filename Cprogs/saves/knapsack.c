#include <stdio.h>
#define W 10000
#define N 100
int main() {
  FILE *fptr;
//  printf ("a is %d\n",sizeof(a));

  static int a[2][W];
  fptr = fopen("./a.txt", "r");
  int weights[N];
  int value[N];
  int i,x;
  int j;

  for(i=0;i<N;i++) {
    fscanf(fptr, "%d",&value[i]);
    fscanf(fptr, "%d\n",&weights[i]);
  }
  
  for(x=0;x<W;x++) 
    a[0][x] = 0;

  for(i=1;i<N;i++) {
    for(x=0;x<W;x++) {
      if(x-weights[i] > 0) 
	a[1][x] = (max(a[0][x], ((a[0][x-weights[i]]) + value[i])));
      else 
	a[1][x] = a[0][x];
    }
    for(j=0;j<W;j++)  {
      a[0][j] = a[1][j];
      a[1][j]= 0;
    }
  }
  
  printf("%d\n", a[0][x-1]);
}

int max(int a, int b) {
  if(a>b) 
    return a;
  else 
    return b;
}
