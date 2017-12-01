#include<stdio.h>
#include<math.h>
#include<assert.h>
#include"functions.h"
#include"parse.h"

int main(){
	double yf,anal;
	/* Input parsing */
	parse_set();	// Setup GRVY for use
	set_def();		// Set default values
	get_inp();		// Read input file

	/* Main routine */
	yf = eulerfwd(1,tstep,2,dydt);
	anal = exp(2);
	printf("Running with dt = %.3E\n",tstep);
	printf("numerical = %lf\t analytic = %lf\n",yf,anal);
	return 0;
}

double dydt(double y)
{
	double dy;
	dy = y;
	return dy;
}
