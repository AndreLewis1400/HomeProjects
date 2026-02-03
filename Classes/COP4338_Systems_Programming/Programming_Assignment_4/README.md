# Programming Assignment 4: Word Puzzle Solver

A multi-threaded C program that finds meaningful English words of specified lengths within a randomly generated string.

## Features

- **Multi-threading**: Distributes workload across multiple threads for improved performance
- **JSON Dictionary Support**: Works with the provided `dictionary.json` file
- **Command-line Options**: Supports all required options from the assignment
- **Binary Search**: Efficient word lookup using the provided `binsearch` function
- **Thread Safety**: Proper mutex usage for shared resources

## Command-line Options

| Option | Points | Description |
|--------|--------|-------------|
| `-nthreads n` | 15 | Number of puzzle-solving threads (default: 1) |
| `-verbose` | 15 | Print thread creation/joining and total run time |
| `-time` | 15 | Print total time spent on binary search |
| `-sorted` | 15 | Sort the list of found words before printing |
| `-distinct` | 15 | Remove duplicate words from output |
| `-len l1,l2,...` | 15 | Word lengths to search (default: 8,9) |

## Files

- `wordpuzzle.c` - Main program source code
- `randomgen.c` - Random string generator for testing
- `Makefile` - Build configuration
- `README.md` - This documentation
- `Downloads/dictionary.json` - Dictionary file (1.6MB, ~93K words)

## Building

```bash
make
```

This creates the `wordpuzzle` executable.

## Usage

### Basic Usage
```bash
# Generate random string and pipe to wordpuzzle
./randomgen 2000000 | ./wordpuzzle

# Search for words of length 8 and 9 (default)
./randomgen 2000000 | ./wordpuzzle -len 8,9

# Use 4 threads
./randomgen 2000000 | ./wordpuzzle -nthreads 4

# Verbose output
./randomgen 2000000 | ./wordpuzzle -verbose -nthreads 4
```

### Advanced Usage
```bash
# Search for words of length 5, 6, and 7 with 8 threads
./randomgen 2000000 | ./wordpuzzle -nthreads 8 -len 5,6,7 -verbose

# Sort and remove duplicates
./randomgen 2000000 | ./wordpuzzle -sorted -distinct -verbose

# Measure binary search time
./randomgen 2000000 | ./wordpuzzle -time -nthreads 16 -verbose
```

### Performance Testing
```bash
# Test different thread counts for the plot
for n in 1 2 4 8 16 32 64 90; do
    echo "Testing with $n threads..."
    ./randomgen 2000000 | ./wordpuzzle -nthreads $n -time
done
```

## Program Structure

### Key Components

1. **Dictionary Loading**: Parses JSON dictionary file into sorted array
2. **Thread Management**: Creates and manages worker threads
3. **Work Distribution**: Divides input buffer among threads
4. **Word Search**: Sliding window approach with binary search
5. **Output Processing**: Handles sorting and duplicate removal

### Thread Safety

- **Time Mutex**: Protects `total_binary_search_time` updates
- **Output Mutex**: Ensures thread-safe printing
- **Memory Management**: Proper allocation/deallocation

### Algorithm

1. Load dictionary from JSON file
2. Read input buffer from stdin
3. Create worker threads with buffer segments
4. Each thread searches for words of specified lengths
5. Use binary search to check if words exist in dictionary
6. Collect and process results (sort/remove duplicates)
7. Print results and timing information

## Testing

### Quick Test
```bash
make test
```

### Manual Testing
```bash
# Test with known words
echo "hello world programming assignment" | ./wordpuzzle -verbose -len 5,6,7,8,9,10,11

# Test with random data
./randomgen 10000 | ./wordpuzzle -verbose -len 3,4,5
```

## Performance Considerations

- **Dictionary Size**: ~93K words loaded into memory
- **Buffer Size**: 2MB input buffer
- **Thread Count**: Optimal performance varies by system
- **Word Lengths**: Shorter words = more potential matches
- **Binary Search**: O(log n) complexity for dictionary lookups

## Submission Requirements

The program meets all assignment requirements:

- **Executable Name**: `wordpuzzle`
- **Command-line Options**: All 5 options implemented
- **Multi-threading**: Proper thread creation and management
- **Binary Search**: Uses provided `binsearch` function
- **JSON Dictionary**: Works with `dictionary.json`
- **Makefile**: Proper build configuration
- **Thread Safety**: Mutex protection for shared resources
- **Memory Management**: Proper allocation and cleanup

## Extra Credit

For the performance plot (10 extra points):

1. Run performance tests with different thread counts
2. Create Excel/Google Sheets with data
3. Generate plot with regression line
4. Save as JPG file

## Troubleshooting

### Common Issues

1. **Dictionary not found**: Ensure `dictionary.json` is in `Downloads/` directory
2. **Memory errors**: Check system has enough RAM for 2MB buffer
3. **Thread creation fails**: Reduce thread count or check system limits
4. **No output**: Verify input contains valid words of specified lengths

### Debug Options

```bash
# Verbose mode for debugging
./wordpuzzle -verbose -nthreads 1

# Check dictionary loading
./wordpuzzle -verbose -len 1,2,3
```

## License

This project is created for COP4338 Systems Programming at Florida International University. 