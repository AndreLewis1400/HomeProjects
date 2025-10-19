package Polymorphism;

public class Clerk extends Employee
{
	private int bonus;
	
	// Default constructor
	public Clerk()
	{
		this(new Employee(), 0);
	}
	// argument constructor
	public Clerk(Employee emp, int bonus)
	{
		super(emp);
		setBonus(bonus);
	}
	// Copy constructor
	public Clerk(Clerk object)
	{
		super(object);
		setBonus(object.getBonus());
		object.addBonus();
	}
	public int getBonus() {
		return bonus;
	}
	public void setBonus(int bonus) {
		this.bonus = bonus;
	}
	// Override method
	public double addBonus()
	{
		return getSalary() + getBonus();
	}
	// Override method
	public int salaryDeductions(int absentDays)
	{
		{
			int deduction = 0;
			switch (absentDays)
			{
			case 1:
				deduction = 505;
				break;
			case 2:
				deduction = 1530;
				break;
			case 3:
				deduction = 2295;
				break;
			case 4:
				deduction =  2000;
				break;
			}
			return deduction; 
		}
	}
	// Override method
	public String toString()
	{
		return super.toString() + addBonus();
	}
	// Override method
	public boolean equals(Clerk other)
	{
		return super.equals(other) && getBonus() == other.getBonus()
				&& addBonus() == other.addBonus();
	}
	
}
