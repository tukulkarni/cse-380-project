#include "grvy.h"
#include<gsl/gsl_odeiv2.h>

/* Parse variables */
int verbosity;
char *odesys; //Either 'test' or 'main'
char *stepper;
const gsl_odeiv2_step_type * stepper_fun; // Pointer to stepper function
char *outfilename;
int verify;

double tstep, tf;
int outfreq;

/* Variables */
#define DEBUG 1
#define STANDARD 0
#define GRVY_SUCCESS 100

/* Parsing routines */
int input_parse();
void parse_set();   // Set up grvy parsing capabilities
void set_def();	    // Set the DEFault values
void get_inp();	    // Get input from input file (parse)
void set_stepper(); // Set the correct GSL stepper based on input
