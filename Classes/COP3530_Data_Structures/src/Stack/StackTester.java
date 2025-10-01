package Stack;

public class StackTester {

	public static void main(String[] args) {
		Stack<Integer> s = new Stack<>();
		s.push(5);
//		s.push("Hello");
//		s.push(5.6);
		s.push(9);
		s.push(7);
		s.push(6);
		s.push(8);
		s.push(15);
		
		s.print();
		
		s.pop();
		s.pop();
//		s.pop();
//		s.pop();
//		s.pop();
//		s.pop();
//		s.pop();
		System.out.println("Top of the stack is "+s.peek());
		s.print();
		
	}

}
