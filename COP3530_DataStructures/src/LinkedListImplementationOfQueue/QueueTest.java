package LinkedListImplementationOfQueue;

public class QueueTest {

	public static void main(String[] args) {
		Queue<Integer> q = new Queue();
		
		q.enQueue(5);
		q.enQueue(10);
		q.enQueue(15);
		q.enQueue(20);
		q.deQueue();
		q.deQueue();
		q.deQueue();
		q.deQueue();
		
		q.enQueue(50);
		System.out.println(q);
		
		System.out.println(q.peek());
	}

}
