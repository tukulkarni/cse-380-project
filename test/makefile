include ../makefile.in
include ../makefile.tpl.in

TEST := $(wildcard *.c)
INC := -I../inc -I$(GRVY_INC_DIR)
LDLIBS := -L$(GRVY_LIB_DIR)

all : $(TEST) $(SRC)
	echo $(SRC)
	gcc -o testsuite $^ $(INC) $(LIBS) $(LDLIBS)
.PHONY : clean
clean : 
	rm -f *.o 
