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

	/* User defined integration routine */
	yf = eulerfwd(1,tstep,2,dydt);
	anal = exp(2);

	/* Using gsl library */
	gsl_odeiv2_system gsl_sys = {gsl_f,gsl_dfdy,1,(void *) NULL};
	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
		(&gsl_sys,gsl_odeiv2_step_rk4,tstep,1e-8,0);

	double t0 = 0; 
	double tf = 2;
	double y[1]; y[0] = 1;
	gsl_odeiv2_driver_apply(gsl_driver,&t0,tf,y);
	gsl_odeiv2_driver_free(gsl_driver);

	/* Print output */
	printf("Running with dt = %.3E\n",tstep);
	printf("numerical = %lf\t analytic = %lf \t gsl = %f \n",
				yf,anal,y[0]);
	return 0;
}
