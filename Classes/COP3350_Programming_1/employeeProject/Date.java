package employeeProject;

public class Date 
{
	String month;
	int day;
	int year;

	// Default constructor
public Date()
{
	this .month = "January";
	this.day = 1;
	this.year = 1000;
}
	// Argument Constructor
public Date(String month, int day, int year)
{
	setDate(month, day, year);
}
public Date(int month, int day, int year)
{
	setDate(month, day, year);
}
public Date(int year)
{
	setDate(1, 1, year);
}
	// Copy constructor
public Date(Date aDate)
{
	this.month = aDate.month;
	this.day = aDate.day;
	this.year = aDate.year;
}
public void setDate(String month, int day, int year)
{
	if (dateOK(month, day, year) == true)
	{
		this.month = month;
		this.day = day;
		this.year = year;
	}
	else
	{
		System.out.println("Fatal Error");
		System.exit(0);
	}
}
public void setDate(int month, int day, int year)
{
	if (dateOK(month, day, year) == true)
	{
		this.month = monthString(month);
		this.day = day;
		this.year = year;
	}
	else
	{
		System.out.println("Fatal Error");
		System.exit(0);
	}
}
public void setMonth(String month)
{
	if (monthOK(month))
	{
		this.month = month;
	}
	else
	{
		System.out.println("Invalid month");
	}
}
public void setMonth(int month)
{
	if (month >= 1 && month <= 12)
	{
		this.month = monthString(month);
	}
	else 
		System.out.println("Invalid month");
}
public void setDay(int day)
{
	if (day >= 1 && day <= 31)
		this.day = day;
	else 
		System.out.println("Invalid day");
}
public void setYear(int year)
{
	if (year >= 1000 && year <= 9999)
		this.year = year;
	else 
		System.out.println("Invalid year");
}
public String getMonth()
{
	return month;
}
public int getYear()
{
	return year;
}
public String monthString(int month)
{
	switch(month)
	{
	case 1:
		return "January";
	case 2:
		return "February";
		case 3:
			return "March";
		case 4:
			return "April";
			case 5:
				return "May";
			case 6:
				return "June";
				case 7:
					return "July";
				case 8:
					return "August";
					case 9:
						return "September";
					case  10:
						return "October";
						case 11:
							return "November";
						case 12:
							return "December";
							default:
								return "Error";							
	}
}
public boolean dateOK(String month, int day, int year)
{
	if (monthOK(month) && (day >= 1 && day <= 31) && (year >= 1000 && year <= 9999))
		return true;
	else 
		return false;
}
public boolean dateOK(int month, int day, int year)
{
	if ((month >= 1 && month <= 12) && (day >= 1 && day <= 31) && (year >= 1000 && year <= 9999))
		return true;
	else 
		return false;
}
public boolean monthOK(String month)
{
	if (month.equals("January") || month.equals("Feburary") || month.equals("March")
			|| (month.equals("April") || month.equals("May") || month.equals("June")
			|| (month.endsWith("July") || month.equals("August") || month.equals("September")
		    || (month.equals("October") || month.equals("November") || month.equals("December")))))
		return true;
	else 
		return false;
}
public String toString()
{
	return (month + " " + day + " " + year);
}
public boolean equals(Date otherDate)
{
	return (month.equals(otherDate.month) && (day == otherDate.day) && year == otherDate.year);
}
}