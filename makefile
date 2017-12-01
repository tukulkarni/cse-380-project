include makefile.in

all :
	$(MAKE) -C $(SRC_DIR) $(INCDIR) $(LIBDIR) $(LIBS)
	$(MAKE) -C $(TEST_DIR)
	$(MAKE) -C $(DOC_DIR)
	
.PHONY : clean
clean : 
	@$(MAKE) -C $(SRC_DIR) 	clean
	@$(MAKE) -C $(TEST_DIR) clean
	@$(MAKE) -C $(DOC_DIR)	clean
