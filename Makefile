CC = gcc
CFLAGS = -Wall -g -fsanitize=address
INC = ./include
RAYLIB_INC = ./raylib/include
RAYLIB_LIB = ./raylib/lib
LDFLAGS = -lraylib -lGL -lm -ldl -lrt -lX11 -fsanitize=address -Wl,-rpath=$(RAYLIB_LIB)

SRCS_DIR = src
OBJS_DIR = obj
LIB_DIR = lib
BIN_DIR = bin

SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))
TARGET_EXE = $(BIN_DIR)/main

.PHONY: all run clean

all: $(TARGET_EXE)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INC) -I$(RAYLIB_INC) -c $< -o $@

$(TARGET_EXE): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -L$(RAYLIB_LIB) $(LDFLAGS) -o $@

run: $(TARGET_EXE)
	LD_LIBRARY_PATH=$(RAYLIB_LIB) ./$(TARGET_EXE)

clean:
	rm -rf $(OBJS_DIR) $(LIB_DIR) $(BIN_DIR)
