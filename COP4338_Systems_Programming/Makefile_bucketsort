CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Target program
TARGET = bucketsort

# Default target
all: $(TARGET)

# Compile bucketsort
$(TARGET): bucketsort.c
	$(CC) $(CFLAGS) -o $(TARGET) bucketsort.c

# Clean target
clean:
	rm -f $(TARGET) *.o

# Test target
test: $(TARGET)
	@echo "Testing bucket sort with sample input..."
	@echo "apple carrot kiwi pineapple watermelon" | ./$(TARGET) apple carrot kiwi pineapple watermelon

.PHONY: all clean test 