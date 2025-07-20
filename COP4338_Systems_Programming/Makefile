CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = discussion_forum_6

all: $(TARGET)

$(TARGET): discussion_forum_6.c
	$(CC) $(CFLAGS) -o $(TARGET) discussion_forum_6.c

clean:
	rm -f $(TARGET)

test: $(TARGET)
	@echo "Testing case-sensitive sorting:"
	@echo -e "Zebra\napple\nBanana\ncat" | ./$(TARGET)
	@echo -e "\nTesting case-insensitive sorting:"
	@echo -e "Zebra\napple\nBanana\ncat" | ./$(TARGET) -i

help:
	@echo "Available targets:"
	@echo "  all     - Build the program (default)"
	@echo "  clean   - Remove compiled files"
	@echo "  test    - Run test cases"
	@echo "  help    - Show this help message"

.PHONY: all clean test help 