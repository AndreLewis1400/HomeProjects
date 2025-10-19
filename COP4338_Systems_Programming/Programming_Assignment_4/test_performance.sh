#!/bin/bash

# Performance testing script for Programming Assignment 4
# Generates data for the extra credit plot

echo "Performance Testing for Word Puzzle Solver"
echo "=========================================="
echo ""

# Create output file
OUTPUT_FILE="performance_data.txt"
echo "# Threads,Total_Time(ns),Binary_Search_Time(ns)" > $OUTPUT_FILE

# Test thread counts for the plot
THREAD_COUNTS=(1 2 4 8 16 32 64 90)

for n in "${THREAD_COUNTS[@]}"; do
    echo "Testing with $n threads..."
    
    # Generate random string and test
    ./randomgen 2000000 | ./wordpuzzle -nthreads $n -time > /dev/null 2> temp_output.txt
    
    # Extract timing information
    TOTAL_TIME=$(grep "Total time:" temp_output.txt | awk '{print $4}')
    BINARY_TIME=$(grep "Total binary search time:" temp_output.txt | awk '{print $5}')
    
    echo "$n,$TOTAL_TIME,$BINARY_TIME" >> $OUTPUT_FILE
    
    echo "  Total time: $TOTAL_TIME ns"
    echo "  Binary search time: $BINARY_TIME ns"
    echo ""
done

# Clean up
rm -f temp_output.txt

echo "Performance data saved to $OUTPUT_FILE"
echo ""
echo "Data format:"
echo "Threads,Total_Time(ns),Binary_Search_Time(ns)"
echo ""
echo "You can now:"
echo "1. Open $OUTPUT_FILE in Excel/Google Sheets"
echo "2. Create a scatter plot with Threads on X-axis and Total_Time on Y-axis"
echo "3. Add a trend line (regression line)"
echo "4. Save as JPG for extra credit" 