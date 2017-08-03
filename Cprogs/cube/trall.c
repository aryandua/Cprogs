#include <stdio.h>
#define SIZE 61917364224

int count,count1;
int main() {
  int i,j;
  count = 0;
  count1 = 0;
  for(i=0;i<SIZE;i++) {
    for(j=0;j<SIZE;j++) {

      if(cubesolved()) {
	
      }
      else {
	hi();
      }
    }
  }
}
int cubesolved() {
  count++;
  if(count % 1000000000 == 0) {
    count1++;
    printf("%d\n",count1);
  }
  return 0;
}

int hi() {
  return;
}
