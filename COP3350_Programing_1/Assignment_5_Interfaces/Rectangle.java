package Assignment_5_Interfaces;

public class Rectangle implements Shape {

	private double height, width;

	public Rectangle() {

		this(0.0,0.0);
	}
	public Rectangle(double height, double width) {

		this.height = height;
		this.width = width;
	}
	public double getHeight() {
		return height;
	}
	public void setHeight(double height) {
		this.height = height;
	}
	public double getWidth() {
		return width;
	}
	public void setWidth(double width) {
		this.width = width;
	}
	@Override
	public double area() {

		return height * width;
	}
}
