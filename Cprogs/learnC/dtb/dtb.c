#include<stdio.h>
#include<math.h>
main() {
int j=1;
int i=0;
int dec=0, bin[1000];
printf("Enter the binary value \nTO end Enter any other postive digit than 1 to end\nPress Enter after every digit :\n ");
scanf("%d", &bin[0]);
for(i=0;bin[i] <  2;i++) {
	dec = dec+(j*bin[i]);
	j*=2;
	scanf("%d" ,&bin[i+1]);
}
printf("The decimal equivelant is %d\n" ,dec);
}
