#include <stdio.h>
#include <math.h>
#define SIZE 100 
int orig_inp[SIZE];
int inp[SIZE];
int out[SIZE];
int done[SIZE][10];
main() {
  read();
  sheep();
}
read() {
  int i;
  FILE *fptr;
  fptr = fopen("./a.txt", "r");
  for(i=0;i<SIZE;i++) {
    fscanf(fptr, "%d",&orig_inp[i]);
    inp[i] = orig_inp[i];
  }
}

sheep() {
  int i,k,j;
  FILE *fptr2;
  fptr2 = fopen("./output.txt", "w");
  for(i=0;i<SIZE;i++) {
    printf("%d\n",i);
    int alldone = 0;
    int count = 1;
    if(inp[i] == 0)
      out[i] = -1;
    else if(inp[i]!=0) {
      while(!alldone) {
	int arr[10];
	inp[i]=((orig_inp[i])*count);
	getdigits(inp[i], arr, 10);
	for(j=0;j<floor(log10(abs(inp[i])) + 1);j++) {
	  k = arr[j];
	  done[i][k] = 1;
	  out[i] = inp[i];
	}
	alldone = 1;
	for(j=0;j<10;j++) {
	  if(done[i][j] != 1)
	    alldone = 0;
	}
	count++;
      }
    }
  }
  for(i=0;i<SIZE;i++) {
	if(out[i] == -1) 
	  fprintf(fptr2,"Case #%d: INSOMNIA\n",i+1);
      else 
	fprintf(fptr2,"Case #%d: %d\n",i+1,out[i]);
  }
}
