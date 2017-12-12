include ../makefile.defs

TESTSRC := testparse.c
TESTOBJ :=	$(patsubst %.c,%.o,$(TESTSRC))

all : $(TESTOBJ)
	gcc -o testsuite $^ $(INC) $(LIBS) $(LDFLAGS) $(LIBS) \
	-Wl,-rpath,$(GRVY_LIB_DIR),-rpath,$(CUnit_LIB_DIR)

%.o : %.c
	gcc -c $< $(INC) $(LIBS) $(LDFLAGS) $(DEBUG)
.PHONY : clean
clean : 
	rm -f *.o 
