package User_Defined_ArrayList;

public class ArrayListTest {
    public static void main(String[] args) {
        // Create an instance of ArrayList to hold any type of elements
        ArrayList<Object> list = new ArrayList<>();
        
        // Add "Apple" to the ArrayList
        list.add("Apple");
        
        // Add "Grapes" to the ArrayList
        list.add("Grapes");
        
        // Add "Banana" to the ArrayList
        list.add("Banana");
        
        // Add 56 (int) to the ArrayList
        list.add(56);
        
        // Add 9.8 (double) to the ArrayList
        list.add(9.8);
        
        // Add 'A' (char) to the ArrayList
        list.add('A');
        
        // Add "Mellon" at index 2 to the ArrayList
        list.add(2, "Mellon");
        
        // Print the contents of the ArrayList
        System.out.println(list); // Expected: [Apple, Grapes, Mellon, Banana, 56, 9.8, A]
        
        // Remove the last element from the ArrayList
        list.remove();
        System.out.println(list); // Expected: [Apple, Grapes, Mellon, Banana, 56, 9.8]
        
        // Remove the element at index 2
        list.remove(2);
        System.out.println(list); // Expected: [Apple, Grapes, Banana, 56, 9.8]
        
        // Check if the ArrayList contains "Mellon"
        System.out.println(list.contains("Mellon")); // Expected: false
        
        // Clear all elements from the ArrayList
        list.clear();
        System.out.println(list); // Expected: []
    }
}
