// Function file for input parsing routines
#include "parse.h"
#include "functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int input_parse()
{
	// High level wrapper for all GRVY wrappers
	parse_set();
	set_def();
	get_inp();
	return GRVY_SUCCESS;
}
void parse_set()
{
	int q;
	// Sets up input parsing with grvy
	q=grvy_input_fopen("input.dat");
	if(q!=1)
	{
		grvy_input_fclose();
		exit(1);
	}
}

void set_def()
{
	// Set defaluts for code params
	grvy_input_register_int("code/verbosity",1);
	grvy_input_register_char("code/odesys","test");
	grvy_input_register_char("code/stepper","explicit rk4");
	grvy_input_register_char("code/outfile","dat/output.dat");
	grvy_input_register_int("code/verify",0);
	
	// Set default values for runtime parameters
	grvy_input_register_double("run/hmax",1e-2);
	grvy_input_register_int("run/outfreq",1);
	grvy_input_register_double("run/Final_time",10);

	// Print the default values
	message(0,"\nDefault input parameters are as following :");
	message(0,"#### DEFAULT VALUES FOR INPUT PARAMETERS ####");
	message(0,"  Verbosity          :   1 of 1");
	message(0,"  System of eqns     :   'test'");
	message(0,"  Time step          :   0.01");
	message(0,"  Output frequency   :   1 (every time step)");
	message(0,"  Verification mode  :   OFF");
	message(0,"  Final time         :   10 sec");
	message(0,"  Output file        :   dat/output.dat");
	message(0,"############################################");
}

void get_inp()
{
	/* Code behavior */
	// C1.Verbosity Level
    if(grvy_input_fread_int("code/verbosity",&verbosity)==0)
		grvy_input_register_get_int("code/verbosity",&verbosity);
	message(1,"Running in debug mode");
	// C2.ODE System (main or test)
	if(grvy_input_fread_char("code/odesys",&odesys)==0)
		grvy_input_register_get_char("code/odesys",&odesys);
	// C3.Stepper function : Default is explicit RK4
	if(grvy_input_fread_char("code/stepper",&stepper)==0)
		grvy_input_register_get_char("code/stepper",&stepper);
	set_stepper();
	// C4.Output file
	if(grvy_input_fread_char("code/outfile",&outfilename)==0)
		grvy_input_register_get_char("code/outfile",&outfilename);
	// C5.Verification mode
	if(grvy_input_fread_int("code/verification",&verify)==0)
		grvy_input_register_get_int("code/verification",&verify);
	
	/* Runtime parameters */
	// R1.Time step 
	if(grvy_input_fread_double("run/hmax",&tstep)==0)
		grvy_input_register_get_double("run/hmax",&tstep);
	// R2.Output frequency
	if(grvy_input_fread_int("run/outfreq",&outfreq)==0)
		grvy_input_register_get_int("run/outfreq",&outfreq);
	// R3.Final time
	if(grvy_input_fread_double("run/Final_time",&tf)==0)
		grvy_input_register_get_double("run/Final_time",&tf);


    grvy_input_fclose();
}

void set_stepper()
{

	char msg[100];
	char stepper_str[22];
	if(strcasecmp(stepper,"explicit rk4")==0)
	{
		stepper_fun = gsl_odeiv2_step_rk4;
		sprintf(stepper_str,"Explicit RK4");
	}

	else if(strcasecmp(stepper,"explicit rk23")==0)
	{	
		stepper_fun = gsl_odeiv2_step_rk2;
		sprintf(stepper_str,"Explicit RK23");
	}
	else if(strcasecmp(stepper,"backward euler")==0)
	{
		stepper_fun = gsl_odeiv2_step_rk1imp;
		sprintf(stepper_str,"Backward Euler");
	}
	else
		{
			stepper_fun = gsl_odeiv2_step_rk4; //Default stepper
			sprintf(stepper_str,"Explicit RK4");
			printf(" Unknown stepper option, using RK4\n");
		}

	sprintf(msg,"Using the stepper %s\n",stepper_str);
	message(0,msg);
}
