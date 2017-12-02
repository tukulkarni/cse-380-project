#include "functions.h"
/* functions to solve 1st order ODE */
double eulerfwd(double y0, double dt, double tf,double (*f)(double))
{
// Solves dy/dt = f(y) with y(0) = y0 and step dt
int i,n;
double y,dy;
n = (int) tf/dt;

y = y0;	// initialize;
for(i=0;i<n;i++)
	{
		dy = (*f)(y);
		y = y + dy*dt;
	}
return y;
}

double dydt(double y)
{
	double dy;
	dy = y;
	return dy;
}

int gsl_f(double t,const double y[],double f[],void *params)
{
	f[0]=y[0]+0*t;
	return GSL_SUCCESS;
}

int gsl_dfdy(double t,const double y[],double *dfdy, double dfdt[], void *params)
{
	// Set dfdy and dfdt
	dfdt[0] = 0*t;
	dfdy[0] = 1.0 + 0*y[0];
	return GSL_SUCCESS;	
}

