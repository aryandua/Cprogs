#include <stdio.h>
#define SIZE 100000
int main() {
	FILE *ptr;
	ptr=fopen("./papaIntegerArray.txt","r");
	int intarr[SIZE];
	int i;
	for(i=0;i<SIZE;i++) {
		fscanf(ptr,"%d ",&intarr[i]);
	}
// printf("First = %d Last=%d",intarr[0],intarr[SIZE-1]); //  USED FOR CHECKING
//for (i = 0; i < SIZE; i++)
//	printf ("%d, ", intarr[i]);
int a,b;
long long count=0;
	for(a=0;a<SIZE;a++) {
		for(b=a+1;b<SIZE;b++) {
			if(intarr[a]>intarr[b]) {
				count++;
			}
		}
//		if(a%100==99) {
//			printf("Count = %lld \n",count);
//		}
	}
printf("THE FINAL COUNT IS %lld\n", count);
}
