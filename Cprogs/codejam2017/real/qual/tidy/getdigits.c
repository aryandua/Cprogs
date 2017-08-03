#include <stdio.h>
#include <math.h>

getdigits(int num, int *ptr, int numofdigits) {
  int i;
  int a,b,c;
  for(i=0;i<numofdigits;i++) {
    a = (num/pow(10,i));
    b = (num/pow(10,i+1));
    c = a - (b*10);
    ptr[i] = c;
  }
}
