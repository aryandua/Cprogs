#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define T 100
#define N 1000
//#define PI 3.14159265359
#define PI M_PI


long long h[N];
long long r[N];
long long rh[N];
long long rsort[N];

double ans;
int sizen,sizek;

int main(int argc, char *argv[]) {
  /* char inputFile[20]; */
  /* strcpy(inputFile, argv[1]); */
  FILE *fptr,*fptr2;
  fptr = fopen(argv[1], "r");
  fptr2 = fopen("./output.txt", "w");

  if(fptr == NULL) {
    printf("ERROR OPENING FILE\n");
    exit(1);
  }
  int i;
  int testcases;
  fscanf(fptr, "%d",&testcases);
  if(testcases != T) {
    printf("ERROR TEST CASES DID NOT MATCH\n");
    exit(1);
  }

  for(i=0;i<T;i++) {
    readtestcase(fptr,i);
    calans();
    print_ans(fptr2,i);
  }

}

int readtestcase(FILE *fptr) {
  int i;
  fscanf(fptr, "%d",&sizen);
  fscanf(fptr, "%d",&sizek);
  for(i=0;i<N;i++) {
    r[i] = 0;
    h[i] = 0;
    rh[i] = 0;
  }
  if(sizen>N) {
    printf("ERROR SIZE GREATER THAN EXPECTED SIZEN = %d\n",sizen);
    exit(1);
  }

  for(i=0;i<sizen;i++) {
    fscanf(fptr, "%lld",&r[i]);
    fscanf(fptr, "%lld",&h[i]);
    rh[i] = 0;

    rsort[i] = r[i];
  }
}

int calans() {
  int i,j,k,base;
  double tmp,max,sides;
  divide_sort(rsort,sizen);
  for(i=0;i<sizen;i++) {
    base = r[i];
    tmp = PI*base*base;
    k=0;
    sides = 2*PI*r[i]*h[i];
    for(j=0;j<sizen;j++)
      rh[j] = 0;
   
    for(j = 0;j<sizen;j++) {
      if((r[j] <= base) && (i != j)) {
	rh[k++] = r[j]*h[j];
      }
    }
    divide_sort(rh, sizen);
    for(j=0;j<sizek-1;j++)
      sides += 2*PI*rh[j];
    tmp += sides;
    if(tmp > max) {
      max = tmp; 
      printf ("base = %d\n",base);
    }
  }
  ans = max;
}

int print_ans(FILE *fptr2, int i) {
  fprintf(fptr2, "Case #%d: %.8f\n",i+1,ans);
}

int divide_sort(long long *arr,int n) {
        long long *left=arr;
        long long *right=arr+n/2;
        int k=0;
        int i=0;
        int j=0;
	int count, n1, n2;
	long long newarr[n];

        if(n==1) return;

	n1 = n/2;
	n2 = n - n1;
	
        divide_sort(left,n1);
        divide_sort(right,n2);

        while  ( k < n ) {
                if (left[i] < right[j]) {
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
