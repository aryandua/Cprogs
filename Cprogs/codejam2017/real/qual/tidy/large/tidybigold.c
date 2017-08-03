#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 6
//#define SIZE2 4
#define SIZE2 19
long long inp[SIZE];
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
    fscanf(fptr, "%lld",&inp[i]);
  }
}

int tidy() {
  int i;
  long long j;
  long long num;
  long long last_tidy[SIZE];
  FILE *fptr2;
  fptr2 = fopen("./output.txt", "w");
  for(i=0;i<SIZE;i++) {
    num = inp[i];
    printf("i=%d and num=%lld\n",i,num);
    for(j=num;j>=0;j--) {
      //if(j==123456788999999999)
      //printf("stop");
      if(j%10000000 == 1)
       printf("j=%lld\n",j);
      if(istidy(j)) {
	last_tidy[i] = j;
	break;
      }
    }
  }
  for(i=0;i<SIZE;i++)
    fprintf(fptr2, "Case #%d: %lld\n",i+1,last_tidy[i]);
}

int istidy(long long num) {
  int i;
  long long a,b,c,cprev,pa,pb;
  a = (num/pow(10,0));
  b = (num/pow(10,1));
  cprev = a - (b*10);
  for(i=1;i<SIZE2;i++) {
    pa = pow(10,i);
    pb = pow(10,i+1);
    a = (num/pa);
    b = (num/pb);
    c = a - (b*10);
    if(c > cprev) 
      return 0;
    cprev = c;
  }
  return 1;
}
