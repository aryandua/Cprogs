#include <stdio.h>


int main() 
{
   int amount, i, n1=1, n2=1, n3;
 
   
   printf("Enter the number of items to be printed in the series : ");
  
  scanf("%d" ,&amount);
  if (amount <= 0) {
    printf ("Please enter a positive number");
    return (-1);
  }
  if (amount == 1) {
    printf ("1");
  }
  else if (amount >= 2) {
    printf ("1, 1");
    for(i=0;i<(amount-2);i++) {
      n3 = n1 + n2;
      printf (", %d", n3);
      n1 = n2;
      n2 = n3;
	}
return 0;


	
}
