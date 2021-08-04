# C_SOURCES = $(shell find -name "*.c")
# HEADER_DIR = ./headers/
# OUTPUT_NAME = nvm.o
# OBJ = ${C_SOURCES:.c=.o}
# 
# CFLAGS = -I ${HEADER_DIR}
# run: ${OUTPUT_NAME}
# 	./${OUTPUT_NAME}
# 
# %.o: %.c
# 	gcc ${CFLAGS} -c $< -o $@
# 
# ${OUTPUT_NAME}: ${OBJ}
# 	gcc $^ -o $@
# 
# clean:
# 	rm ${OBJ} ${OUTPUT_NAME}

# App name
TARGET = nvm

CC = gcc

# App directories
INC_DIR := ./headers
LIB_DIR := .
SRC_DIR := .
OUT_DIR := ./out

# App artifacts
INC := $(shell find $(INC_DIR) -type d | sed -e 's/^/-I/' | grep -v ".git" | tr '\n' ' ')
LIB := $(shell find $(LIB_DIR) -type d | sed -e 's/^/-I/' | grep -v ".git" | tr '\n' ' ')
SRC := $(shell find $(SRC_DIR) \( -name "*.c" \))
OBJ := $(SRC:.c=.o)
OUT := $(OUT_DIR)/$(TARGET)
FLG := -O2 -I/usr/include
DBG_FLG := -DDEBUG

# make
$(TARGET):
	mkdir -p $(OUT_DIR)
	$(CC) $(SRC) $(INC) $(LIB) $(FLG) -o $(OUT_DIR)/$@ $^

# clean
clean:
	rm -rf $(OUT_DIR)

# run
run: $(TARGET)
	$(OUT)

debug:
	mkdir -p $(OUT_DIR)
	cp ~/neoncode/prog.neonbin .
	$(CC) $(SRC) $(INC) $(LIB) $(FLG) $(DBG_FLG) -o $(OUT_DIR)/$@ $^
	$(OUT_DIR)/$@