
#include <stdio.h>
#include <time.h>
main() {
	int i;
	float f;
	int count;
	time_t t;
	srand ((unsigned)time(&t));
	for (count = 0; count < 5; count++) {
		i = rand() % 200;
		printf ("i = %d\n",i);
	}
	return;
}
