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
	q=grvy_input_fopen("INPUT");
	if(q!=1)
	{
		grvy_input_fclose();
		exit(1);
	}
}

void set_def()
{
	// Set defaluts for code params
	if(grvy_input_register_int("code/verbosity",0))
		printf("Setting default output level to standard\n");
	if(grvy_input_register_char("code/odesys","test"))
		printf("Setting default system to 'test'\n");
	// Set default values for runtime parameters
	if(grvy_input_register_double("run/Time_step",1e-2)!=1)
		printf("Could not register time step default\n");
	if(grvy_input_register_int("run/outfreq",1)!=1)
		printf("Could not register output freq default\n");
}

void get_inp()
{
	// Debug Level
    if(grvy_input_fread_int("code/verbosity",&verbosity)==0)
	{
		grvy_input_register_get_int("code/verbosity",&verbosity);
		printf("Debug level not set, running standard mode\n");
	}
	else if(verbosity)
		printf("Running in debug mode\n");
	
	// ODE System (main or test)
	if(grvy_input_fread_char("code/odesys",&odesys)==0)
	{
		grvy_input_register_get_char("code/odesys",&odesys);
		if(verbosity)
			printf("Using default time step = %.3E\n",tstep);
	}

	// Stepper function : Default is explicit RK4
	if(grvy_input_fread_char("code/stepper",&stepper)==0)
	{
		grvy_input_register_get_char("code/stepper",&stepper);
		if(verbosity)
			printf("Using default stepper: RK4\n");
	}
	set_stepper();
	// Time step 
	if(grvy_input_fread_double("run/Time_step",&tstep)==0)
	{
		grvy_input_register_get_double("run/Time_step",&tstep);
		if(verbosity)
			printf("Using default time step = %.3E\n",tstep);
	}
	// Output frequency
	if(grvy_input_fread_int("run/outfreq",&outfreq)==0)
	{
		grvy_input_register_get_int("run/outfreq",&outfreq);
		if(verbosity)
			printf("Using default value of outfreq=1\n");
	}

    grvy_input_fclose();
}

void set_stepper()
{
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

if(verbosity)
	printf("Using the stepper %s\n",stepper);
}
