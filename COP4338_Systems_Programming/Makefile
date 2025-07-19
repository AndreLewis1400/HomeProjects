CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Target programs
TARGETS = date_scanner_fixed csv_to_txt_converter file_io_converter printf_analysis

# Default target
all: $(TARGETS)

# Individual targets
date_scanner_fixed: date_scanner_fixed.c
	$(CC) $(CFLAGS) -o date_scanner_fixed date_scanner_fixed.c

csv_to_txt_converter: csv_to_txt_converter.c
	$(CC) $(CFLAGS) -o csv_to_txt_converter csv_to_txt_converter.c

file_io_converter: file_io_converter.c
	$(CC) $(CFLAGS) -o file_io_converter file_io_converter.c

printf_analysis: printf_analysis.c
	$(CC) $(CFLAGS) -o printf_analysis printf_analysis.c

# Clean target
clean:
	rm -f $(TARGETS) *.o

# Test target
test: all
	@echo "Testing printf analysis..."
	./printf_analysis
	@echo ""
	@echo "Testing CSV to TXT converter (enter: 1,2,3,4,5,6)"
	@echo "1,2,3,4,5,6" | ./csv_to_txt_converter

.PHONY: all clean test 