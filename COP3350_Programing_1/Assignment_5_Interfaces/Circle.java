package Assignment_5_Interfaces;

public class Circle implements Shape{
	private double radius;

	public Circle() {

		this(0.0);
	}	
	public Circle(double radius) {

		this.radius = radius;
	}
	public double getRadius() {
		return radius;
	}
	public void setRadius(double radius) {
		this.radius = radius;
	}
	@Override
	public double area() {

		return Math.PI * radius * radius;
	}
}
