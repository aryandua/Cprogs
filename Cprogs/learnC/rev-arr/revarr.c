#include <stdio.h>
main() {
	char inp[50]; 
	char *rev; 
	int i, j=100,h;
	char temp;
	printf("Enter a line of text : ");
	scanf("%[^\n]" ,inp);
	printf("%s" ,inp);
	j=(int) strlen(inp);
	rev=(char *)malloc(j+1);
	h=j;
	for(i=0;i<h;i++) {
		rev[i] = inp[j-1];
		j--;
	}
	rev[i] = '\n';
	printf("Here is the reversed verion : \n%s\n" ,rev);
}
