# Makefile for Process Creation Example

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = process_creation
SOURCE = main.c

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Build with debugging symbols
debug: CFLAGS += -DDEBUG
debug: $(TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Run with debugging
debug-run: debug
	gdb ./$(TARGET)

# Run with system call tracing
trace: $(TARGET)
	strace ./$(TARGET)

# Run with memory checking
memcheck: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all        - Build the program (default)"
	@echo "  debug      - Build with debugging symbols"
	@echo "  clean      - Remove build artifacts"
	@echo "  run        - Build and run the program"
	@echo "  debug-run  - Build with debug symbols and run with GDB"
	@echo "  trace      - Run with system call tracing"
	@echo "  memcheck   - Run with memory leak checking"
	@echo "  help       - Show this help message"

.PHONY: all debug clean run debug-run trace memcheck help
