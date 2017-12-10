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
	// Set default values for runtime parameters
	grvy_input_register_double("run/Time_step",1e-2);
	grvy_input_register_int("run/outfreq",1);
	grvy_input_register_double("run/Final_time",10);

	// If debug mode is set, print the default values
	message(1,"------ DEFAULT VALUES FOR GRVY PARAMETERS ------");
	message(1,"	\tVerbosity        : 1 of 1\n");
	message(1,"	\tSystem of eqns   : 'test'\n");
	message(1,"	\tTime step        : 0.01\n");
	message(1,"	\tOutput frequency : 1 (every time step)\n");
	message(1,"------------------------------------------------");
}

void get_inp()
{
	// Verbosity Level
    if(grvy_input_fread_int("code/verbosity",&verbosity)==0)
	{
		grvy_input_register_get_int("code/verbosity",&verbosity);
		printf("Verbosity level not set, running verbose mode\n");
	}
	message(1,"Running in debug mode");
	
	// ODE System (main or test)
	if(grvy_input_fread_char("code/odesys",&odesys)==0)
	{
		grvy_input_register_get_char("code/odesys",&odesys);
	}

	// Stepper function : Default is explicit RK4
	if(grvy_input_fread_char("code/stepper",&stepper)==0)
	{
		grvy_input_register_get_char("code/stepper",&stepper);
		message(1,"Using default stepper: RK4");
	}
	set_stepper();
	// Time step 
	if(grvy_input_fread_double("run/Time_step",&tstep)==0)
	{
		grvy_input_register_get_double("run/Time_step",&tstep);
		message(1,"Using default time step = 0.01");
	}
	// Output frequency
	if(grvy_input_fread_int("run/outfreq",&outfreq)==0)
	{
		grvy_input_register_get_int("run/outfreq",&outfreq);
		message(1,"Using default value of outfreq = 1\n");
	}
	// Output file
	if(grvy_input_fread_char("code/outfile",&outfilename)==0)
	{
		grvy_input_register_get_char("code/outfile",&outfilename);
		message(1,"Using default output file 'dat/output.dat'");
	}

	// Final time
	if(grvy_input_fread_double("run/Final_time",&tf)==0)
	{
		grvy_input_register_get_double("run/Final_time",&tf);
		message(1,"Using default final time = 10");
	}
	
    grvy_input_fclose();
}

void set_stepper()
{

	char msg[100];
	if(strcasecmp(stepper,"explicit rk4"))
		stepper_fun = gsl_odeiv2_step_rk4;
	else if(strcasecmp(stepper,"explicit rk23"))
			stepper_fun = gsl_odeiv2_step_rk2;
	else if(strcasecmp(stepper,"backward euler"))
			stepper_fun = gsl_odeiv2_step_rk1imp;
	else if(strcasecmp(stepper,"Runge Kutta Fehlenberg"))
			stepper_fun = gsl_odeiv2_step_rkf45;
	else
		{
			stepper_fun = gsl_odeiv2_step_rk4; //Default stepper
			printf(" Unknown stepper option, using RK4\n");
		}
	sprintf(msg,"Using the stepper %s\n",stepper);
	message(1,msg);
}
