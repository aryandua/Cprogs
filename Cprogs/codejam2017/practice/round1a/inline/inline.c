#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define T 50
#define SIZEN 10
#define RINP ((SIZEN * 2) - 1)
#define CINP SIZEN
#define RC RINP*CINP
int main() {
  read_it();
}

int read_it() {
  int i,j,n,s;
  int rtc;
  int val[RC];
  int odd[RC];
  int ans[CINP];
  int anscount = 0;
  FILE *fptr;
  fptr = fopen("./a.txt", "r");
  FILE *fptr2;
  fptr2 = fopen("./output.txt", "w");
  int check;
  fscanf(fptr, "%d", &check);
  if(check != T) {
    printf("ERROR\n");
    exit(1);
  }
  for(i=0;i<T;i++) {
    anscount = 0;
    fscanf(fptr, "%d",&n);
    rtc = n*((n*2)-1);
    for(j=0;j<rtc;j++) 
      odd[j] = 0;
    for(j=0;j<(rtc);j++) {
      fscanf(fptr, "%d",&val[j]);
      odd[(val[j]-1)] = !odd[val[j]-1];
    }
    for(j=0;j<(rtc);j++) {
      if(odd[j]) {
	ans[anscount] =j+1;
	anscount++;
      }
    }
    divide_sort (ans,n);
    fprintf(fptr2, "Case #%d: ",i+1);
    for(j=0;j<n;j++) {
      fprintf(fptr2, "%d ",ans[j]);
    }
    fprintf(fptr2,"\n");
  }
}

int divide_sort(int *arr,int n) {
        int *left=arr;
        int *right=arr+n/2;
        int k=0;
        int i=0;
        int j=0;
	int count, n1, n2;
	int newarr[n];

        if(n==1) return;

	n1 = n/2;
	n2 = n - n1;
	
        divide_sort(left,n1);
        divide_sort(right,n2);

        while  ( k < n ) {
                if (left[i] > right[j]) {
			newarr[k] = right[j];
			j++;
			k++;
			if (j >= n2) {
				for (count = i; count < n1; count++) {
					newarr[k] = left[i];
					i++;
					k++;
				}
			}
		}
		else {
			newarr[k]=left[i];
			i++;
			k++;
			if (i >= n1) {
				for (count = j; count < n2; count++) {
					newarr[k] = right[j];
					j++;
					k++;
				}
			}
		}
	}
        for(count=0;count<n;count++) {
		arr[count] = newarr[count];
        }
}
