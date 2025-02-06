package LinkedList;

public class LinkedListTest {
	
	public static void main(String[] args) {
		System.out.println("Debugging LinkedList");
		LinkedList list = new LinkedList();
		list.addFirst(50);
		list.addFirst(40);
		list.addFirst(90);
		list.addFirst(15);
		
		list.addLast(25);
		list.addLast(45);
		list.addLast(55);
		list.add(65);
		
		list.insert(3, 105);
		
		System.out.println(list);
		
		list.insert(5, 120);
		
		System.out.println(list);
		
		list.removeFirst();
		System.out.println(list);
		
		list.removeLast();
		
		System.out.println(list);
		
		list.remove(2);
		
		System.out.println(list);
		
		list.remove();
		
		System.out.println(list);
		
		System.out.println(list.getFirst());
		System.out.println(list.getLast());
		
		list.set(2, 50);
		System.out.println(list);
		
		
		System.out.println(list.contains(190));
		list.clear();
		System.out.println(list);
		
		
	}

}
