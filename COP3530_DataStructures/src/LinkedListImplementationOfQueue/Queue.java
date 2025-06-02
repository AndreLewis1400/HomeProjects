package LinkedListImplementationOfQueue; // Package declaration (likely a typo, should be "queue")

import java.util.NoSuchElementException; // Import for exception handling

public class Queue <T> { // Generic Queue class
    Node<T> front, rear; // Pointers to track the front and rear of the queue
    int size; // Variable to track the number of elements in the queue

    // Inner class representing a node in the queue
    private class Node<T> {            
        T data; // Data stored in the node
        Node<T> next; // Pointer to the next node in the queue
    }

    // Constructor to initialize an empty queue
    public Queue() {
        size = 0; // Queue starts with size 0
        front = rear = null; // Front and rear pointers are set to null
    }

    // Adds an element to the end of the queue
    public void enQueue(T data) {
        Node<T> node = new Node<>(); // Create a new node
        node.data = data; // Assign data to the node
        node.next = null; // Since it’s added at the rear, next is null
        
        if (front == null && rear == null) { // If queue is empty
            rear = front = node; // Set both front and rear to the new node
            size++; // Increment size
            return; // Exit the function
        }
        rear.next = node; // Link the current rear node to the new node
        rear = node; // Update the rear pointer to the new node
        size++; // Increment size
    }

    // Removes and returns the front element from the queue
    public T deQueue() {
        Node<T> temp = front; // Store reference to the front node
        if (front == null) // Check if queue is empty
            throw new NoSuchElementException("Queue is Empty"); // Throw an exception if empty
        
        if (front == rear) { // If there is only one element in the queue
            front = rear = null; // Set front and rear to null
            size--; // Decrement size
            return temp.data; // Return the removed element's data
        } else {
            front = front.next; // Move front pointer to the next node
            size--; // Decrement size
            return temp.data; // Return the removed element's data
        }
    }

    // Returns the front element without removing it
    public T peek() {
        if (front == null) // Check if queue is empty
            throw new NoSuchElementException("Queue is Empty"); // Throw an exception if empty
        return front.data; // Return the front element's data
    }

    // Returns the number of elements in the queue
    public int getSize() {
        return size;
    }

    // Converts the queue elements into a string representation
    public String toString() {
        Node<T> temp = front; // Start from the front
        String s = "["; // Initialize the string
        for (int i = 0; i < size; i++) { // Loop through all elements
            s = s + temp.data + ", "; // Append each element to the string
            temp = temp.next; // Move to the next node
        }
        s = s + "]"; // Close the string format
        return s; // Return the final string representation
    }
}
