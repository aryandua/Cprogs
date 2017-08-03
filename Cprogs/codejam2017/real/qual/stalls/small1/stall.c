#include <stdio.h>
#include <stdlib.h>
#define T 100
#define SIZEN 1000
int main() {
  read_it();
}

int read_it() {
  FILE *fptr;
  FILE *fptr2;
  fptr2 = fopen("./output.txt", "w");
  fptr = fopen("./a.txt", "r");
  int i,n,k,check;
  fscanf(fptr, "%d",&check);
  if(check != T) {
    printf("ERROR\n");
    exit(1);
  }
  for(i=0;i<T;i++) {
    fscanf(fptr, "%d", &n);
    fscanf(fptr, "%d", &k);
    if(n>SIZEN) {
      printf("ERROR NOT SUPPORTED FOR %d\n",n);
      exit(1);
    }
    if(k>n) {
      printf("ERROR k greater than n\n");
    }
    stall(n,k,i,fptr2);
  }
}

int stall(int n, int k, int casenum, FILE *fptr2) {
  int L[SIZEN+2];
  int R[SIZEN+2];
  int min[SIZEN+2];
  int max[SIZEN+2];
  int occupied[SIZEN+2];
  int i,j,wval,wi,l,r;
  occupied[0] = 1;
  for(j=1;j<=n;j++)
    occupied[j] = 0;
  for(j = (n+1);j<=SIZEN+1;j++) 
    occupied[j] = 1;

  for(j=0;j<k;j++) {
    calculate(L,R,min,max,occupied,n);
    wval = -100;
    for(i=0;i<(n+2);i++) {
      if(occupied[i] == 0) { 
	if(min[i] > wval) {
	  wi = i;
	  wval = min[i];
	}
	else if(min[i] == wval) {
	  if(max[i] > max[wi]) {
	    wi = i;
	  }
	}
      }
    }
    occupied[wi] = 1;
  }
  int d=0;
  l=0;
  r=0;
  for(i=wi-1;i>=0;i--) {
    if(occupied[i] == 1) {
      break;
    }
    else {
      l++;
    }
  }
  for(i=wi+1;i<=(n+2);i++) {
    if(occupied[i] == 1) {
      break;
    }
    else {
      r++;
    }
  }  
  if(l>r)
    fprintf(fptr2, "Case #%d: %d %d\n",casenum+1,l,r);
  else 
    fprintf(fptr2, "Case #%d: %d %d\n",casenum+1,r,l);
}

int calculate(int *l, int *r, int *min, int *max, int *occupied, int n) {
  int i,d=0;
  for(i=0;i<=(n+1);i++) {
    if(occupied[i] == 1) {
      d=0;
      l[i] = -100;
    }
    else {
      l[i] = d;
      d++;
    }
  }
  for(i=(n+1);i>=0;i--) {
    if(occupied[i] == 1) {
      d=0;
      r[i] = -100;
    }

    else {
      r[i] = d;
      d++;
      if(l[i] < r[i]) {
	min[i] = l[i];
	max[i] = r[i];
      }
      else {
	min[i] = r[i];
	max[i] = l[i];
      }
    }
  }
}
