package assignment_lll;

public class Person 
{
	// Instance variable
	private String name;
	
	// Default constructor
	public Person()
	{
		this("No name yet.");
	}
	// Argument constructor
	public Person(String name)
	{
		setName(name);
	}
	// Copy constructor
	public Person(Person object)
	{
		this(object.getName());
	}
	public String getName() {
		return name;
	}
	public void setName(String name) 
	{
		if (name != null)
		{
			this.name = name;
		}
		else 
		{
			System.out.println("Invalid Name.");
			System.exit(0);
		}
		
	}
	public String toString()
	{
		return getName();
	}
	public boolean equals(Person other)
	{
		return getName().equals(other.getName());
	}
}
