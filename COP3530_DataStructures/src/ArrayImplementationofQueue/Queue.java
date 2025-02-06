package ArrayImplementationofQueue;

import java.util.NoSuchElementException;

public class Queue <T> {
    private int front, rear, size, capacity; // Pointers for front and rear, size tracker, and max capacity
    private T[] queue; // Array to store queue elements

    // Default constructor initializing queue with a default capacity of 5
    public Queue() {
        this(5);
    }

    // Constructor to initialize queue with a specified capacity
    public Queue(int capacity) {
        this.capacity = capacity;
        front = rear = 0;
        size = 0;
        queue = (T[]) new Object[capacity]; // Generic array creation
    }

    // Adds an element to the queue (enqueue operation)
    public void enQueue(T data) {
        if (!isFull()) { // Check if queue is full
            queue[rear] = data;
            rear = (rear + 1) % capacity; // Circular increment of rear pointer
            size++;
            return;
        }
        throw new IndexOutOfBoundsException("Queue is full");
    }

    // Removes and returns the front element from the queue (dequeue operation)
    public T deQueue() {
        if (!isEmpty()) { // Check if queue is empty
            T data = queue[front];
            front = (front + 1) % capacity; // Circular increment of front pointer
            size--;
            return data;
        }
        throw new NoSuchElementException("Queue is Empty");
    }

    // Returns the current size of the queue
    public int getSize() {
        return size;
    }

    // Checks if the queue is full
    public boolean isFull() {
        return getSize() == capacity;
    }

    // Checks if the queue is empty
    public boolean isEmpty() {
        return getSize() == 0;
    }

    // Returns the front element without removing it (peek operation)
    public T peek() {
        if (!isEmpty()) { // Ensure queue is not empty
            T data = queue[front];
            return data;
        }
        throw new NoSuchElementException("Queue is Empty");
    }

    // Prints all elements in the queue in order
    public void print() {
        for (int i = 0; i < size; i++) {
            System.out.print(queue[(front + i) % capacity] + ", ");
        }
        System.out.println();
    }
}
