SRC_FILES=main.c
CC_FLAGS=-Wall -Wextra -g -std=c11
CC=gcc
BIN=mac

all:
	@${CC} ${SRC_FILES} ${CC_FLAGS} -o ${BIN}

run:
	@${CC} ${SRC_FILES} ${CC_FLAGS} -o ${BIN}
	clear
	@./${BIN}