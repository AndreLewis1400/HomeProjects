package assignment_lll;

public class Patient extends Person 
{
	private Doctor primaryDoctor;
	
	// Default constructor
	public Patient()
	{
		this("No name yet.", new Doctor());
	}
	// Argument constructor
	public Patient(String name, Doctor primaryDoctor)
	{
		super(name);
		setPrimaryDoctor(primaryDoctor);
	}
	// Copy constructor
	public Patient(Patient object)
	{
		super(object);
		this.primaryDoctor= new Doctor(object.getPrimaryDoctor()); // Deep copy of Doctor
	}
	public Doctor getPrimaryDoctor() {
		return primaryDoctor;
	}
	public void setPrimaryDoctor(Doctor primaryDoctor)
	{
		this.primaryDoctor = primaryDoctor;
	}
	public String toString()
	{
		return "The name is: " + super.toString() + ", Primary doctor is: " + getPrimaryDoctor().getName();
	}
	public boolean equals(Patient other)
	{
		return super.equals(other) && getPrimaryDoctor().equals(other.getPrimaryDoctor());
	}
	
}

