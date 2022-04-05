LIBDIR := lib
OBJDIR := builds
EXEDIR := bin
TESTS  := tests

EXE    := $(EXEDIR)/calc
LIBS   := $(addprefix $(LIBDIR)/, libdynamic.so liblogger.a libstatic.a)
SRCS   := $(wildcard src/*.cpp)
OBJS   := $(addprefix $(OBJDIR)/,$(patsubst src/%.cpp,%.o,$(SRCS)))
CASES  := $(patsubst $(TESTS)/test%.in,test%,$(wildcard $(TESTS)/test*.in))
OUTFILE := $(patsubst $(TESTS)/test%.in,$(TESTS)/test%sample.out,$(wildcard $(TESTS)/test*.in))

INPUTS := input.in

build: $(EXE)
	@echo "Executable successfully built!"

libs: $(LIBDIR)/libdynamic.so $(LIBDIR)/libstatic.a
	@echo "Libraries built!"

prepare: 
	@read -p "Enter Input File Path: " FILE; echo $$FILE > $(INPUTS)
	@read -p "Enter Output File Path: " FILE; echo $$FILE >> $(INPUTS)
	@read -p "Enter Arguments in proper sequence and with hyphens. For ex: '-a -s -m': " FILE; echo $$FILE >> $(INPUTS)
	@echo "Please make 'run' target to get results!"

run: 
	@if [ -f $(INPUTS) ] ; then \
	 export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$$PWD/lib ; \
	 echo "$(EXE) `head -3 $(INPUTS) | tail -1` < `head -1 $(INPUTS) | tail -1` > `head -2 $(INPUTS) | tail -1` " | bash ; \
	else \
	 echo "Since make 'prepare' was not given, 'run.in' will be taken as input file. Please make sure arguments to 'run.in' are mentioned as comments in the first line of file. A sample 'run.in' is present in PWD." ; \
	 export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$$PWD/lib ; \
	 echo "$(EXE) `head -1 $(PWD)/run.in | cut -c 2-` < $(PWD)/run.in  > $(PWD)/run.out " | bash ; \
	fi;
	@echo "Check output file for result!"

tests: $(CASES)
	@echo "ALL CASES PASSED"

test%:
	@if [ -f $(TESTS)/$@.in ] ; \
	then \
	 export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$$PWD/lib ; \
	 head -n1 $(TESTS)/$@.in | cut -c 2- | bash ; \
	 diff -q $(TESTS)/$@correct.out $(TESTS)/$@sample.out ; \
	 echo "$@ Passed" ; \
	fi;
	
clean:
	@rm -rf $(LIBDIR) $(OBJDIR) $(EXEDIR) error.log
	@rm -f $(OUTFILE) 
	@rm -f $(INPUTS)
	@echo "All unnecessary files cleaned!" 

$(EXE): $(OBJDIR)/main.o $(LIBS) | $(EXEDIR) 
	@g++ -o $@ -I include $< -L lib -ldynamic -llogger -lstatic

$(OBJDIR)/%.o: src/%.cpp include/matrix.h include/Logger.h | $(OBJDIR)
	@g++ -o $@ -c -I include $<

$(OBJDIR)/matrix.o: src/matrix.cpp include/matrix.h | $(OBJDIR)
	@g++ -fPIC -o $@ -c -I include $< 

$(LIBDIR)/libdynamic.so: $(OBJDIR)/matrix.o | $(LIBDIR)
	@g++ -shared -o $@ $^
	
$(LIBDIR)/libstatic.a: $(OBJDIR)/static.o | $(LIBDIR)
	@ar rcs $@ $^

$(LIBDIR)/liblogger.a: $(OBJDIR)/Logger.o | $(LIBDIR)
	@ar rcs $@ $^

$(OBJDIR): 
	@mkdir -p $@

$(LIBDIR): 
	@mkdir -p $@

$(EXEDIR): 
	@mkdir -p $@
