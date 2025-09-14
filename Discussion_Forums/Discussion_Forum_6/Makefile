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
	@printf "Zebra\napple\nBanana\ncat\n" | ./$(TARGET)
	@echo -e "\nTesting case-insensitive sorting:"
	@printf "Zebra\napple\nBanana\ncat\n" | ./$(TARGET) -i

test_file: $(TARGET)
	@echo "Testing with test_input.txt:"
	@./$(TARGET) < test_input.txt
	@echo -e "\nTesting with test_input.txt (case-insensitive):"
	@./$(TARGET) -i < test_input.txt

help:
	@echo "Available targets:"
	@echo "  all       - Build the program (default)"
	@echo "  clean     - Remove compiled files"
	@echo "  test      - Run test cases"
	@echo "  test_file - Run tests with test_input.txt"
	@echo "  help      - Show this help message"

.PHONY: all clean test test_file help 