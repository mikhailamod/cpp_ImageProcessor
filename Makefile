#Assignment 2 makefile

CC=g++
CCFLAGS=-std=c++11
LIBS=-lm -lX

BUILDIR=./build
BINDIR=./bin
INCLUDE=-I./include
SOURCES=./src/menu.cpp ./src/studentDriver.cpp
OBJECTS=menu.o studentDriver.o
TARGET=driver

default: driver

driver: VolImage.o driver.o
	g++ driver.o VolImage.o $(CCFLAGS) -o volimage
	mv *.o ./build
	mv volimage ./bin

VolImage.o: ./src/VolImage.cpp ./include/VolImage.h
	$(CC) $(CCFLAGS) -c ./src/VolImage.cpp -o VolImage.o

driver.o: ./src/driver.cpp
	$(CC) $(CCFLAGS) -c ./src/driver.cpp -o driver.o

clean:
	rm build/*.o
	rm bin/volimage
