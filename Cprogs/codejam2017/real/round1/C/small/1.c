#include <stdio.h>
#include <math.h>
int main(){
 long long i = 811188;
 long long j = 20254;
 double ans;
 ans = i * j;
 ans *= 2*M_PI;
 ans += M_PI*j*j;
 printf ("ans = %f\n",ans);
}

