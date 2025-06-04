package assignment_lll;

public class Doctor extends SalariedEmployee
{
	private double visitFee;
	private String specialty;
		
	// Default constructor
	public Doctor()
	{
		this(new SalariedEmployee(), 0.0, "none");
	}
	// Argument constructor
	public Doctor(SalariedEmployee salary, double visitFee, String speciality)
	{
		super(salary); // call to superclass constructor
		setVisitFee(visitFee);
		setSpeciality(speciality);
	}
	// Copy constructor
	public Doctor(Doctor object)
	{
		super(object); // call to superclass copy constructor
		this.visitFee = object.visitFee;
		this.specialty = object.specialty;
	}
	public void setVisitFee(double fee)
	{
		if (fee < 0)
		{
			System.out.println("Visit fee cannot be negative");
			System.exit(0);
		}
		this.visitFee = fee;
	}
	public void setSpeciality(String specialty)
	{
		this.specialty = specialty;
	}
	public String getSpeciality()
	{
		return specialty;
	}
	public double getVisitFee()
	{
		return visitFee;
	}
	public String toString()
	{
		return super.toString() + "\nThe speciality is " + getSpeciality() + 
				" and visit fee is $" + getVisitFee()+ ".";
	}
	public boolean equals(Doctor other)
	{
		return super.equals(other) && getName().equals(other.getName())
				&& Double.compare(getVisitFee(), other.getVisitFee()) == 0;
	}	
}

