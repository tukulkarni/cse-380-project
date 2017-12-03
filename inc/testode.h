int testode(void);
double eulerfwd(double y0,double dt,double tf,double (*f)(double));
double dydt(double y);
int test_f(double t,const double y[],double f[],void *params);
int test_dfdy(double t,const double y[],double *dfdy, double dfdt[], void *params);
