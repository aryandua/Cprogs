#include <stdio.h>
#define SIZE 100
int main() {
  FILE *fptr;
  FILE *fptr2;
  fptr = fopen("./a.txt", "r");
  fptr2 = fopen("./b.txt", "w");
  int i,x,y;
  fscanf(fptr, "%d",&x);
  fprintf(fptr2, "%d\n",x*1000);
  for(i=0;i<SIZE;i++) {
    fscanf(fptr, "%d %d",&x,&y);
    x*=1000;
    y*=1000;
    fprintf(fptr2,"%d %d\n",x,y);
  }
}
