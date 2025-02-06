package queue;

public class QueueTest {

	public static void main(String[] args) {
		Queue q = new Queue();
		
		q.enQueue(5);
		q.enQueue("Hi");
		q.enQueue(5.9);
		q.enQueue(11);
		q.enQueue(21);
		try {
		q.enQueue(25);}
		catch(Exception e){
			System.out.println(e.getMessage());
		}
		q.print();
		
		q.deQueue();
		q.deQueue();
		q.deQueue();
		
		q.print();
		
		q.enQueue(50);
		q.enQueue(55);
		q.enQueue(60);
		q.deQueue();
		q.enQueue(64);
		q.print();
		
		q.deQueue();
		System.out.println(q.peek());

		
	
		
		


	}

}
