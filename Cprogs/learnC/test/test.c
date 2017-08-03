#include<stdio.h>
main() {
char oprc;
int firstnum;
int secondnum;
int score=0;
int opr;
int ans, arnavans, i;
printf("Hello Arnav Dua. \n Today you will be tested on how well you have understood the concepts that have been tought in the Spring break math tutoring program\n");
printf("Let's Begin \n Remember this is not a timed test\n");
for(i=1;i<=30;i++) {
	firstnum = rand() % 18 + (-9);
	secondnum = rand() % 18 + (-9);
	opr = rand() % 3+1;
	if(opr==1) {
		ans=firstnum+secondnum;
		oprc = '+';
	}
	else if(opr==2) {
		ans=firstnum-secondnum;
		oprc = '-';
	}
	else if(opr==3) {
		ans=firstnum*secondnum;
		oprc='x';
	}
	printf("%d%c%d = ",firstnum,  oprc, secondnum);
	scanf("%d",&arnavans);
	if(ans==arnavans) {
		score=score+1;
	}
}
printf("END OF TEST\n You scored %d out of 30",score+1);
}

