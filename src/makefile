include ../makefile.in
include ../makefile.tpl.in

# Files
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
EXEC := run
# Compiler, libraries and flags
CC := gcc
CFLAGS := -O0
INC := -I../inc -I$(GRVY_INC_DIR)
LDFLAGS := -L$(GRVY_LIB_DIR)
DEBUG := -Wall -Wextra -Wshadow

# Targets 
all : $(OBJ)
	$(CC) -o $(EXEC) $^ $(CFLAGS) $(LIBS) $(INC) $(LDFLAGS)

%.o : %.c 
	$(CC) -c $< $(DEBUG) $(INC)

# Phony targets : always out-of-date
.PHONY : clean 

clean : 
	@rm -f *.o ~* *~ *.swp $(EXEC)
