package assignment_lll;

public class Billing 
{
	private Patient patient;
	private double amountDue;
	
	// Default constructor
	public Billing()
	{
		this(new Patient(), 0.0);
	}
	// Argument constructor
	public Billing(Patient patient, double amountDue)
	{
		setPatient(patient);
		setAmountDue(amountDue);
	}
	// Copy constructor
	public Billing(Billing object)
	{
		this(object.getPatient(), object.amountDue);

	}
	public Patient getPatient() 
	{
		return patient;
	}
	public void setPatient(Patient patient) 
	{
		this.patient = patient;
	}

	public double getAmountDue() {
		return amountDue;
	}
	public void setAmountDue(double amountDue) {
		this.amountDue = amountDue;
	}
	// Override toString method
	public String toString()
	{
        return "Patient: " + patient.getName() + "\n" +
                "Doctor: " + patient.getPrimaryDoctor().getName() + "\nAmount Due: $" + getAmountDue();
	}
    public boolean equals(Billing other) 
    {
  
            return this.patient.equals(other.getPatient()) &&
                    this.patient.getPrimaryDoctor().equals(other.getPatient().getPrimaryDoctor()) &&
                    this.amountDue == other.amountDue;
    }
  
}

