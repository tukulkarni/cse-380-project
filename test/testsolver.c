#include "testsuite.h"
void testBE()
{
	double h[5] = {1e-1,1e-2,1e-3,1e-4,1e-5};
	double slope = testsolver(gsl_odeiv2_step_rk1imp,h);
	printf(" slope = %f ---> ",slope);
	CU_ASSERT_DOUBLE_EQUAL(slope,1,0.1);
}

void testRK2()
{
	double h[5] = {1e-1,5e-2,1e-2,5e-3,1e-3};
	double slope = testsolver(gsl_odeiv2_step_rk2,h);
	printf(" slope = %f ---> ",slope);
	CU_ASSERT_DOUBLE_EQUAL(slope,3,0.2);
}

void testRK4()
{
	double h[5] = {1e-1,5e-2,1e-2,5e-3,2e-3};
	double slope = testsolver(gsl_odeiv2_step_rk4,h);
	printf(" slope = %f ---> ",slope);
	CU_ASSERT_DOUBLE_EQUAL(slope,4,0.2);
}

double testsolver(const gsl_odeiv2_step_type * GSLstepper, double h[5])
{
	// Test GSL solver RK1-imp convergence
	double logh[5];
	double err[5];
	double y[1];
	double nsteps;
	double anal = exp(2);
	double t0,slope; 
		
	// Set up the GSL system
	gsl_odeiv2_system gsl_sys = {test_f,test_dfdy,1,(void *) NULL};

	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
			(&gsl_sys,GSLstepper,h[0],0.1,0);
	for(int i=0;i<5;i++)
	{
		y[0] = 1;
		t0 = 0;
		// Using gsl library 
		nsteps = (int)(2/h[i]);
		logh[i] = log10(h[i]);
		gsl_odeiv2_driver_reset(gsl_driver);
		gsl_odeiv2_driver_apply_fixed_step(gsl_driver,&t0,h[i],nsteps,y);
		err[i] = log10(fabs(y[0]-anal));
	}
	gsl_odeiv2_driver_free(gsl_driver);
	// Check if the order of convergence is correct
	slope = linreg(logh,err,5);
	return slope;
}

double linreg(const double x[], const double y[],int n)
{
    double sumx = 0.0;                      /* sum of x     */
    double sumx2 = 0.0;                     /* sum of x**2  */
    double sumxy = 0.0;                     /* sum of x * y */
    double sumy = 0.0;                      /* sum of y     */
    double sumy2 = 0.0;                     /* sum of y**2  */
	double slope;

    for (int i=0;i<n;i++){ 
        sumx  += x[i];       
        sumx2 += pow(x[i],2);  
        sumxy += x[i]*y[i];
        sumy  += y[i];      
        sumy2 += pow(y[i],2); 
    } 

    double denom = (n * sumx2 - pow(sumx,2));
    if (denom == 0) {
        // singular matrix. can't solve the problem.
            return 0;
    }

    slope = (n * sumxy  -  sumx * sumy) / denom;
    return slope; 
}
