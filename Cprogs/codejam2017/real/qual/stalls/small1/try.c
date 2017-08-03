#include <stdio.h>

int main() {
  FILE *fptr;
  fptr = fopen("./try.txt", "w");
  int i;
  fprintf(fptr, "100\n");
  for(i=1;i<=100;i++) {
    fprintf(fptr, "100 %d\n",i);
  }
}
