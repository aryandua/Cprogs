#include <stdio.h>
main() {
int a;
int b;
char *ptr3;
int *ptr;
int *ptr2;
a=7;
ptr = &a;
b = *ptr;
ptr2 = &b;
printf("ptr = %x, ptr2 = %x, a = %d, b = %d, &a = %x, &b = %x, *ptr = %d, *ptr2 = %d, ptr3 = %x, *ptr3 = %c \n", ptr, ptr2, a, b, &a, &b, *ptr, *ptr2,ptr3, *ptr3);
}  
