include ../makefile.in

# Files
OBJ := $(patsubst %.c,%.o,$(SRC))

# Targets 
all : $(OBJ)
	$(CC) -o $(EXEC) $^ $(CFLAGS) $(INC) -Wl,-rpath,\
	$(GRVY_LIB_DIR),-rpath,$(GSL_LIB_DIR) \
	$(LDFLAGS) $(LIBS)

%.o : %.c 
	$(CC) -c $< $(DEBUG) $(INC)

# Phony targets : always out-of-date
.PHONY : clean
clean : 
	rm -f *.o ~* *~ *.swp $(EXEC)
