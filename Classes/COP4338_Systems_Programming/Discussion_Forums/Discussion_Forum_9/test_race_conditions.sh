#!/bin/bash

echo "=========================================="
echo "Discussion Forum 9: Multithreading Test"
echo "=========================================="

echo ""
echo "Testing ORIGINAL version (with race conditions):"
echo "=========================================="

echo ""
echo "1. Running ./bank (default thread_no=1) 5 times:"
for i in {1..5}; do
    echo "Run $i:"
    ./bank
done

echo ""
echo "2. Running ./bank 100 5 times:"
for i in {1..5}; do
    echo "Run $i:"
    ./bank 100
done

echo ""
echo "3. Running ./bank 1000 5 times:"
for i in {1..5}; do
    echo "Run $i:"
    ./bank 1000
done

echo ""
echo "4. Running ./bank 10000 5 times:"
for i in {1..5}; do
    echo "Run $i:"
    ./bank 10000
done

echo ""
echo "=========================================="
echo "Testing FIXED version (with mutex locks):"
echo "=========================================="

echo ""
echo "1. Running ./bank_fixed (default thread_no=1) 5 times:"
for i in {1..5}; do
    echo "Run $i:"
    ./bank_fixed
done

echo ""
echo "2. Running ./bank_fixed 100 5 times:"
for i in {1..5}; do
    echo "Run $i:"
    ./bank_fixed 100
done

echo ""
echo "3. Running ./bank_fixed 1000 5 times:"
for i in {1..5}; do
    echo "Run $i:"
    ./bank_fixed 1000
done

echo ""
echo "4. Running ./bank_fixed 10000 5 times:"
for i in {1..5}; do
    echo "Run $i:"
    ./bank_fixed 10000
done

echo ""
echo "=========================================="
echo "Test completed!"
echo "==========================================" 