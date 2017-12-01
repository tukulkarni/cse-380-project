include makefile.in

run : $(OBJ)

%.o : %.c
	$(MAKE) -C $(SRC_DIR) // just compiles source code
		
	
.PHONY : clean
clean : 
	@$(MAKE) -C $(SRC_DIR) 	clean
