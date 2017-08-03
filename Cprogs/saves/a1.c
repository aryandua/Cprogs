#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define T 100
#define N 10
//#define PI 3.14159265359
#define PI M_PI

long long h[N];
long long r[N];
long long rh[N];
long long rorig[N];
long long horig[N];
 double ans;
int sizen,sizek;

int main() {
  FILE *fptr,*fptr2;
  fptr = fopen("./a.txt", "r");
  fptr2 = fopen("./output.txt", "w");
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
    printf("ERROR SIZE GREATER THAN EXPECTED\n");
    exit(1);
  }

  for(i=0;i<sizen;i++) {
    fscanf(fptr, "%lld",&r[i]);
    fscanf(fptr, "%lld",&h[i]);
    rh[i] = r[i] * h[i];

    rorig[i] = r[i];
    horig[i] = h[i];
  }
}

int calans() {
  int i,count;
  long long tmp;
  ans = 0.0;
  divide_sort(rh,sizen);
  divide_sort(r,sizen);
  for(i=0;i<sizek;i++) {
    ans += rh[i];
  }

  for(count = 0;count<sizen;count++) {
    for(i=0;i<sizen;i++) {
      if(r[count] == rorig[i]) {
	break;
      }
    }
    tmp = rorig[i] * horig[i];
    if(tmp>=rh[sizek-1]) {
      ans = (ans*2*PI);
      ans = ans + (PI*rorig[i]*rorig[i]);
      return;
    }
  }
}

int print_ans(FILE *fptr2, int i) {
  fprintf(fptr2, "Case #%d: %.9f\n",i+1,ans);
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
