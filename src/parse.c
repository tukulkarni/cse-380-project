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
	// Set default values for some parameters
	if(grvy_input_register_double("Time_step",1e-2)!=1)
		printf("Could not register time step default\n");

}

void get_inp()
{
    if(grvy_input_fread_double("Time_step",&tstep))
        printf("Time step = %.3E\n",tstep);
	else
	{
		grvy_input_register_get_double("Time_step",&tstep);
		printf("Using default time step = %.3E\n",tstep);
	}
    grvy_input_fclose();
}

