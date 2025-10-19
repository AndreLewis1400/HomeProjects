package FoodOrderingSystem;

public class Salad implements FoodItem{

	private String name;
	private double price;
	private String description;

	public Salad() {

		this("none", 0.0, "none");
	}
	public Salad(String name, double price, String description) {

		this.name = name;
		this.description = description;
		this.price = price;
	}
	@Override
	public String getName() {
		return name;
	}
	public void setName(String name) {
		if (name instanceof String) { // If the name is not a string, the code prints an error message
			this.name = name; 
		}
		else {
			System.out.println("Error: Invalid Food Item");
			System.exit(0);
		}
	}
	@Override
	public double getPrice() {
		return price;
	}
	public void setPrice(double price) {
		if (price < 0.0) { // checks if the provided price is less than zero. This condition indicates an invalid price.
			System.out.println("Error: Invalid price");
		}
		else
			this.price = price;	
	}
	@Override
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		if (description instanceof String) { // If the description is not a string, the code prints an error message
			this.description = description; 
		}
		else {
			System.out.println("Error: Invalid Food Item");
			System.exit(0);
		}
	}
}
