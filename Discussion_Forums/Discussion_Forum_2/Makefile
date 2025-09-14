CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = discussion_forum_2

all: $(TARGET)

$(TARGET): discussion_forum_2.c
	$(CC) $(CFLAGS) -o $(TARGET) discussion_forum_2.c

clean:
	rm -f $(TARGET)

test: $(TARGET)
	@echo "Running program:"
	@./$(TARGET)

help:
	@echo "Available targets:"
	@echo "  all     - Build the program (default)"
	@echo "  clean   - Remove compiled files" 
	@echo "  test    - Run the program"
	@echo "  help    - Show this help message"

.PHONY: all clean test help 