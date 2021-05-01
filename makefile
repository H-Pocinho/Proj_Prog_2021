CC = gcc 

TARGET = covid19

CFLAGS = -std=c11 -O3

all:
		$(CC) -Wall -o $(TARGET) covid19.c 

clear:
		rm $(TARGET)