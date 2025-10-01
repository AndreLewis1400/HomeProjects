CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread
TARGET = wordpuzzle
SOURCES = wordpuzzle.c
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Compile the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJECTS) $(TARGET)

# Install target (optional)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall target (optional)
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Test target
test: $(TARGET)
	@echo "Testing wordpuzzle with sample input..."
	@echo "abcdefghijklmnop" | ./$(TARGET) -verbose -len 8,9

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build the wordpuzzle executable"
	@echo "  clean     - Remove object files and executable"
	@echo "  test      - Run a simple test"
	@echo "  install   - Install to /usr/local/bin"
	@echo "  uninstall - Remove from /usr/local/bin"
	@echo "  help      - Show this help message"

.PHONY: all clean install uninstall test help 