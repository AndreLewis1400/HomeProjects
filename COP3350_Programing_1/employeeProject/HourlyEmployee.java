package employeeProject;

public class HourlyEmployee extends Employee
{
	private double hours;
	private double wageRate;
	
	//Default constructor 
	public HourlyEmployee()
	{
		this("No name yet", new Date(), 0.0,0.0); //Initialize field variables
	}
	//Argument constructor
	public HourlyEmployee(String name, Date hireDate, double hours, double wageRate)
	{
		super(name, hireDate); // call to parent class constructor "Employee"
		setHours(hours);
		setWageRate(wageRate);
	}
	//Copy constructor
	public HourlyEmployee(HourlyEmployee otherEmployee)
	{
		super(otherEmployee); // call to Employee copy constructor
		setHours(otherEmployee.getHours());
		setWageRate(otherEmployee.getWageRate());
//		this(otherEmployee.getName(), otherEmployee.getHireDate(), otherEmployee.getHours(), otherEmployee.getWageRate());
		
	}
	public void setHours(double hours)
	{
		if (hours < 0.0 || hours > 40)
		{
			System.out.println("Invalid working hours.");
			System.exit(0);
		}
		this.hours = hours;
	}
	public void setWageRate(double wageRate)
	{
		if (wageRate < 0.0)
		{
			System.out.println("Invalid Wage Rae.");
			System.exit(0);
		}
		this.wageRate = wageRate;
	}
	public double getHours()
	{
		return hours;
	}
	public double getWageRate()
	{
		return wageRate;
	}
	public double getPay()
	{
		return getHours() * getWageRate();
	}
	public String toString()
	{
		return super.toString() + " to work for " + getHours() + 
			" hours, and has a wage rate $" + getWageRate();
	}
	public boolean equals(HourlyEmployee other)
	{
		return super.equals(other) && getHours() == other.getHours() 
				&& getWageRate() == other.getWageRate();
	}
}

