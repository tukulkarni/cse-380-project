#include "functions.h"
/* Test for Euler Forward routine with dy/dt = y */
void main(){
double yf,anal;

printf("-------------------------------");
printf("Running test on Euler Forward\n");
yf = eulerfwd(1,0.01,2,dydt);
anal = exp(2);

}

double dydt(double y)
{
double dy;
dy = y;
return dy;
}
