package Polymorphism;

public class Employee 
{
	private String employeeID;
	private String name;
	private String department;
	private double salary;
	private String designation;
	
	// Default constructor
	public Employee()
	{
		this("none", "none", "none", 0.0, "none");
	}
	// Argument constructor
	public Employee(String employeeID, String name, String department, double salary, String designation)
	{
		setEmployeeID(employeeID);
		setName(name);
		setDepartment(department);
		setSalary(salary);
		setDesignation(designation);
	}
	// Copy constructor
	public Employee(Employee object)
	{
		this(object.getEmployeeID(), object.getName(), object.getDepartment(), object.getSalary(), object.getDesignation());
		object.addBonus();
	}
	public String getEmployeeID() {
		return employeeID;
	}
	public void setEmployeeID(String employeeID) {
		this.employeeID = employeeID;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getDepartment() {
		return department;
	}
	public void setDepartment(String department) {
		this.department = department;
	}
	public double getSalary() {
		return salary;
	}
	public void setSalary(double salary) {
		this.salary = salary;
	}
	public String getDesignation() {
		return designation;
	}
	public void setDesignation(String designation) {
		this.designation = designation;
	}
	// Bonus calculation
	public double addBonus()
	{
		double defaultBonus = 200;
		return salary + defaultBonus;
	}
	public int salaryDeductions(int absentDays)
	{
		return 0;
	}
	// Override method
	public String toString()
	{
		return "Employee ID :E" + getEmployeeID() + "\nEmployee name : " + getName() + "\nDepartment name : " +
				getDepartment() + "\nSalary :" +
				getSalary() + "\nDesignation : " + getDesignation() + "\nSalary after adding the bonus is : ";	
	}
	// Override method
	public boolean equals(Employee other)
	{
		return getEmployeeID() == other.getEmployeeID() && getName().equals(other.getName())
				&& getDepartment().equals(other.getDepartment()) && getSalary() == other.getSalary()
				&& getDesignation().equals(other.getDesignation())&& addBonus() == other.addBonus();
	}
	
}
