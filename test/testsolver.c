#include "testsuite.h"

void testBE()
{
	// Test GSL solver RK1-imp convergence
	double anal = exp(2);
	double h[6] = {1e-2,1e-3,1e-4,1e-5,1e-6,1e-7};
	double logh[6] = {-2,-3,-4,-5,-6,-7};
	double err[6];
	double y[1];
	double nsteps;

	const gsl_odeiv2_step_type * GSLstepper = gsl_odeiv2_step_rk1imp;
	double order = 1;
	double TOL = 0.2;
	// Set up the GSL system
	gsl_odeiv2_system gsl_sys = {test_f,test_dfdy,1,(void *) NULL};

	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
			(&gsl_sys,GSLstepper,h[0],0.1,0);
	for(int i=0;i<6;i++)
	{
		y[0] = 1;
		// Using gsl library 
		double t0 = 0; 
		nsteps = (int)(2/h[i]);
		gsl_odeiv2_driver_reset(gsl_driver);
		gsl_odeiv2_driver_apply_fixed_step(gsl_driver,&t0,h[i],nsteps,y);
		err[i] = log(y[0]-anal);
	}
	gsl_odeiv2_driver_free(gsl_driver);
	// Check if the order of convergence is correct
	double slope = linreg(logh,err,6);
	printf("Test Backward Euler gave slope = %f\n",slope);
	CU_ASSERT_DOUBLE_EQUAL(slope,order,TOL);
}

void testRK2()
{
	// Test GSL solver RK1-imp convergence
	double anal = exp(2);
	double h[6] = {1e-2,1e-3,1e-4,1e-5,1e-6,1e-7};
	double logh[6] = {-2,-3,-4,-5,-6,-7};
	double err[6];
	double y[1];
	double nsteps;

	const gsl_odeiv2_step_type * GSLstepper = gsl_odeiv2_step_rk2;
	double order = 2.0;
	double TOL = 0.2;
	// Set up the GSL system
	gsl_odeiv2_system gsl_sys = {test_f,test_dfdy,1,(void *) NULL};

	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
			(&gsl_sys,GSLstepper,h[0],0.1,0);
	for(int i=0;i<6;i++)
	{
		y[0] = 1;
		// Using gsl library 
		double t0 = 0; 
		nsteps = (int)(2/h[i]);
		gsl_odeiv2_driver_reset(gsl_driver);
		gsl_odeiv2_driver_apply_fixed_step(gsl_driver,&t0,h[i],nsteps,y);
		err[i] = log(y[0]-anal);
	}
	gsl_odeiv2_driver_free(gsl_driver);
	// Check if the order of convergence is correct
	double slope = linreg(logh,err,6); 
	printf("Test RK2 gave slope = %f\n",slope);
	CU_ASSERT_DOUBLE_EQUAL(slope,order,TOL);
}

void testRK4()
{
	// Test GSL solver RK1-imp convergence
	double anal = exp(2);
	double h[6] = {1e-2,1e-3,1e-4,1e-5,1e-6,1e-7};
	double logh[6] = {-2,-3,-4,-5,-6,-7};
	double err[6];
	double y[1];
	double nsteps;

	const gsl_odeiv2_step_type * GSLstepper = gsl_odeiv2_step_rk4;
	double order = 4.0;
	double TOL = 0.2;
	// Set up the GSL system
	gsl_odeiv2_system gsl_sys = {test_f,test_dfdy,1,(void *) NULL};

	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
			(&gsl_sys,GSLstepper,h[0],0.1,0);
	for(int i=0;i<6;i++)
	{
		y[0] = 1;
		// Using gsl library 
		double t0 = 0; 
		nsteps = (int)(2/h[i]);
		gsl_odeiv2_driver_reset(gsl_driver);
		gsl_odeiv2_driver_apply_fixed_step(gsl_driver,&t0,h[i],nsteps,y);
		err[i] = log(abs(y[0]-anal));
	}
	gsl_odeiv2_driver_free(gsl_driver);
	// Check if the order of convergence is correct
	double slope = linreg(logh,err,6); 
	printf("Test RK4 gave slope = %f\n",slope);
	CU_ASSERT_DOUBLE_EQUAL(slope,order,TOL);
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
	printf("Slope = %f\n",denom);
    return slope; 
}

