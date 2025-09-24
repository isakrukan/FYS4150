SRC 		:= utils.o jacobi_eigensolver.o arg_parser.o triDag.o
TESTS 		:= tests.o
BUILD 		:= build

# Distinguishing between mac/linux and windows:
UNAME 		:= $(strip $(OS))

# Checking whether folder exists or not is different between mac/linux and windows
ifeq ($(UNAME),Windows_NT)
$(info I am sorry for using Windows)
INCL 		:= -I./include -I C:/vcpkg/installed/x64-mingw-dynamic/include
LIB 		:= -L C:/vcpkg/installed/x64-mingw-dynamic/lib
DELETE		:= del /Q
define MKDIR 
	if not exist "$(1)" mkdir "$(1)"
endef 
else 
$(info I can't update my mac but I love it so much)
INCL 		:= -I./include
LIB 		:=
DELETE		:= rm -f
define MKDIR 
	mkdir -p "$(1)"
endef 
endif 

define compile_func
	g++ -c $1 $(INCL) $(LIB) -o $2
endef 

OS_message:
	@echo $(UNAME)

outfolder:
	@$(call MKDIR,$(BUILD))

compile:
	@$(call compile_func, tests/test.cpp, test.o)
	@$(call compile_func, src/utils.cpp, utils.o)
	@$(call compile_func, src/triDag.cpp, triDag.o)
	@$(call compile_func, src/jacobi_eigensolver.cpp, jacobi_eigensolver.o)
	@$(call compile_func, src/arg_parser.cpp, arg_parser.o)
	@$(call compile_func, main.cpp, main.o)

link:
	g++ main.o $(SRC) $(LIB) -larmadillo -o $(BUILD)/main	
	g++ test.o $(SRC) $(LIB) -larmadillo -o $(BUILD)/test

clean:
	-$(DELETE) *.o

test:
	./$(BUILD)/test

.PHONY: build
build: outfolder compile link clean

all: build test