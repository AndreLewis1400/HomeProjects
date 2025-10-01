package Assignment_5_HashTable;
import java.util.Arrays;
/*
 * Write a java program to implement the following algorithms for Open Addressing techniques for
 * Hash Table data structure. (Use a simple array of integers to store integer key values only).
 * For both algorithms, to compute the index 𝑗, write the following methods:
 */

public class HashTable {
	// Instance variables
    private int[] table;
    private int size;
    private static final int EMPTY = -1;
    // Constructor to initialize the Hash Table
    public HashTable(int size) {
        this.size = size;
        table = new int[size];
        Arrays.fill(table, EMPTY);
    }
    // Primary hash function h1(k) = k % size
    private int h1(int key) {
        return key % size;
    }
    // Secondary hash function h2(k) = 1 + (k % (size - 1))
    // Resolves collisions by checking the next available slot
    private int h2(int key) {
        return 1 + (key % (size - 1));
    }
    // Compute index for Linear Probing: (h1(k) + i) % size
    // function to find the next slot
    public int getLinearProbIndex(int key, int i) {
        return (h1(key) + i) % size;
    }
    // Compute index for Quadratic Probing: (h1(k) + i^2) % size
    // Uses a second hash function for better distribution
    public int getQuadraticProbIndex(int key, int i) {
        return (h1(key) + i * i) % size;
    }
    // Compute index for Double Hashing: (h1(k) + i * h2(k)) % size
    public int getDoubleHash(int key, int i) {
        return (h1(key) + i * h2(key)) % size;
    }
    // Insert key into hash table using specified probing method
    public void insert(int key, String method) {
        for (int i = 0; i < size; i++) {
            int index;
            if (method.equals("linear")) {
                index = getLinearProbIndex(key, i);
            } else if (method.equals("quadratic")) {
                index = getQuadraticProbIndex(key, i);
            } else if (method.equals("double")) {
                index = getDoubleHash(key, i);
            } else {
                throw new IllegalArgumentException("Invalid probing method");
            }
            // Insert key if the slot is empty
            if (table[index] == EMPTY) {
                table[index] = key;
                return;
            }
        }
        System.out.println("Hash table is full, couldn't insert key: " + key);
    }
    // Search for key in hash table using specified probing method
    public boolean search(int key, String method) {
        for (int i = 0; i < size; i++) {
            int index;
            if (method.equals("linear")) {
                index = getLinearProbIndex(key, i);
            } else if (method.equals("quadratic")) {
                index = getQuadraticProbIndex(key, i);
            } else if (method.equals("double")) {
                index = getDoubleHash(key, i);
            } else {
                throw new IllegalArgumentException("Invalid probing method");
            }
            // Return true if key is found
            if (table[index] == key) {
                return true;
            }
            // Return false if an empty slot is encountered
            if (table[index] == EMPTY) {
                return false;
            }
        }
        return false;
    }
    // Display the hash table
    public void display() {
        System.out.println("Hash Table:");
        for (int i = 0; i < size; i++) {
            System.out.println(i + " -> " + (table[i] == EMPTY ? "empty" : table[i]));
        }
    }
    
    public static void main(String[] args) {
        HashTable hashTable = new HashTable(10);
        int[] keys = {15, 25, 35, 45};
        // Insert keys using Linear Probing
        System.out.println("Inserting using Linear Probing:");
        for (int key : keys) {
            hashTable.insert(key, "linear");
        }
        hashTable.display();
        // Search for keys using Linear Probing
        System.out.println("\nSearching for 25: " + hashTable.search(25, "linear"));
        System.out.println("Searching for 99: " + hashTable.search(99, "linear"));
        // Insert keys using Quadratic Probing
        System.out.println("\nInserting using Quadratic Probing:");
        HashTable quadraticHashTable = new HashTable(10);
        for (int key : keys) {
            quadraticHashTable.insert(key, "quadratic");
        }
        quadraticHashTable.display();
        // Insert keys using Double Hashing
        System.out.println("\nInserting using Double Hashing:");
        HashTable doubleHashTable = new HashTable(10);
        for (int key : keys) {
            doubleHashTable.insert(key, "double");
        }
        doubleHashTable.display();
    }

}
