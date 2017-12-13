include makefile.defs

exec :
	$(MAKE) -C $(SRC_DIR)

all : exec test doc

check :
	@$(MAKE) -C $(TEST_DIR)
	@test/testsuite

coverage :
	@$(MAKE) -C $(SRC_DIR) coverage
	@src/a.out > /dev/null
	@rm src/a.out
	@echo ' ----------------------------------------------------'
	@echo ' ------------ Coverage statistics -------------------'
	@gcov $(SRC_DIR)/*.c

doc :		
	
.PHONY : clean
clean : 
	@$(MAKE) -C $(SRC_DIR) 	clean
	@$(MAKE) -C $(TEST_DIR) clean
	@rm -f $(EXEC) *.gcov
