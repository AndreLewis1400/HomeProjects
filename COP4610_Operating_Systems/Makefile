# Makefile for COP4610 Operating Systems - Banking System Assignment
# Author: Andre Lewis
# Course: COP4610 Operating Systems - FIU

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread -g
LDFLAGS = -pthread

# Target executable
TARGET = banking_system

# Source files
SOURCES = banking_system.c

# Object files (automatically generated from sources)
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build successful! Executable: $(TARGET)"

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean completed"

# Run the program
run: $(TARGET)
	@echo "Running $(TARGET)..."
	./$(TARGET)

# Debug build with additional flags
debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Release build with optimization
release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

# Install (copy to system path - optional)
install: $(TARGET)
	@echo "Installing $(TARGET) to /usr/local/bin (requires sudo)"
	sudo cp $(TARGET) /usr/local/bin/

# Uninstall (remove from system path - optional)
uninstall:
	@echo "Removing $(TARGET) from /usr/local/bin (requires sudo)"
	sudo rm -f /usr/local/bin/$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the banking system (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  run      - Build and run the program"
	@echo "  debug    - Build with debug flags"
	@echo "  release  - Build optimized release version"
	@echo "  install  - Install to system path (requires sudo)"
	@echo "  uninstall- Remove from system path (requires sudo)"
	@echo "  help     - Show this help message"

# Phony targets (not actual files)
.PHONY: all clean run debug release install uninstall help

# Dependencies
banking_system.o: banking_system.c
