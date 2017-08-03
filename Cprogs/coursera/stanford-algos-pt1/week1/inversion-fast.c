#include <stdio.h>
#define SIZE 10
long long divide_sort (int *arr, int n);
int main() {
 FILE *fptr;
        fptr=fopen("./small.txt","r");
        int intarr[SIZE];
        int j;
	long long answer;
        for(j=0;j<SIZE;j++) {
                fscanf(fptr,"%d ",&intarr[j]);
        }
	answer = divide_sort(intarr,SIZE);
//printf("%d \n",j);
//        for(j=0;j<SIZE;j++)
  //              printf("%d  ",intarr[j]);
	printf ("Total Inversions are = %lld\n", answer);
}


long long divide_sort(int *arr,int n) {
        int *left=arr;
        int *right=arr+n/2;
        int k=0;
        int i=0;
        int j=0;
	int count, n1, n2;
	int newarr[n];
	long long invcount = 0;
        if(n==1){
	 return;
	}

	n1 = n/2;
	n2 = n - n1;

        invcount += divide_sort(left,n1);
        invcount += divide_sort(right,n2);
        while  ( k < n ) {
                if (right[j] < left[i] ) {
			newarr[k] = right[j];
			invcount+=(n1-i);
			j++;
			k++;
			if (j >= n2) {
				for (count = i; count < n1; count++) {
					newarr[k] = left[i];
					i++;
					k++;
			//		invcount += n2;
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
       		printf("%d, ",arr[count]);
	}
//printf("split Inversions = %lld, n = %d \n",invcount, n);
	//printf("%lld \n",invcount);
printf("\n");
	return (invcount);
/*
        for(count=0;count<n;count++) {
                printf("%d  ",arr[count]);
        }

	printf ("\n");
*/
}
