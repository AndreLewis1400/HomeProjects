package FoodOrderingSystem;

public class OnlineFoodOrderSYstem {

	public static void main(String[] args) {

		Pizza p = new Pizza("Pizza", 12.99, "Large");
		Burger b = new Burger("Burger", 9.99, "Combo");
		Salad s = new Salad("Salad", 6.49, "Cesar");

		FoodOrder fO = new FoodOrder();

		fO.addItem(p);
		fO.addItem(b);
		fO.addItem(s);
		fO.displayOrderDetails();
	}
}
