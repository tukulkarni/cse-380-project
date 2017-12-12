#include "functions.h"

int print_header()
{
	outfile = fopen(outfilename,"w+");
	if(outfile==NULL)
	{
		printf("Error: Could not open file");
		return 3;	
	}
	
	// Print header
	fprintf(outfile,"###\n");
	fprintf(outfile,"# Charged Particle in Vertical Electric Field \n");	
	fprintf(outfile,"#-------- Runtime parameters ----#\n");
	fprintf(outfile,"# Solver used : %s\n",stepper);
	fprintf(outfile,"# Time step : %f\n",tstep);
	fprintf(outfile,"#--------------------------------#\n");
	fprintf(outfile,"%-12s\t%-12s\t%-12s\t%-12s\t%-12s\t%-12s\t%-12s\n",
			"#    t","     x","     y","     z","     u",
			"     v","     w");
	fprintf(outfile,"###\n");
	return 0;
}

void message(int type,char text[])
{
	// Usage : wrapper for printf to control what to print according
	//			to the debug level parameter.
	// 			higher the level, higher is the verbosity
	if(verbosity>=type)
		printf("%s\n",text);
}
