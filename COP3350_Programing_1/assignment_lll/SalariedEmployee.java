package assignment_lll;

public class SalariedEmployee extends Employee
{
	private double salary;
	
	// Default constructor
	public SalariedEmployee() 
	{
		this("No name yet", new Date(), 0.0);
	}
	// Argument constructor
	public SalariedEmployee(String name, Date hireDate, double salary)
	{
		super(name, hireDate);
		setSalary(salary);
	}
	// Copy constructor
	public SalariedEmployee(SalariedEmployee object)
	{
		super(object);
		setSalary(object.getSalary());
	}
	public double getSalary() 
	{
		return salary;
	}
	public double getPay()
	{
		return getSalary() /12;
	}
	public void setSalary(double salary) 
	{
		if ( salary < 0.0)
		{
			System.out.println("Invalid salary");
			System.exit(0);
		}
		this.salary = salary;
	}
	//override toString method
	public String toString()
	{
		return super.toString() + " at Salary $" + getSalary() + ".";
	}
	public boolean equals(SalariedEmployee other)
	{
		return super.equals(other) && getSalary() == other.getSalary();
	}
	
}
