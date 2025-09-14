package employeeProject;

public class Employee 
{
	private String name;
	private Date hireDate;
	
	// Default constructor
	public Employee()
	{
		this("No name yet.", new Date());
	}
	// Argument constructor
	public Employee(String name, Date hireDate)
	{
		setName(name);
		setHireDate(hireDate);
	}
	// Copy constructor
	public Employee(Employee otherEmployee)
	{
		this(otherEmployee.getName(), otherEmployee.getHireDate());
	}
	public void setName(String name)
	{
		if (name != null)
		{
			this.name = name;
		}
		else {
			System.out.println("Invalid Name.");
			System.exit(0);
		}
	}
	public void setHireDate(Date hireDate)
	{
		if (hireDate == null)
		{
			System.out.println("Invalid hiring date.");
			System.exit(0);
		}
		this.hireDate = hireDate;
	}
	public String getName()
	{
		return name;
	}
	public Date getHireDate()
	{
		return hireDate;
	}
	public String toString()
	{
		return getName() + " was hired on " + getHireDate();
	}
	public boolean equals(Employee otherEmployee)
	{
		return getName().equals(otherEmployee.getName()) &&
				getHireDate().equals(otherEmployee.getHireDate());
	}
}
