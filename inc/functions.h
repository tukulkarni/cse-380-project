//Libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "grvy.h"

// Variables

// Functions
double eulerfwd(double y0,double dt,double tf,double (*f)(double));
double dydt(double y);
void input_parse();
