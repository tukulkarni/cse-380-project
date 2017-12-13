#include "testsuite.h"

// Tests for parsing functions
void test_temp(void)
{
	printf("Inside test_temp\n");
}


void test_parse()
{
	char * charptr;
	int int1;
	CU_ASSERT(grvy_input_fopen("parsetest.dat")==GRVY_SUCCESS);
	CU_ASSERT(grvy_input_fread_int("test1/integer1",&int1)==GRVY_SUCCESS);
	CU_ASSERT(grvy_input_fread_char("test1/string1",&charptr)==GRVY_SUCCESS);

	// Test if read data is correct
	CU_ASSERT(int1==100);
	CU_ASSERT_STRING_EQUAL(charptr,"some path");

	grvy_input_fread_int("test1/integer2",&int1);
	CU_ASSERT_FALSE(int1==100000);

	grvy_input_fclose();
}

void test_register()
{
	double random = rand();
	double test;
	// Test for registering an input
	grvy_input_fopen("parsetest.dat");
	grvy_input_register_double("test2/float1",random);
	// Now read and check
	grvy_input_register_get_double("test2/float1",&test);
	CU_ASSERT_DOUBLE_EQUAL(test,random,1e-15);
	grvy_input_fclose();
}

void test_free_param()
{
	char * freeparam;
	grvy_input_fopen("parsetest.dat");
	grvy_input_fread_char("free",&freeparam);
	// Test that free parameters are read correctly,
	// and that strings with spaces can be parsed
	CU_ASSERT_STRING_EQUAL(freeparam,"Free parameter");
	grvy_input_fclose();
}
