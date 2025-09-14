package Polymorphism;

public class Manager extends Employee
{
	private int bonus;
	
	// Default constructor
	public Manager()
	{
		this(new Employee(),0);
	}
	// Argument constructor
	public Manager(Employee emp, int bonus)
	{
		super(emp);
		setBonus(bonus);
	}
	// Copy constructor
	public Manager(Manager object)
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
	// Overridden method
	public double addBonus()
	{
		return getSalary() + getBonus();
	}
	// Overridden method
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
	// Overridden method
	public String toString()
	{
		return super.toString() + addBonus();
	}
	// Overridden method
	public boolean equals(Manager other)
	{
		return super.equals(other) && getBonus()== other.getBonus() &&
				addBonus() == other.addBonus();
	}
}
