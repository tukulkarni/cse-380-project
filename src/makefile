include ../makefile.in

# Files
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
EXEC := run
# Compiler, libraries and flags
CC := gcc
CFLAGS := -O0
LDFLAGS := -lm
INC := -I../inc/

# Targets 
all : $(OBJ)
	$(CC) -o $(EXEC) $(CFLAGS) $^

%.o : %.c
	$(CC) -c $< $(INC)

# Phony targets : always out-of-date
.PHONY : clean 

clean : 
	@rm -f *.o ~* *~ *.swp $(EXEC)
