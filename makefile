include makefile.defs

exec :
	$(MAKE) -C $(SRC_DIR)

all : exec test doc

check :

coverage :
	$(MAKE) -C $(SRC_DIR) coverage
	@src/a.out > /dev/null
	@rm src/a.out
	@echo 'Coverage target built, check source directory'

doc :		
	
.PHONY : clean
clean : 
	@$(MAKE) -C $(SRC_DIR) 	clean
	@rm -f $(EXEC)
