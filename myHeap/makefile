# Variables
CC = g++
CFLAGS = -Wall

# Project Sources
LIB = myHeap.cpp
EXP = myExceptions.cpp # ---------- myException library source '.cpp' file
SRC = main.cpp # ---------- Project '.cpp' file

# Binaries
EXEC = main


# ================================== Rules ===================================

# Compile EXEC Rule
$(EXEC): $(LIB) $(EXP) $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

# Run EXEC Rule
run: $(EXEC)
	./$(EXEC)

# Clean EXEC Rule
clean:
	rm -f $(EXEC)