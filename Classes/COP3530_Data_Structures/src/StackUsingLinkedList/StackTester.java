package StackUsingLinkedList;

public class StackTester {

	public static void main(String[] args) {
		Stack<Integer> s = new Stack<>();
		s.push(5);
		s.push(45);
		s.push(95);
		s.push(25);
		s.push(67);
		
		System.out.println(s);
		
		s.pop();
		System.out.println(s);
		System.out.println(s.pop());
		System.out.println(s);
		
		System.out.println(s.peek());
		
		System.out.println(s);

	}

}
