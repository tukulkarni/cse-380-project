#include<stdio.h>
#include<math.h>
#include<assert.h>
#include"functions.h"
#include"parse.h"
#include<gsl/gsl_odeiv2.h>
#include<gsl/gsl_errno.h>

int main(){
	double yf,anal;
	/* Input parsing */
	parse_set();	// Setup GRVY for use
	set_def();		// Set default values
	get_inp();		// Read input file

	/* TESTS with 1st order ODE
	// User defined integration routine
	yf = eulerfwd(1,tstep,2,dydt);
	anal = exp(2);

	// Using gsl library 
	gsl_odeiv2_system gsl_sys = {test_f,test_dfdy,1,(void *) NULL};
	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
		(&gsl_sys,gsl_odeiv2_step_rk1imp,tstep,1e-8,0);

	double t0 = 0; 
	double tf = 2;
	double y[1]; y[0] = 1;
	gsl_odeiv2_driver_apply(gsl_driver,&t0,tf,y);
	gsl_odeiv2_driver_free(gsl_driver);

	// Print output
	printf("Running with dt = %.3E\n",tstep);
	printf("numerical = %lf\t analytic = %lf \t gsl = %f \n",
				yf,anal,y[0]);
	*/
	/* Main CPEVF code */
	double params[2];
	params[0] = 5; params[1] = 5;
	gsl_odeiv2_system gsl_sys = {cpvef_f,cpvef_dfdy,6,&params};
	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
		(&gsl_sys,gsl_odeiv2_step_rk4,tstep,1e-8,0);

	double t0 = 0;
	double tf = 10;
	// Initial conditions
	double y[6] = {0,0,0,20,0,2};
	gsl_odeiv2_driver_apply(gsl_driver,&t0,tf,y);
	gsl_odeiv2_driver_free(gsl_driver);
	for(int i=0;i<6;i++)
		printf("%f\t",y[i]);
	printf("\n");
	return 0;
}
