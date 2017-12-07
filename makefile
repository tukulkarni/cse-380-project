include makefile.in

all : exec test doc

exec :
	$(MAKE) -C $(SRC_DIR) ## just compiles source code

test :

doc :		
	
.PHONY : clean
clean : 
	@$(MAKE) -C $(SRC_DIR) 	clean
	@rm -f $(EXEC)
