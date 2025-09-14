CC=gcc
CFLAGS=-Wall -Wextra -O2
TARGET=pointer_hello_world
SRC=pointer_hello_world.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) 