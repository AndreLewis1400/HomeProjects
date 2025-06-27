# Makefile for railcipher assignment

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = railcipher
SRC = railcipher.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean 