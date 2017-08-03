#include <stdio.h>
main() {
int a;
int b;
int *ptr;
int *ptr2;
a=7;
ptr = &a;
b = *ptr;
ptr2 = &b;
printf("ptr = %x, ptr2 = %x, a = %d, b = %d, &a = %x, &b = %x, *ptr = %d, *ptr2 = %d \n", ptr, ptr2, a, b, &a, &b, *ptr, *ptr2);
*ptr2 = 20;
printf("ptr = %x, ptr2 = %x, a = %d, b = %d, &a = %x, &b = %x, *ptr = %d, *ptr2 = %d \n", ptr, ptr2, a, b, &a, &b, *ptr, *ptr2);
}  
