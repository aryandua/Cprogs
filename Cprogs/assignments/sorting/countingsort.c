#include <stdio.h>

//define SIZE and MAX from command line using -D in gcc
//also pass a file using argv


int list[SIZE];

int main(int argc, char *argv[]) {
  FILE *fptr;
  fptr = fopen(argv[1], "r");
  fileread(fptr);
  countsort(list);
  /* int i; */
  /* for(i=0;i<SIZE;i++) { */
  /*   printf("%d\n",list[i]); */
  /* } */
  return 0;
}
int fileread(FILE *fptr) {
  int i;
  for(i=0;i<SIZE;i++) {
    fscanf(fptr,"%d\n",&list[i]);
  }
}

int countsort(int *list) {
    int count[MAX+1];
    int final[SIZE];
    int i; 
    for(i=0;i<MAX+1;i++)
        count[i]=0;
    for(i=0;i<SIZE;i++) 
        count[list[i]]++;
    for(i=1;i<MAX+1;i++)
        count[i]+=count[i-1];
    for(i=0;i<SIZE;i++) {
        final[count[list[i]]-1] = list[i];
        count[list[i]]--;   
    }
   for(i=0;i<SIZE;i++)
     list[i]=final[i];
}


