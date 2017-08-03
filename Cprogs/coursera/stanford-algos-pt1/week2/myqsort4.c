#include <stdio.h>
#define SIZE 10000
int main() {
	int i;
	int arr[SIZE];
	FILE *fptr;
	fptr=fopen("./a.txt", "r");
	for(i=0;i<SIZE;i++) {
		fscanf(fptr," %d",&arr[i]);
	}
	qsort(arr, SIZE);
	for(i=0;i<SIZE;i++) {
		printf("%d\n",arr[i]);
	}
}
qsort(int *arr, int n) {
	if(n<=1) return;
	int p=arr[0];
	int i;
	int l=0;
	int r=n-1;
	i=partition(arr, p,l,r);
	qsort(arr, i);
	qsort(arr+i+1, r-i);
}

int partition(int *arr, int p, int l, int r) {
	int i=1,j,temp;
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
	return i-1;
}
