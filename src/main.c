#include<stdio.h>
#include<math.h>
#include<assert.h>
#include<string.h>
#include"functions.h"
#include"testode.h"
#include"parse.h"
#include<gsl/gsl_odeiv2.h>
#include<gsl/gsl_errno.h>

int main(){
	/* Input parsing */
	FILE * outfile;
	if(input_parse()!=GRVY_SUCCESS)
		{
			printf("Error: Input parsing failed\n");
			return 1;
		}

	// Test which case to run
	if(strcmp(odesys,"test")==0)
	{
		printf("Running test case...\n");	
		testode();
		return 0;
	} else if(strcmp(odesys,"main")!=0)
		{
			printf("Error: odesys must be 'main' or 'test'\n");
			return 2;
		}
	
	/* Main CPEVF code */
	double params[2];
	params[0] = 5; params[1] = 5;
	gsl_odeiv2_system gsl_sys = {cpvef_f,cpvef_dfdy,6,&params};
	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
		(&gsl_sys,gsl_odeiv2_step_rk4,tstep,1e-8,0);

	double t0 = 0;
	double tf = 10;
	int nstep = tf/tstep+1;
	// Initial conditions
	double y[6] = {0,0,0,20,0,2};

	// Initial outfile header
	outfile = fopen("../dat/output.dat","w+");
	if(outfile==NULL)
	{
		printf("Error: Could not open file");
		return 3;
	}
	// Run the driver and output to outfile
	for(int ti=0;ti<nstep;ti++)
	{
	gsl_odeiv2_driver_apply_fixed_step(gsl_driver,&t0,tstep,1,y);
	fprintf(outfile,"%.6e\t%.6e\t%.6e\t%.6e\t%.6e\t%.6e\t%.6e\n",
		t0,y[0],y[1],y[2],y[3],y[4],y[5]);
	}
	gsl_odeiv2_driver_free(gsl_driver);
	fclose(outfile);
	return 0;
}
