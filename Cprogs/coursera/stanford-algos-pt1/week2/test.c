#include <stdio.h>
int main(){
static int n=0;
printf("N=%d\n", n);
n++;
main();
}
