package assignment_lll;

public class Employee extends Person 
{
	// Instance variable
	private Date hireDate;
	
	// Default constructor
	public Employee()
	{
		this("No name yet", new Date());
	}
	// Argument constructor
	public Employee(String name, Date hireDate)
	{
		super(name);
		setHireDate(hireDate);	
	}
	// Copy constructor
	public Employee(Employee object)
	{
		super(object);
		setHireDate(object.getHireDate());
	}
	public Date getHireDate() 
	{
		return hireDate;
	}
	public void setHireDate(Date hireDate) 
	{
		{
			if (hireDate == null)
			{
				System.out.println("Invalid hiring date.");
				System.exit(0);
			}
			this.hireDate = hireDate;
		}
	}
	public String toString()
	{
		return "The doctor " + super.getName() + " was hired on " + getHireDate();
	}
	public boolean equals(Employee other)
	{
		return getName().equals(other.getName()) &&
				getHireDate().equals(other.getHireDate());
	}
}
