#include "functions.h"
#include "testode.h"
/* Test for Euler Forward routine with dy/dt = y */
void tEulerfwd(){
double yf,anal;

printf("-------------------------------");
printf("Running test on Euler Forward\n");
yf = eulerfwd(1,0.01,2,dydt);
anal = exp(2);
}

