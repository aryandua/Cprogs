#include <stdio.h>
#include <stdlib.h>
#define T 100
#define R 25
#define C 25

char arr[R][C];

int main() {
  read_it();
}

int read_it() {
  int i,rows,cols,j,k,check;
  FILE *fptr,*fptr2;
  char junk;
  fptr = fopen("./a.txt", "r");
  fptr2 = fopen("./output.txt", "w");
  fscanf(fptr, "%d",&check);
  if(check != T) {
    printf("ERROR\n");
    exit(1);
  }
  for(i=0;i<T;i++) {
    fscanf(fptr, "%d",&rows);
    fscanf(fptr, "%d\n",&cols);
    for(j=0;j<rows;j++) {
      for(k=0;k<cols;k++) {
       fscanf(fptr, "%c",&arr[j][k]);
      }
      fscanf(fptr, "%c",&junk);
    }
    calans(rows, cols);
    fprintf(fptr2, "Case #%d:\n",i+1);
    for(j=0;j<rows;j++) {
     for(k=0;k<cols;k++) {
      fprintf(fptr2, "%c",arr[j][k]);
     }
     fprintf(fptr2, "\n");
    }
  }
}

int calans(int rows, int cols) {
  int i,j,k,l,first;
  char tmp = '?';
  int findveryfirst = 1;
  int firstrealrow = rows;
  for(i=0;i<rows;i++) {
    tmp = '?';
    first = 1;
    for(j=0;j<cols;j++) {
      if(arr[i][j] != '?') {
	tmp = arr[i][j];
	if(findveryfirst) {
	  firstrealrow = i;
	  findveryfirst = 0;
	}
	if(first) {
	  for(l=j;l>=0;l--) {
	    arr[i][l] = tmp;
	  }
	  first = 0;
	}
      }
      else {
	arr[i][j] = tmp;
      }
    }
    if(first) {
      if(findveryfirst == 0) {
	for(l=0;l<cols;l++)
	  arr[i][l] = arr[i-1][l];
      }
      
    }
  }
  for(i=0;i<firstrealrow;i++) {
    for(j=0;j<cols;j++) {
      arr[i][j] = arr[firstrealrow][j];
    }
  }
}
