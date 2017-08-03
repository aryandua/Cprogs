#include <stdio.h>
main()
{
	int value = 0;
	int i,inp;
	int arr[10];

	arr[0] = 1;
	arr[1] = 0;
	arr[2] = 1;
	arr[3] = 0;
	arr[4] = 1;
	arr[5] = 1;
	arr[6] = 0;
	arr[7] = 0;
	arr[8] = 0;
	arr[9] = 1;

	for (i = 0 ; i < 10; i++) {
		inp = arr[i];
		if (inp != 0 && inp != 1)
			printf ("ERROR : This is invalid %d \n",inp);
	//	value = inp << 1;
		value = value << 1 | inp;
	}

	printf ("value is decimal is %d \n", value);
	printf ("value in hex  is %x \n", value);
}
