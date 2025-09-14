# COP3530 Data Structures

This directory contains assignments and projects for COP3530: Data Structures at FIU.

## Course Overview

COP3530 covers fundamental data structures and algorithms, including:
- Arrays, stacks, and queues
- Linked lists and trees
- Graphs and graph algorithms
- Sorting and searching algorithms
- Algorithm analysis and complexity

## Projects & Materials

### Source Code Directory
- **Directory**: [`src/`](src/)
- **Description**: Contains all source code implementations
- **Structure**: Organized by data structure type and algorithm category

### Data Structure Implementations

#### Linear Data Structures
- **Arrays**: Dynamic array implementations and operations
- **Stacks**: LIFO data structure with push/pop operations
- **Queues**: FIFO data structure with enqueue/dequeue operations
- **Linked Lists**: Singly and doubly linked list implementations

#### Hierarchical Data Structures
- **Trees**: Binary trees, binary search trees, and tree traversals
- **Heaps**: Min-heap and max-heap implementations
- **Graphs**: Adjacency matrix and adjacency list representations

#### Advanced Data Structures
- **Hash Tables**: Hash table implementations with collision resolution
- **Sets**: Set data structure implementations
- **Maps**: Key-value pair data structures

### Algorithm Implementations

#### Sorting Algorithms
- **Bubble Sort**: Simple comparison-based sorting
- **Selection Sort**: In-place comparison sorting
- **Insertion Sort**: Adaptive comparison sorting
- **Merge Sort**: Divide-and-conquer sorting
- **Quick Sort**: Partition-based sorting
- **Heap Sort**: Heap-based sorting

#### Searching Algorithms
- **Linear Search**: Sequential search through data
- **Binary Search**: Divide-and-conquer search on sorted data
- **Depth-First Search (DFS)**: Graph traversal algorithm
- **Breadth-First Search (BFS)**: Graph traversal algorithm

#### Graph Algorithms
- **Shortest Path**: Dijkstra's and Floyd-Warshall algorithms
- **Minimum Spanning Tree**: Kruskal's and Prim's algorithms
- **Topological Sort**: DAG sorting algorithm

## Key Learning Outcomes

- **Data Structure Design**: Understanding when and how to use different data structures
- **Algorithm Analysis**: Time and space complexity analysis
- **Implementation Skills**: Converting algorithms to working code
- **Problem Solving**: Applying appropriate data structures to solve problems
- **Performance Optimization**: Choosing efficient algorithms for specific problems

## Implementation Languages

The course primarily uses:
- **Java**: Main implementation language for most data structures
- **C/C++**: Some low-level implementations for performance-critical algorithms
- **Python**: Prototyping and algorithm demonstration

## Project Structure

Each implementation typically includes:
- **Source Code**: Complete implementation of the data structure or algorithm
- **Documentation**: Comments explaining the implementation details
- **Test Cases**: Sample inputs and expected outputs
- **Performance Analysis**: Time and space complexity documentation

## Usage Examples

### Compiling and Running Java Programs
```bash
# Navigate to source directory
cd src/

# Compile Java files
javac DataStructureName.java

# Run the program
java DataStructureName
```

### Testing Implementations
```bash
# Run with test data
java DataStructureName < test_input.txt

# Run performance tests
java PerformanceTest
```

## Best Practices Demonstrated

- **Modular Design**: Separate classes for different data structures
- **Interface Implementation**: Consistent APIs across similar data structures
- **Error Handling**: Proper validation and exception handling
- **Documentation**: Comprehensive comments and documentation
- **Testing**: Unit tests and integration tests for validation

## Performance Considerations

- **Time Complexity**: Analysis of algorithm efficiency
- **Space Complexity**: Memory usage optimization
- **Trade-offs**: Understanding when to use different implementations
- **Optimization**: Techniques for improving algorithm performance

---

For detailed implementation details and specific algorithms, see the source code in the `src/` directory. 