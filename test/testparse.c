#include "parse.h"
#include "functions.h"
#include<stdio.h>
#include<assert.h>
#include<CUnit/CUnit.h>

// Tests for parsing functions
void test_parse()
{
	char * charptr;
	int int1;
	long int int2;
	CU_ASSERT(grvy_input_fopen("parsetest.dat")==GRVY_SUCCESS);
	CU_ASSERT(grvy_input_fread_int("test1/integer1",&int1)==GRVY_SUCCESS);

}
