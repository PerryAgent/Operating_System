all: bin/calc

build: bin/calc

prepare: 
	@echo "Give path of input in the format: tests/sample<1/2/3/4>.in: "; \
	read inp; \
	INP ?= inp
	@echo "Give path of input in the format: tests/sample<1/2/3/4>.in: "; \
	read out;
	OUT = $$out 
	@echo $(INP)
	@echo $(OUT)

libs: lib/libdynamic.so lib/libstatic.a
prepare:
	@read -p "Enter Input File Path.: " FILE; \
	INPFILEPATH=`cat $(FILE)`; \
	read -p "Enter Output File Path: " FILE; \
	OUTFILEPATH="$$FILE"; \
	read -p "Enter arguments with proper hyphens and in proper order: " FILE; \
	ARG="$$FILE"
	@echo $$INPFILEPATH
	@if [ -f $(INPFILEPATH) ] ; \
	then \
	 echo "Input File Exists" ; \
	else \
	 echo "Input File Does not Exist" ; \
	fi;

bin/calc: build/main.o libs lib/liblogger.a 
	g++ -o bin/calc -I include build/main.o -L lib -ldynamic -llogger -lstatic

build/main.o: src/main.cpp include/matrix.h include/Logger.h
	g++ -o $@ -c -I include $<

build/matrix.o: src/matrix.cpp include/matrix.h
	g++ -fPIC -o $@ -c -I include $< 

build/static.o: src/static.cpp include/matrix.h
	g++ -o $@ -c -I include $<

build/logger.o: src/Logger.cpp include/Logger.h
	g++ -o $@ -c -I include $<


lib/libdynamic.so: build/matrix.o
	g++ -shared -o $@ $^

lib/libstatic.a: build/static.o 
	ar rcs $@ $^

lib/liblogger.a: build/logger.o 
	ar rcs $@ $^

	