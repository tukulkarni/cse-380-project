#include "grvy.h"

/* Parse variables */
int debuglevel;
double tstep;
char *odesys; //Either 'test' or 'main'

/* Variables */
#define DEBUG 1
#define STANDARD 0
#define GRVY_SUCCESS 100
/* Parsing routines */
int input_parse();
void parse_set(); // Set up grvy parsing capabilities
void set_def();	  // Set the DEFault values
void get_inp();	  // Get input from input file (parse)
