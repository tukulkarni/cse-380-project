include ../makefile.in

# Files
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
EXEC := run
# Compiler, libraries and flags
CC := gcc
CFLAGS := -O0
INC := -I../inc
DEBUG := -Wall -Wextra -Wshadow

# Targets 
all : $(OBJ)
	$(CC) -o $(EXEC) $^ $(CFLAGS) $(LIBS)

%.o : %.c 
	$(CC) -c $< $(INC) $(DEBUG)

# Phony targets : always out-of-date
.PHONY : clean 

clean : 
	@rm -f *.o ~* *~ *.swp $(EXEC)
