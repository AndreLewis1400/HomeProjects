package Stack; // Defines the package named "Stack"

public class Stack<T> { // Generic class Stack with type parameter T
    private int top; // Tracks the index of the top element in the stack
    T[] stack; // Array to store stack elements

    // Default constructor initializes the stack with size 5
    public Stack() {
        this(5);
    }

    // Constructor initializes the stack with a given size
    public Stack(int size) {
        top = 0; // Stack is initially empty
        stack = (T[]) new Object[size]; // Creates a generic array
    }

    // Push method to add an element to the stack
    public void push(T data) {
        // If the stack is full, resize it by doubling its capacity
        if (top >= stack.length) {
            T[] temp = (T[]) new Object[stack.length * 2]; // Create a new array with double the size
            for (int i = 0; i < stack.length; i++) // Copy elements to new array
                temp[i] = stack[i];
            stack = temp; // Update reference to the new array
        }
        stack[top] = data; // Add new element to the stack
        top++; // Increment top pointer
    }

    // Pop method to remove and return the top element from the stack
    public T pop() {
        if (top <= 0) { // Check if the stack is empty
            System.out.println("Stack is empty");
            System.exit(0); // Exit program if stack is empty
        }
        T data = stack[top - 1]; // Get the top element
        top--; // Decrease the top index
        return data; // Return the removed element
    }

    // Peek method to return the top element without removing it
    public T peek() {
        if (top <= 0) { // Check if the stack is empty
            System.out.println("Stack is empty");
            System.exit(0); // Exit program if stack is empty
        }
        return stack[top - 1]; // Return the top element
    }

    // Print method to display all elements in the stack
    public void print() {
        for (int i = 0; i < top; i++) { // Iterate through the stack
            System.out.print(stack[i] + ", "); // Print each element
        }
        System.out.println(); // Move to new line after printing all elements
    }
}
