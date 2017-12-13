include ../makefile.defs

TESTSRC := testparse.c testsolver.c main.c
TESTOBJ :=	$(patsubst %.c,%.o,$(TESTSRC))

all : $(TESTOBJ) ../src/functions.c ../src/parse.c ../src/output.c ../src/testode.c
	gcc -o testsuite $^ $(INC) $(LIBS) $(LDFLAGS) $(LIBS) \
	-Wl,-rpath,$(GRVY_LIB_DIR),-rpath,$(CUnit_LIB_DIR)

%.o : %.c
	gcc -c $< $(INC) $(LIBS) $(LDFLAGS) $(DEBUG)

.PHONY : clean
clean : 
	rm -f *.o 
