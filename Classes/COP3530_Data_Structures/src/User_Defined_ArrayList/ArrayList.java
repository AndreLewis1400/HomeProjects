package User_Defined_ArrayList;

public class ArrayList<AnyType> { 
    // Instance Variables
    public final static int CAPACITY = 10; // Default capacity of the ArrayList
    private int size; // Tracks the number of elements in the ArrayList
    private AnyType[] items; // The array to store the elements

    // Default constructor to initialize the ArrayList
    public ArrayList() {
        clear(); // Resets the ArrayList to its initial state
    }

    // Resets the ArrayList: size is set to 0 and items array is initialized
    public void clear() { 
        size = 0; 
        items = (AnyType[]) new Object[CAPACITY]; // Creates a new array with default capacity
    }

    // Returns the current number of elements in the ArrayList
    public int getSize() { 
        return size;
    }

    // Checks if the ArrayList is empty
    public boolean isEmpty() { 
        return size == 0;
    }

    // Ensures the ArrayList has enough capacity; expands the array if needed
    public void ensureCapacity(int capacity) { 
        if (capacity <= items.length) {
            return; // No expansion needed if the current capacity is sufficient
        }
        AnyType[] temp = (AnyType[]) new Object[capacity]; // Creates a new larger array
        for (int i = 0; i < size; i++) { 
            temp[i] = items[i]; // Copies elements from the old array to the new array
        }
        items = temp; // Replaces the old array with the new array
    }

    // Adds a new element to the end of the ArrayList
    public void add(AnyType data) { 
        if (size == items.length) {
            ensureCapacity(size * 2); // Doubles the array capacity if it is full
        }
        items[size++] = data; // Adds the new element and increments the size
    }

    // Adds a new element at the specified index in the ArrayList
    public void add(int index, AnyType data) { 
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException(); // Ensures the index is valid
        }
        if (size == items.length) {
            ensureCapacity(size * 2); // Doubles the array capacity if it is full
        }
        for (int i = size; i > index; i--) { 
            items[i] = items[i - 1]; // Shifts elements to make room for the new element
        }
        items[index] = data; // Places the new element at the specified index
        size++; // Increments the size
    }

 // Removes the last element from the ArrayList
    public void remove() { 
        if (size > 0) {
            items[size - 1] = null; // Explicitly remove the reference to the last element
            size--; // Reduce the size, effectively removing the last element
        }
    }


    // Removes the element at the specified index from the ArrayList
    public void remove(int index) { 
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException(); // Ensures the index is valid
        }
        for (int i = index; i < size - 1; i++) {
            items[i] = items[i + 1]; // Shifts elements to fill the gap left by the removed element
        }
        size--; // Reduces the size
    }

    // Returns the element at the specified index
    public AnyType get(int index) { 
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException(); // Ensures the index is valid
        }
        return items[index]; // Retrieves the element
    }

    // Sets a new value at the specified index
    public void set(int index, AnyType data) { 
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException(); // Ensures the index is valid
        }
        items[index] = data; // Updates the value at the specified index
    }

    // Checks if the ArrayList contains a specific value
    public boolean contains(AnyType value) { 
        for (int i = 0; i < size; i++) {
            if (items[i].equals(value)) {
                return true; // Returns true if the value is found
            }
        }
        return false; // Returns false if the value is not found
    }

    // Returns a string representation of the ArrayList
    @Override
    public String toString() { 
        if (size == 0) {
            return "[]"; // Returns an empty list representation
        }
        StringBuilder str = new StringBuilder("["); // Starts the string with an opening bracket
        for (int i = 0; i < size - 1; i++) {
            str.append(items[i]).append(", "); // Appends each element followed by a comma
        }
        str.append(items[size - 1]).append("]"); // Appends the last element and a closing bracket
        return str.toString();
    }
}
