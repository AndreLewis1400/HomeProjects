package LinkedList;

public class LinkedList <T>{

    // Inner class representing a node in the linked list
    private class Node<T> {
        private T data; // Stores the data of the node
        private Node<T> next; // Reference to the next node in the list
        
        private Node() {
            data = null;
            next = null;
        }
    }

    private int size; // Tracks the number of elements in the linked list
    private Node<T> head; // Reference to the first node in the list

    // Default constructor initializing an empty linked list
    public LinkedList() {
        size = 0;
        head = null;
    }

    // Adds an element at the beginning of the list
    public void addFirst(T data) {
        insert(0, data);
    }
    
    // Adds an element at the end of the list
    public void addLast(T data) {
        insert(size-1, data);
    }
    
    // Adds an element at the end of the list (same as addLast)
    public void add(T data) {
        addLast(data);
    }
    
    // Inserts an element at a specified index
    public void insert(int index, T data) {
        if (index < 0 || index > size) 
            throw new IndexOutOfBoundsException();
        
        Node<T> newNode = new Node<>();
        newNode.data = data;
        
        if(index == 0) { // Inserting at the head
            newNode.next = head;
            head = newNode; 
            size++;
            return;
        }
        
        Node<T> temp = head;
        for(int i = 0; i < index-1; i++)
            temp = temp.next;
        
        newNode.next = temp.next;
        temp.next = newNode;
        size++;
    }

    // Removes an element at a specified index
    public void remove(int index) {
        if(index < 0 || index >= size)
            throw new IndexOutOfBoundsException();
        
        if(index == 0) { // Removing the first element
            head = head.next;
            size--;
            return;
        }
        
        Node<T> temp = head;
        for (int i = 0; i < index-1; i++)
            temp = temp.next;
        
        Node<T> temp2 = temp.next;
        temp.next = temp2.next;
        size--;
    }

    // Removes the first element of the list
    public void removeFirst() {
        remove(0);
    }

    // Removes the last element of the list
    public void removeLast() {
        remove(size-1);
    }

    // Removes the last element of the list (same as removeLast)
    public void remove() {
        removeLast();
    }

    // Returns the size of the list
    public int size() {
        return size;
    }

    // Returns the data at the specified index
    public T get(int index) {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException();
        
        Node<T> temp = head;
        for (int i = 0; i < index; i++)
            temp = temp.next;
        
        return temp.data;
    }

    // Returns the first element
    public T getFirst() {
        return get(0);
    }

    // Returns the last element
    public T getLast() {
        return get(size-1);
    }

    // Updates the value at a specified index
    public void set(int index, T data) {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException();
        
        Node<T> temp = head;
        for (int i = 0; i < index; i++){
            temp = temp.next;
            temp.data = data;
        }
    }

    // Clears the entire list
    public void clear() {
        head = null;
        size = 0;
    }

    // Checks if the list contains a specific value
    public boolean contains(T data) {
        Node<T> temp = head;
        for (int i = 0; i < size; i++) {
            if (temp.data.equals(data))
                return true;
            temp = temp.next;
        }
        return false;
    }

    // Converts the list into a readable string format
    public String toString() {
        String str = "[";
        if(head == null)
            return str + "]";
        
        Node<T> temp = head;
        while (temp.next != null) {
            str = str + temp.data + ", ";
            temp = temp.next;
        }
        
        str = str + temp.data + "]";
        return str;
    }
}
