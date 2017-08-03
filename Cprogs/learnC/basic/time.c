#include <stdio.h>
#include <time.h>
int main() {
	time_t t;
	printf("TIME : %s\n" ,ctime(&t));
}
