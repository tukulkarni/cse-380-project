#include<stdio.h>
#include<math.h>
#include<string.h>
#include"functions.h"
#include"testode.h"
#include"parse.h"
#include<gsl/gsl_odeiv2.h>
#include<gsl/gsl_errno.h>
#include<CUnit/CUnit.h>
int main(){
	char str[100];// Maximum supported length of messages
	/* Input parsing */
	input_parse();	// Grvy takes care of error handling
	// Test which case to run
	if(strcmp(odesys,"test")==0)
	{
		message(0,"Running test case...");	
		testode();
		return 0;
	} else if(strcmp(odesys,"main")!=0)
		{
			message(0,"Error: odesys must be 'main' or 'test'");
			return 2;
		}
	
	/* Main CPEVF code */
	message(0,"Running calculations for Charged Particle in Vertical Electric Field");
	sprintf(str," Time step is %.3e",tstep);
	message(0,str);
	
	double params[2];
	params[0] = 5; params[1] = 5;
	gsl_odeiv2_system gsl_sys = {cpvef_f,cpvef_dfdy,6,&params};
	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
		(&gsl_sys,stepper_fun,tstep,1e-8,0);

	double t0 = 0;
	double tf = 10;
	int nstep = tf/tstep+1;
	// Initial conditions
	double y[6] = {0,0,0,20,0,2};
	sprintf(str, "Initial conditions (x0,y0,z0) = (%.3e,%.3e,%.3e)",
				y[0],y[1],y[2]);
	message(0,str);
	sprintf(str, "                   (u0,v0,w0) = (%.3e,%.3e,%.3e)",
				y[3],y[4],y[5]);
	message(0,str); 
	message(1,"----- Output of the program ---- ");
	sprintf(str," %9s :  %11s   %11s   %11s","time","x(m)","y(m)","z(m)"); 
	message(1,str);
	// Initial outfile header
	print_header();
	// Run the driver and output to outfile
	for(int ti=0;ti<nstep;ti++)
	{
		if(ti%outfreq==0)
		{	
			fprintf(outfile,"%.6e\t%.6e\t%.6e\t%.6e\t%.6e\t%.6e\t%.6e\n",
				t0,y[0],y[1],y[2],y[3],y[4],y[5]);
			sprintf(str," %9.3e : %11.4E   %11.4E   %11.4E",
				t0,y[0],y[1],y[2],y[3],y[4],y[5]);
			message(1,str);
		}
		gsl_odeiv2_driver_apply_fixed_step(gsl_driver,&t0,tstep,1,y);
	}
	gsl_odeiv2_driver_free(gsl_driver);
	fclose(outfile);
	return 0;
}
