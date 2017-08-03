#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 5
int inp[SIZE];
int main() {
  read_it();
  tidy();
}
int read_it() {
  FILE *fptr;
  fptr = fopen("./a.txt", "r");
  int i,sc;
  fscanf(fptr, "%d",&sc);
  if(sc != SIZE) {
    printf("ERROR");
    exit(1);
  }
  for(i=0;i<SIZE;i++) {
    fscanf(fptr, "%d",&inp[i]);
  }
}

int tidy() {
  int i,j;
  int last_tidy[SIZE];
  FILE *fptr2;
  fptr2 = fopen("./output.txt", "w");
  //for loop for all input (i)
       //for loop for all numbers till inp[i] (j)
            //check if j is tidy
                //last_tidy[i] = j
  for(i=0;i<SIZE;i++) {
    printf("%d\n",i+1);
    for(j=0;j<inp[i]+1;j++) {
      if(istidy(j)) {
	last_tidy[i] = j;
      }
    }
  }
  for(i=0;i<SIZE;i++)
    fprintf(fptr2, "Case #%d: %d\n",i+1,last_tidy[i]);
}

int istidy(int s) {
  int i;
  int arr[1000];
  getdigits(s, arr, 1000);
  for(i=0;i<floor(log10(abs(s)));i++) {
    if(arr[i] > arr[i+1])
      return 0;
  }
  return 1;
}
