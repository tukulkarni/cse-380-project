#include<stdio.h>
#include<math.h>
#include<assert.h>
#include"functions.h"

int main(){
double yf,anal;
yf = eulerfwd(1,0.001,2,dydt);
anal = exp(2);
printf("yf = %lf\t exp = %lf\n",yf,anal);
return 0;
}
