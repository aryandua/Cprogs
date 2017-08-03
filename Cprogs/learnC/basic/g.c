#include <stdio.h>
main() {
char filename[10];
FILE *fptr;
printf("Enter the desired file name : ");
scanf("%s" ,filename);
fptr = fopen(filename, "a+");
fprintf(fptr, "HELLO!");
fclose(fptr);
}

