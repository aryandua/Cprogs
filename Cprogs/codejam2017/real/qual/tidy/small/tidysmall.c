#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 100
#define SIZE2 4
//#define SIZE2 19
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
  int i,j,num;
  int last_tidy[SIZE];
  FILE *fptr2;
  fptr2 = fopen("./output.txt", "w");
  //for loop for all input (i)
       //for loop for all numbers till inp[i] (j)
            //check if j is tidy
                //last_tidy[i] = j
  for(i=0;i<SIZE;i++) {
    num = inp[i];
    printf("i=%d and num=%d\n",i,num);
    for(j=num;j>=0;j--) {
      // printf("j=%d\n",j);
      if(istidy(j)) {
	last_tidy[i] = j;
	break;
      }
    }
  }
  for(i=0;i<SIZE;i++)
    fprintf(fptr2, "Case #%d: %d\n",i+1,last_tidy[i]);
}

int istidy(int num) {
  int i;
  int a,b,c,cprev;
  a = (num/pow(10,0));
  b = (num/pow(10,1));
  cprev = a - (b*10);
  for(i=1;i<SIZE2;i++) {
    a = (num/pow(10,i));
    b = (num/pow(10,i+1));
    c = a - (b*10);
    if(c > cprev) 
      return 0;
    cprev = c;
  }
  return 1;
}
