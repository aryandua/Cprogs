#include <stdio.h>
#define SIZE 10000
void qsort(int *arr, int n);

int main() {
	int arr[SIZE];
	int i;
	FILE *fptr;
	fptr=fopen("./small.txt", "r");
	for(i=0;i<SIZE;i++) fscanf(fptr, " %d",&arr[i]);
	qsort(arr, SIZE);
	for(i=0;i<SIZE;i++) printf("%d\n",arr[i]);
}

void qsort(int *arr, int n) {
	if(n<=1) return;
	int l=0, r=n-1;
	int i,p;
	p=choosepivot(arr,l,r);
	i=partition(arr,l,r,p);
	qsort(arr, i);
	qsort(arr+i+1, r-i);
}

int choosepivot(int *arr, int l, int r) {
	return arr[l];
}

int partition(int *arr, int l, int r, int p) {
	int i=l+1;
	int j, temp;
	for(j=l+1;j<=r;j++) {
		if(arr[j]<p) {
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
			i++;
		}
	}
	temp=arr[i-1];
	arr[i-1]=arr[l];
	arr[l]=temp;
	return (i-1);
}


