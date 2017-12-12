//Libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "parse.h"
#include<gsl/gsl_odeiv2.h>
#include<gsl/gsl_errno.h>

// Variables
FILE * outfile;
// Functions
int cpvef_f(double t,const double y[],double f[],void *params);
int cpvef_dfdy(double t,const double y[],double *dfdy, double dfdt[], void *params);
int print_header();
void message(int type,char text[]);

