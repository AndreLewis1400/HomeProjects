#!/bin/bash

echo "=== Testing Assignment 3 on Ocelot ==="
echo "Compiling banking_system.c..."

# Compile with gcc
gcc -Wall -Wextra -std=c99 -pthread -o banking_system banking_system.c

if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo ""
    echo "Running banking system..."
    echo "================================"
    ./banking_system
    echo "================================"
    echo "✓ Program completed successfully!"
else
    echo "✗ Compilation failed!"
    exit 1
fi

echo ""
echo "Files in current directory:"
ls -la

echo ""
echo "Ready for submission!"
