#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 5
//#define SIZE2 4
#define SIZE2 19
long long gettidy(long long num);
long long inp[SIZE];
long long arr[SIZE2];
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
    last_tidy[i] = gettidy(inp[i]);
  }
  for(i=0;i<SIZE;i++)
    fprintf(fptr2, "Case #%d: %lld\n",i+1,last_tidy[i]);
}

long long gettidy(long long num) {
  long long i,l,ans,pa,pb,a,tsi,tl;
  int went = 0,nottidy=0;
  ans = num;
  for(l=0;l<SIZE2;l++) 
    arr[l] = 0;
  getdigits(num);
  for(l=0;l<SIZE2-1;l++) {
    if(arr[l] > arr[l+1]) 
      nottidy = 1;
  }
  if(nottidy == 0) 
    return num;
  for(l=0;l<SIZE2-1;l++) {
    if(arr[l] > arr[l+1]) {
      i=l+1;
      went = 1;
      break;
    }
  }
  if(went) {
    tsi = pow(10,SIZE2-i);
    a = (num/tsi-1);
    a = gettidy(a);
    a*=tsi;
    for(l=0;l<SIZE2-i;l++) {
      tl = pow(10,l);
      a += 9*tl;
    }
    ans = a;
  }
  return ans;
}


getdigits(long long num) {
  int i;
  long long a,b,c,pa,pb;
  for(i=0;i<SIZE2;i++) {
    pa = pow(10,i);
    pb = pow(10,i+1);
    a = (num/pa);
    b = (num/pb);
    c = a - (b*10);
    arr[SIZE2-(i+1)] = c;
  }
}
