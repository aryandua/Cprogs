#include <stdio.h>
static int count = 0;

int main() {
	FILE *fptr;
        fptr=fopen("./a.txt","r");
        int intarr[SIZE];
        int j;
        for(j=0;j<SIZE;j++) {
                fscanf(fptr,"%d ",&intarr[j]);
        }
	qsort(intarr,SIZE);
	printf ("count = %d\n",count);
	for(j=0;j<SIZE;j++) printf("%d, ",intarr[j]);
}
int qsort(int *arr, int n) {
	if(n <= 1) return;

	int i, p;
	int l=0; int r=n;

	p=choosepivot(arr,n);
	i=partition(arr,l,r,p);
	qsort(arr,i);
	qsort(arr+i,n-i);

	count += n-1;
	printf ("mini count = %d , n = %d\n",count,n);
}
int choosepivot(int *arr,int n) {
	int f = arr[0];
	int l = arr[n-1];
	int m ;
	if (n % 2 == 1)
		m = arr[(n-1)/2];
	else
		arr[(n/2)-1];
	int pivot;
#ifdef FIRST
	pivot = f;
#endif
#ifdef LAST
	pivot = l;
#endif
#ifdef AVG
	if (n > 2) {
		if ((f > l && f < m) || (f < l && f > m))
			pivot = f;
		else if ((m > f && m < l) || (m < f && m > l))
			pivot = m;
		else if ((l > f && l < m) || (l < f && l > m))
			pivot = l;
		else
			printf ("ERROR!!! Could not find Average. n= %d. f = %d, m = %d, l = %d, What a shame :( \n", n, f,m,l);
	}
	else if (n == 2) {
		pivot = l;
	}
	else 
		printf ("ERROR!!! n is unexpected value = %d. What a shame :( \n",n);
#endif
	return (pivot);
}

int partition(int *arr, int l, int r,int p) {
        int i=l+1;
        int j;
        int temp;
        for(j=l+1;j<r;j++) {
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
	return i;
}

