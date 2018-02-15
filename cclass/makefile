# Compiler stuff
CC=gcc
CFLAGS=-Wall -fno-strict-aliasing

# Environment
RM=rm
CLEAR=clear

# Extensions
OBJ=o
BIN=exe
SRC=c
HDR=h

# Cclass base
CCLSDIR=./cclass
CCLASS=$(CCLSDIR)/cclass
ERR=$(CCLSDIR)/err

# Class names
CCLS_STRING=cclsString
CCLS_ANIMAL=cclsAnimal
CCLS_CAT=cclsCat
CCLS_SWATCAT=cclsSwatCat
CCLS_SHARK=cclsShark
CCLS_SQUID=cclsSquid
CCLS_SHTP=cclsSharkSquid
CCLS_MBP=cclsManBearPug
CCLS_STRSTACK=cclsString_stack

# Unit tests
SINH=simple_inheritance
TEST_SINH=$(CCLASS).$(OBJ) $(ERR).$(OBJ) $(CCLS_STRING).$(OBJ) $(CCLS_ANIMAL).$(OBJ) $(CCLS_CAT).$(OBJ)

HINH=hierarchy_inheritance
TEST_HINH=$(CCLASS).$(OBJ) $(ERR).$(OBJ) $(CCLS_STRING).$(OBJ) $(CCLS_ANIMAL).$(OBJ) $(CCLS_CAT).$(OBJ) $(CCLS_SWATCAT).$(OBJ)

DMONDH=diamond_inheritance
TEST_DMONDH=$(CCLASS).$(OBJ) $(ERR).$(OBJ) $(CCLS_STRING).$(OBJ) $(CCLS_ANIMAL).$(OBJ) $(CCLS_SHARK).$(OBJ) $(CCLS_SQUID).$(OBJ) $(CCLS_SHTP).$(OBJ)

STRT=string_test
TEST_STRT=$(CCLASS).$(OBJ) $(ERR).$(OBJ) $(CCLS_STRING).$(OBJ)

MULINH=multiple_inheritance
TEST_MULINH=$(CCLASS).$(OBJ) $(ERR).$(OBJ) $(CCLS_STRING).$(OBJ) $(CCLS_MBP).$(OBJ)

ASTACK=stack_allocation
TEST_ASTACK=$(CCLASS).$(OBJ) $(ERR).$(OBJ) $(CCLS_STRSTACK).$(OBJ)

tests: compile_tests
	echo "TESTS START"
	./$(STRT).$(BIN)
	./$(HINH).$(BIN)
	./$(DMONDH).$(BIN)
	./$(MULINH).$(BIN)
	./$(ASTACK).$(BIN)
	./$(SINH).$(BIN)
	
compile_tests: $(HINH).$(BIN) $(DMONDH).$(BIN) $(STRT).$(BIN) $(MULINH).$(BIN) $(ASTACK).$(BIN) $(SINH).$(BIN)

# Simple inheritance test
$(SINH).$(BIN): $(SINH).$(OBJ) $(TEST_SINH)
	$(CC) $^ -o $@ $(CFLAGS)

# Hierarchy inheritance test
$(HINH).$(BIN): $(HINH).$(OBJ) $(TEST_HINH)
	$(CC) $^ -o $@ $(CFLAGS)

$(HINH).$(OBJ): $(HINH).$(SRC)
	$(CC) -c $< -o $@ $(CFLAGS)

# Diamond inheritance
$(DMONDH).$(BIN): $(DMONDH).$(OBJ) $(TEST_DMONDH)
	$(CC) $^ -o $@ $(CFLAGS)

$(DMONDH).$(OBJ): $(DMONDH).$(SRC)
	$(CC) -c $< -o $@ $(CFLAGS)
	
# Multiple inheritance
$(MULINH).$(BIN): $(MULINH).$(OBJ) $(TEST_MULINH)
	$(CC) $^ -o $@ $(CFLAGS)

$(MULINH).$(OBJ): $(MULINH).$(SRC)
	$(CC) -c $< -o $@ $(CFLAGS)

# String test
$(STRT).$(BIN): $(STRT).$(OBJ) $(TEST_STRT)
	$(CC) $^ -o $@ $(CFLAGS)

$(STRT).$(OBJ): $(STRT).$(SRC)
	$(CC) -c $< -o $@ $(CFLAGS)

# String on the stack test
$(ASTACK).$(BIN): $(ASTACK).$(OBJ) $(TEST_ASTACK)
	$(CC) $^ -o $@ $(CFLAGS)

$(ASTACK).$(OBJ): $(ASTACK).$(SRC)
	$(CC) -c $< -o $@ $(CFLAGS)
	
# Cclass base
$(ERR).$(OBJ): $(ERR).$(SRC) $(ERR).$(HDR)
	$(CC) -c $< -o $@ $(CFLAGS)
	
$(CCLASS).$(OBJ): $(CCLASS).$(SRC) $(CCLASS).$(HDR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Classes
$(CCLS_STRING).$(OBJ): $(CCLS_STRING).$(SRC) $(CCLS_STRING).$(HDR)
	$(CC) -c $< -o $@ $(CFLAGS)
	
$(CCLS_ANIMAL).$(OBJ): $(CCLS_ANIMAL).$(SRC) $(CCLS_ANIMAL).$(HDR)
	$(CC) -c $< -o $@ $(CFLAGS)
	
$(CCLS_CAT).$(OBJ): $(CCLS_CAT).$(SRC) $(CCLS_CAT).$(HDR)
	$(CC) -c $< -o $@ $(CFLAGS)
	
$(CCLS_SWATCAT).$(OBJ): $(CCLS_SWATCAT).$(SRC) $(CCLS_SWATCAT).$(HDR)
	$(CC) -c $< -o $@ $(CFLAGS)
	
$(CCLS_SHARK).$(OBJ): $(CCLS_SHARK).$(SRC) $(CCLS_SHARK).$(HDR)
	$(CC) -c $< -o $@ $(CFLAGS)
	
$(CCLS_SQUID).$(OBJ): $(CCLS_SQUID).$(SRC) $(CCLS_SQUID).$(HDR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(CCLS_SHTP).$(OBJ): $(CCLS_SHTP).$(SRC) $(CCLS_SHTP).$(HDR)
	$(CC) -c $< -o $@ $(CFLAGS)
	
$(CCLS_MBP).$(OBJ): $(CCLS_MBP).$(SRC) $(CCLS_MBP).$(HDR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(CCLS_STRSTACK).$(OBJ): $(CCLS_STRSTACK).$(SRC) $(CCLS_STRSTACK).$(HDR)
	$(CC) -c $< -o $@ $(CFLAGS)
	
clean: clean_bin clean_obj
	
clean_obj:
	$(RM) *.$(OBJ)
	$(RM) $(CCLSDIR)/*.$(OBJ)

clean_bin:
	$(RM) *.$(BIN)
