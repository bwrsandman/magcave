CC=g++
SOURCE=magcave.cpp minimax.cpp readxml.cpp gameboard.cpp gameinfo.cpp
HEADERS=minimax.h readxml.h gameboard.h gameinfo.h
NAME=magcave
OUTPUT=-o ${NAME}
INCLUDE=-I/usr/include/libxml2 -I/usr/include/ncurses
LINKER=-lxml2 -lncurses
WARN=-Wall

all: ${SOURCE} ${HEADERS}
	${CC} ${SOURCE} ${INCLUDE} ${LINKER} ${WARN} ${OUTPUT}
