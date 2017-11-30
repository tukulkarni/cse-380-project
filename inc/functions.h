#include<stdio.h>
#include<math.h>

double eulerfwd(double y0,double dt,double tf,double (*f)(double));
double dydt(double y);
