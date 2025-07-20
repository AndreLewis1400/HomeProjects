package Reversed_user_defined_ArrayList;

	public class TestReversedLinkedList {
	    public static void main(String[] args) {
	    	// Custom ArrayList class
	    	ReversedLinkedList<Object> list = new ReversedLinkedList<>();

	        // Add elements to the ArrayList
	        list.add(1);
	        list.add(2);
	        list.add(3);
	        list.add(4);
	        list.add(5);
	        
	        // Print the original ArrayList
	        System.out.println("Original ArrayList:");
	        System.out.println(list);

	        // Reverse the ArrayList
	        list.reverse();
	        // Print the reversed ArrayList
	        System.out.println("Reversed ArrayList:");
	        System.out.println(list);
	    }
	}