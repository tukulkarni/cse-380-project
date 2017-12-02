//Libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "grvy.h"
#include<gsl/gsl_math.h>
#include<gsl/gsl_odeiv2.h>
#include<gsl/gsl_errno.h>

// Variables

// Functions
double eulerfwd(double y0,double dt,double tf,double (*f)(double));
double dydt(double y);
int gsl_f(double t,const double y[],double f[],void *params);
int gsl_dfdy(double t,const double y[],double *dfdy, double dfdt[], void *params);
