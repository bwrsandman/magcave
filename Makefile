CC=g++
SOURCE=magcave.cpp minimax.cpp readxml.cpp gameboard.cpp
HEADERS=minimax.h readxml.h gameboard.h
NAME=magcave
OUTPUT=-o ${NAME}
INCLUDE=-I/usr/include/libxml2
LINKER=-lxml2 -lcurses

all: ${SOURCE} ${HEADERS}
	${CC} ${SOURCE} ${INCLUDE} ${LINKER} ${OUTPUT}
