#include <stdio.h>
int main() {
	static int lap=0;
	if(lap==233) {
		printf("10000 steps done!!! \n");
	}
	printf("Laps Remaining=%d\n",233-lap);
	getchar();
	lap++;
	main();
}
