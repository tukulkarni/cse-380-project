#include "parse.h"
#include "functions.h"
#include<assert.h>
#include<CUnit/CUnit.h>
#include<CUnit/Basic.h>

void test_temp(void);
void test_parse();
void test_register();
void test_free_param();

void testBE();
void testRK4();
void testRK2();
double testsolver(const gsl_odeiv2_step_type * GSLstepper,double h[]);

double linreg(const double x[], const double y[],int n);
int test_f(double t,const double y[],double f[],void *params);
int test_dfdy(double t,const double y[],double *dfdy, double dfdt[], void *params);
