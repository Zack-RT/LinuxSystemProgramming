CC=gcc
CFLAGS=-g -Wall -std=gnu11
BUILD_DIR = ./build
SRC=$(wildcard *.c)
BIN=$(patsubst %.c, %, $(SRC))
BIN:=$(addprefix $(BUILD_DIR)/, $(BIN))
OBJ=$(patsubst %.c, %.o, $(SRC))
#OBJ:=$(addprefix $(BUILD_DIR)/, $(OBJ))
	
all:$(BUILD_DIR) $(OBJ) $(BIN)

debug:
	@echo $(SRC) 
	@echo $(BIN) 
	@echo $(OBJ)

$(BUILD_DIR):
	[ -d $@ ] || mkdir $@

$(BIN):%:%.o
	$(CC) -o $@ $(CFLAGS) $?

$(OBJ):%.o:%.c
	$(CC) -c -o $(addprefix $(BUILD_DIR)/, $@) $(CFLAGS) $?

.PHONY:clean
clean:
	-$(RM) ./build/* 