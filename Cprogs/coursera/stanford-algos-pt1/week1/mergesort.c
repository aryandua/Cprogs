#include <stdio.h> 
#define SIZE 100000
int main() {
 FILE *fptr;
        fptr=fopen("./IntegerArray.txt","r");
        int intarr[SIZE];
        int j;
        for(j=0;j<SIZE;j++) {
                fscanf(fptr,"%d ",&intarr[j]);
        }

	divide_sort(intarr,SIZE);

//        for(j=0;j<SIZE;j++)
  //              printf("%d  ",intarr[j]);
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
/*
        for(count=0;count<n;count++) {
                printf("%d  ",arr[count]);
        }
	printf ("\n");
*/
}
