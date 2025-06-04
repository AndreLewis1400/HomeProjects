package FoodOrderingSystem;

public interface Order {

	public void addItem(FoodItem item); // add a food item to order
	public double calculateTotal(); // calculate the total cost of the order
	public void displayOrderDetails(); // display the details of the order	
}
