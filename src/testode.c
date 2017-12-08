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
	grvy_timer_begin("testode");
	/* TESTS with 1st order ODE */
	// User defined integration routine
	double yf,anal;
	double h = 1e-1;
	unsigned long int nsteps;
	do
	{
		gsl_odeiv2_system gsl_sys = {test_f,test_dfdy,1,(void *) NULL};
		gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
			(&gsl_sys,gsl_odeiv2_step_rk1imp,h,1e-8,0);

		double t0 = 0; 
		double tf = 2;
		nsteps = (int)(tf/h);
		double y[1] = {1};
		
		// User implementation of forward euler
		yf = eulerfwd(*y,h,tf,dydt);
		anal = exp(2);
		
		// Using gsl library 
		grvy_timer_begin("GSL solver");
		gsl_odeiv2_driver_apply_fixed_step(gsl_driver,&t0,h,nsteps,y);
		grvy_timer_end("GSL solver");
		gsl_odeiv2_driver_free(gsl_driver);

		// Print output
		printf("h = %.3E, nstep = %10d. Errors : ",h,nsteps);
		printf("num = %10.3E\t gsl = %10.3E \n",
					fabs(yf-anal),fabs(anal-y[0]));
		h = h/2;
	}
	while(h>1e-6);
	grvy_timer_end("testode");
	return 0;

}

double eulerfwd(double y0, double dt, double tf,double (*f)(double))
{
// Solves dy/dt = f(y) with y(0) = y0 and step dt
grvy_timer_begin("Euler forward (user)");
int i,n;
double y,dy;
n = (int) tf/dt;

y = y0;	// initialize;
for(i=0;i<n;i++)
	{
		dy = (*f)(y);
		y = y + dy*dt;
	}
grvy_timer_end("Euler forward (user)");
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
