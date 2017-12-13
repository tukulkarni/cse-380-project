#include"testsuite.h"
int main()
{
	// Initialize the test registry
	assert(CU_initialize_registry()==CUE_SUCCESS);
	
	/* ------ Suite : Input Parsing ----- */
	CU_pSuite sParse = CU_add_suite("Input Parsing",NULL,NULL);
	// Test for reading input file correctly
	if((NULL== CU_add_test(sParse,"Read input",test_parse)) || 
	   (NULL== CU_add_test(sParse,"Default",test_register)) ||
	   (NULL == CU_add_test(sParse,"Free param",test_free_param)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* ----- Suite : ODE solvers -------- */
	CU_pSuite sSolvers = CU_add_suite("ODE Solvers",NULL,NULL);
	// Tests for different solver methods based on convergence rates
	if((NULL==CU_add_test(sSolvers,"RK4",testRK4)) ||
	   (NULL==CU_add_test(sSolvers,"RK2",testRK2))	||
	   (NULL==CU_add_test(sSolvers,"Back Euler",testBE)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Run all tests using the CUnit Basic interface
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	
	// Clean-up the registry
	CU_cleanup_registry();
	return 0;
}
