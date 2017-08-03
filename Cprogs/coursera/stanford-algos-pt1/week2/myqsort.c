#include <stdio.h>
#define SIZE 8
int main() {
	FILE *fptr;
	fptr=fopen("small.txt","r");
	int arr[SIZE];
	int i;
	for(i=0;i<SIZE;i++) fscanf(fptr, " %d",&arr[i]);
	qsort(arr,SIZE);
	for(i=0;i<SIZE;i++) printf("%d, ",arr[i]);
	printf("\n");
}
qsort(int *arr, int n) {
	if(n<=1) return;
	int i,p,r=n-1,l=0;
	p=choosepivot(arr, l);
	i=partition(arr, l, r, p);
	qsort(arr,i);
	qsort(arr+i+1, r-i);
}
int choosepivot(int *arr, int l) {
	return arr[l];
}
int partition(int *arr, int l, int r, int p) {
	int i=l+1;
	int temp;
	int j;
	for(j=l+1;j<=r;j++) {
		if(arr[j]<p) {
			temp=arr[j];
			arr[j]=arr[i];
			arr[i]=temp;
			i++;
		}
	}
	temp=arr[l];
	arr[l]=arr[i-1];
	arr[i-1]=temp;
	return (i-1);
}

