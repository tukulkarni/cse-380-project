include ../makefile.defs

TESTSRC := testparse.c testsolver.c main.c
TESTOBJ :=	$(patsubst %.c,%.o,$(TESTSRC))

all : $(TESTOBJ) $(filter-out $(SRC_DIR)/main.c,$(SRC))
	@$(CC) -o testsuite $^ $(INC) $(LIBS) $(LDFLAGS) $(LIBS) \
	-Wl,-rpath,$(GRVY_LIB_DIR),-rpath,$(CUnit_LIB_DIR)

%.o : %.c
	$(CC) -c $< $(INC) $(LIBS) $(LDFLAGS) $(DEBUG)

.PHONY : clean
clean : 
	rm -f *.o testsuite
