#include "functions.h"
/* functions to solve 1st order ODE */
double eulerfwd(double y0, double dt, double tf,double (*f)(double))
{
// Solves dy/dt = f(y) with y(0) = y0 and step dt
int i,n;
double y,dy;
n = (int) tf/dt;

y = y0;	// initialize;
for(i=0;i<n;i++)
	{
		dy = (*f)(y);
		y = y + dy*dt;
	}
return y;
}
