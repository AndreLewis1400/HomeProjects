package StackUsingLinkedList; // Defines the package name

public class Stack<T> { // Generic Stack class with type parameter T

    // Inner class representing a node in the linked list
    private class Node<T> {
        private T data; // Stores the node's data
        private Node<T> next; // Points to the next node in the stack
    }

    private Node<T> top; // Points to the top node of the stack
    private int size; // Tracks the number of elements in the stack

    // Constructor initializes an empty stack
    public Stack() {
        top = null; // Stack is initially empty
        size = 0; // Stack size is 0
    }

    // Push method to add an element to the top of the stack
    public void push(T data) {
        Node<T> node = new Node<>(); // Create a new node
        node.data = data; // Set node data
        node.next = top; // Link new node to the current top
        top = node; // Update top to the new node
        size++; // Increase stack size
    }

    // Pop method to remove and return the top element of the stack
    public T pop() {
        if (top == null) // Check if stack is empty
            throw new IndexOutOfBoundsException(); // Throw exception if empty
        T data = top.data; // Store the top element's data
        top = top.next; // Move top pointer to the next node
        size--; // Decrease stack size
        return data; // Return the removed element
    }

    // Peek method to return the top element without removing it
    public T peek() {
        if (top == null) // Check if stack is empty
            throw new IndexOutOfBoundsException(); // Throw exception if empty
        return top.data; // Return top element's data
    }

    // Converts the stack into a string representation
    public String toString() {
        String str = "["; // Initialize the string representation
        Node<T> temp = top; // Temporary pointer to traverse the stack
        while (temp.next != null) { // Traverse until the second last node
            str = str + temp.data + ", "; // Append element to the string
            temp = temp.next; // Move to the next node
        }
        str = str + temp.data + "]"; // Append last element and closing bracket
        return str; // Return the final string
    }
}
