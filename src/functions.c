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

int test_f(double t,const double y[],double f[],void *params)
{
	f[0]=y[0]+0*t;
	return GSL_SUCCESS;
}

int test_dfdy(double t,const double y[],double *dfdy, double dfdt[], void *params)
{
	// Set dfdy and dfdt
	dfdt[0] = 0*t;
	dfdy[0] = 1.0 + 0*y[0];
	return GSL_SUCCESS;	
}

int cpvef_f(double t, const double y[], double f[], void *params)
{
	/* RHS of ODE for 
	CPVEF : Charged Particle in Vertical Electric Field
	3 ODEs are cast in form of 6 1st order ODES dy/dt = f(y,t)
	*/
	double * consts = (double *)params;
	double omega = consts[0];
	double tau = consts[1];

	f[0] = y[3];
	f[1] = y[4];
	f[2] = y[5];
	f[3] = omega*y[4] - y[3]/tau;
	f[4] = -omega*y[3] - y[4]/tau;
	f[5] = -y[5]/tau; 

	return GSL_SUCCESS;
}

int cpvef_dfdy(double t,const double y[],double *dfdy, double dfdt[], void *params)
{
	double * consts = (double *)params;
	double omega = consts[0];
	double tau = consts[1];
	int i,j;
	int len = sizeof(y)/sizeof(double);
	
	/* Jacobian df/dy */
	// Initialize all to zero
	for(i=0;i<len;i++)
		for(j=0;j<len;j++)
		{
			dfdy[i*len+j] = 0;
		}
	// Fill non-zero entries
	dfdy[0*len+3] = 1.0;
	dfdy[1*len+4] = 1.0;
	dfdy[2*len+5] = 1.0; // dfdy[2][5]
	dfdy[3*len+3] = -1.0/tau; dfdy[3*len+4] = omega;
	dfdy[4*len+4] = -1.0/tau; dfdy[4*len+5] = -omega;
	dfdy[5*len+5] = -1.0/tau;

	/* df/dt */
	for(i=0;i<len;i++)
		dfdt[i] = 0.0;	// No explicit dependence on t
	
	return GSL_SUCCESS;
}
