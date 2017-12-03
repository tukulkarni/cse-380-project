#include<stdio.h>
#include<math.h>
#include"testode.h"
#include"parse.h"
#include<gsl/gsl_odeiv2.h>
#include<gsl/gsl_errno.h>

int testode()
{
	// Test GSL and user implementation of Euler forward
	// on a simple 1st order ODE : dy/dt = y, with y(0) =1
	// which admits the analytic solution y = exp(t)

	/* TESTS with 1st order ODE */
	// User defined integration routine
	double yf,anal;
	yf = eulerfwd(1,tstep,2,dydt);
	anal = exp(2);

	// Using gsl library 
	gsl_odeiv2_system gsl_sys = {test_f,test_dfdy,1,(void *) NULL};
	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
		(&gsl_sys,gsl_odeiv2_step_rk1imp,tstep,1e-8,0);

	double t0 = 0; 
	double tf = 2;
	double y[1] = {1};
	gsl_odeiv2_driver_apply(gsl_driver,&t0,tf,y);
	gsl_odeiv2_driver_free(gsl_driver);

	// Print output
	printf("Running with dt = %.3E\n",tstep);
	printf("numerical = %lf\t analytic = %lf \t gsl = %f \n",
				yf,anal,y[0]);
	return 0;

}

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
	(void)(params);
	f[0]=y[0]+0*t;
	return GSL_SUCCESS;
}

int test_dfdy(double t,const double y[],double *dfdy, double dfdt[], void *params)
{
	(void)(params);
	// Set dfdy and dfdt
	dfdt[0] = 0*t;
	dfdy[0] = 1.0 + 0*y[0];
	return GSL_SUCCESS;	
}
