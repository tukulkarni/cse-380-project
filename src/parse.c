// Function file for input parsing routines
#include "parse.h"
#include "functions.h"
#include<stdio.h>
#include<stdlib.h>

void parse_set()
{
	int q;
	// Sets up input parsing with grvy
	q=grvy_input_fopen("../input");
	if(q!=1)
	{
		grvy_input_fclose();
		exit(1);
	}
}

void set_def()
{
	// Set defaluts for code params
	if(grvy_input_register_int("code/Debug_Level",0))
		printf("Setting default output level to standard\n");
	// Set default values for runtime parameters
	if(grvy_input_register_double("run/Time_step",1e-2)!=1)
		printf("Could not register time step default\n");

}

void get_inp()
{
	printf("In get_inp, DEBUG = %d\n",DEBUG);
    if(grvy_input_fread_int("code/Debug_Level",&debuglevel)==0)
	{
		grvy_input_register_get_int("code/Debug_Level",&debuglevel);
		printf("Debug level not set, running standard mode\n");
	}
	else if(debuglevel)
		printf("Running in debug mode\n");
	
	if(grvy_input_fread_double("run/Time_step",&tstep)==0)
	{
		grvy_input_register_get_double("run/Time_step",&tstep);
		if(debuglevel)
			printf("Using default time step = %.3E\n",tstep);
	}

	
    grvy_input_fclose();
}

