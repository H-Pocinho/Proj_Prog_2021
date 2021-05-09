CC = gcc 

TARGET = covid19

CFLAGS = -std=c11 -O3

all:
		$(CC) -Wall -o $(TARGET) &(CFLAGS) covid19.c 

clear:
		rm $(TARGET)