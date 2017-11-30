include ../makefile.in
TEST := $(wildcard *.c)
INC := -I../inc

all : $(TEST) $(SRC)
	echo $(SRC)
	gcc -o testsuite $^ $(INC) $(LIBS)
.PHONY : clean
clean : 
	rm -f *.o 
