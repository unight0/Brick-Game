#CC - code compiler
#CL - code linker
#R_OBJ - result object

CC = g++
CL = g++
C_OPT = -Og -g -Wall -Wpedantic -Wextra
L_OPT = -lSDL2_image -lSDL2_ttf `sdl2-config --libs`
C_OBJS = *.cpp
L_OBJS = *.o
R_OBJ = brick-game 

BIN_DIR = bin
SRC_DIR = src

.DEFAULT_TARGET := all

all: build link                                       

link:
	$(CL) $(BIN_DIR)/$(L_OBJS) $(L_OPT) -o $(R_OBJ)

build:
	$(CC) -c $(SRC_DIR)/$(C_OBJS) $(C_OPT)
	@mv $(L_OBJS) $(BIN_DIR)

run: $(R_OBJ)
	./$(R_OBJ)
