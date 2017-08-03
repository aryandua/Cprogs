#include <stdio.h>
#include <strings.h>
#include <string.h>
int main() {
	FILE *ptr;
    char eng[40];
    int size,firstword=0, count=1;
    char pig[40];
    char final;

    ptr = fopen("./file","w+");

    while (1) {
	    if(firstword==0) {
			printf("Enter the first word : ");
        	scanf("%[^\n]" ,eng);
			firstword=1;
       	}
		else {
			printf("Enter the next word or \\end\\to end : ");
			scanf(" %[^\n]" ,eng);
		}
	    if(strcmp(eng, "end") == 0)
	    	break;
	 	size = strlen(eng);
        for (count = 1; count <size; count++) {
       		pig[count-1]=eng[count];
        }
        pig[size-1]=eng[0];
       	pig[size]='a';
       	pig[size+1]='\0';
       	fprintf(ptr, "%s ", pig);
	}
    fclose (ptr);

    ptr = fopen ("./file", "r");
	while ((final = getc(ptr)) != EOF)
		putchar(final);
	fclose(ptr);
	return 0;
}

