#include"functions.h"
#include"testode.h"
#include"parse.h"
#include<math.h>
#include<stdio.h>

int testode()
{
	// Test GSL and user implementation of Euler forward
	// on a simple 1st order ODE : dy/dt = y, with y(0) =1
	// which admits the analytic solution y = exp(t)
	grvy_timer_begin("testode");
	/* TESTS with 1st order ODE */
	// User defined integration routine
	double yf;
	double anal = exp(2);
	double h = 1e-1; // hmax, halved every time till 1e-6
	double y[1];
	char msg[100];
	unsigned long int nsteps;

	// Set up file I/O for results
	FILE * testfile = fopen(outfilename,"w");
	fprintf(testfile,"## Output of 1st order ODE solution\n");
	fprintf(testfile,"# ODE : dy/dt = cos(y), y(0) = 0\n");
	fprintf(testfile,"# Analytic solution : y(t) = exp(t)\n");
	fprintf(testfile,"# ODE integrated from t = 0 to t = 2\n");
	fprintf(testfile,"# Convergence analysis for Euler Forward and GSL's Implicit RK1\n");
	fprintf(testfile,"%-10s\t%-10s\t%-10s\t%-10s\t%-10s%-10s\n","#   dt"," Analytic"," Numerical",
				"     GSL","    E_num","    E_GSL");
	sprintf(msg,"Writing the output of error analysis to %s",outfilename);
	message(0,msg);	
	// Set up the GSL system
	gsl_odeiv2_system gsl_sys = {test_f,test_dfdy,1,(void *) NULL};
	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
			(&gsl_sys,stepper_fun,h,0.1,0);
	do
	{
		y[0] = 1;
		// User implementation of forward euler
		yf = eulerfwd(*y,h,2,dydt);
		sprintf(msg,"Tfinal is %.3E\n",tf);
		message(1,msg);
	
		// Using gsl library 
		grvy_timer_begin("GSL solver");
		double t0 = 0; 
		nsteps = (int)(2/h);
		gsl_odeiv2_driver_reset(gsl_driver);
		gsl_odeiv2_driver_apply_fixed_step(gsl_driver,&t0,h,nsteps,y);

		sprintf(msg,"h is %f, nsteps is %ld, tfinal is %f",h,nsteps,t0);
		message(1,msg);
		grvy_timer_end("GSL solver");

		// Print output
		fprintf(testfile,"%10.3E\t%10.3E\t%10.3E\t%10.3E\t%10.3E\t%10.3E\n",
					h,anal,yf,y[0],fabs(yf-anal),fabs(anal-y[0]));
		h = h/2;
	}
	while(h>1e-6);
	gsl_odeiv2_driver_free(gsl_driver);
	grvy_timer_end("testode");
	return 0;
}

double eulerfwd(double y0, double dt, double tend,double (*f)(double))
{
// Solves dy/dt = f(y) with y(0) = y0 and step dt
grvy_timer_begin("Euler forward (user)");
int i,n;
double y,dy;
n = (int) tend/dt;

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
	return y;
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
	dfdy[0] = 1+0*y[0];
	return GSL_SUCCESS;	
}
