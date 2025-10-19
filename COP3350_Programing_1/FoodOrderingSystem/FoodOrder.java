package FoodOrderingSystem;

import java.util.ArrayList;
import java.util.List;

public class FoodOrder implements Order {

	private List<FoodItem> items; // List of food items added

	public FoodOrder() {	
		this.items = new ArrayList<>(); // Create a new ArrayList to hold food items
	}
	public void addItem(FoodItem item) {

		items.add(item); // add the provided food item to the items list
	}
	public double calculateTotal() {
		double total = 0.0; // Initialize total price to zero
		for (FoodItem item : items) { // Loop through each food item
			total += item.getPrice(); // Add the price of each item to total
		}
		if (total == 0.0) {
			System.out.println("Error: can not calculate the total cost of an empty order.");
			System.exit(0);
		}
		return total;
	}
	public void displayOrderDetails() {

		System.out.println("Order Details:");
		for (FoodItem item: items) { // Loop through each item
			System.out.println(item.getName() + "(" + item.getDescription() + "): $" + item.getPrice());
		}
		System.out.println("Total: $" + calculateTotal());
	}
}

