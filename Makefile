CC=g++
SOURCE=magcave.cpp minimax.cpp gameboard.cpp gameinfo.cpp
HEADERS=minimax.h gameboard.h gameinfo.h
NAME=magcave
OUTPUT=-o ${NAME}
INCLUDE=-I/usr/include/ncurses
LINKER=-lncurses -lpthread
WARN=-Wall

all: ${SOURCE} ${HEADERS}
	${CC} ${SOURCE} ${INCLUDE} ${LINKER} ${WARN} ${OUTPUT}
