#include"functions.h"
#include"testode.h"
int main(){
	char msg[100];// Maximum supported length of messages
	
	/* Input parsing */
	grvy_timer_init(" Timing using GRVY ");
	grvy_timer_begin("Main program");
	grvy_timer_begin("Input parsing");
	input_parse();	// Grvy takes care of error handling
	grvy_timer_end("Input parsing");

	/* Test which case to run */
	if(strcmp(odesys,"test")==0)
	{
		message(0,"\nRunning test case...");	
		testode();
		grvy_timer_end("Main program");
		grvy_timer_finalize();
		grvy_timer_summarize();
		return 0;
	} else if(strcmp(odesys,"main")!=0)
		{
			message(1,"Error: odesys must be 'main' or 'test'");
			return 2;
		}
	
	/* Main CPEVF code */
	message(0,"\nRunning calculations for Charged Particle in Vertical Electric Field");
	sprintf(msg,"--> Time step is %.3e",tstep);
	message(1,msg);
	
	double params[2];
	params[0] = 5; params[1] = 5;
	gsl_odeiv2_system gsl_sys = {cpvef_f,cpvef_dfdy,6,&params};
	gsl_odeiv2_driver * gsl_driver = gsl_odeiv2_driver_alloc_y_new
		(&gsl_sys,stepper_fun,tstep,1e-1,0);

	double t0 = 0;
	unsigned long int nstep = (int)(tf/tstep);
	// Initial conditions
	double y[6] = {0,0,0,20,0,2};
	sprintf(msg, "--> Initial conditions (x0,y0,z0) = (%.3e,%.3e,%.3e)",
				y[0],y[1],y[2]);
	message(1,msg);
	sprintf(msg, "                       (u0,v0,w0) = (%.3e,%.3e,%.3e)",
				y[3],y[4],y[5]);
	message(1,msg); 
	message(2,"\n#### Output of the program #### ");
	sprintf(msg," %9s :  %11s   %11s   %11s","time","x(m)","y(m)","z(m)"); 
	message(2,msg);
	// Initial outfile header
	print_header();
	// Run the driver and output to outfile
	for(long unsigned int ti=0;ti<nstep;ti++)
	{
		if(ti%outfreq==0)
		{	
			fprintf(outfile,"%.6e\t%.6e\t%.6e\t%.6e\t%.6e\t%.6e\t%.6e\n",
				t0,y[0],y[1],y[2],y[3],y[4],y[5]);
			sprintf(msg," %9.3e : %11.4E   %11.4E   %11.4E",
				t0,y[0],y[1],y[2]);
			message(2,msg);
		}
		if(ti==0)
			grvy_timer_begin("GSL integrator");
		gsl_odeiv2_driver_apply_fixed_step(gsl_driver,&t0,tstep,1,y);
	}
	gsl_odeiv2_driver_free(gsl_driver);
	fclose(outfile);
	grvy_timer_end("GSL integrator");
	grvy_timer_end("Main program");
	grvy_timer_finalize();
	message(0,"Execution complete..");
	sprintf(msg,"Output written to %s",outfilename);
	message(1,msg);
	message(1,"\n#### GRVY TIMING REPORT ####");
	grvy_timer_summarize();
	return 0;
}
