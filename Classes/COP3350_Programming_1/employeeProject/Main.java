package employeeProject;

public class Main {

	public static void main(String[] args) {
		HourlyEmployee e1 = new HourlyEmployee();
		System.out.println(e1.getName());
		System.out.println(e1);
		
		HourlyEmployee e2 = new HourlyEmployee("John", new Date(5, 12, 2021), 37, 45);
		System.out.println(e2);
		
		SalariedEmployee e3 = new SalariedEmployee();
		System.out.println(e3);
		SalariedEmployee e4 = new SalariedEmployee("Robert", new Date(12,12,2021), 89000);
		System.out.println(e4);
		System.out.println(e4.getPay());
		System.out.println(e2.getPay());
		
		HourlyEmployee e5 = new HourlyEmployee(e2);
		System.out.println(e5);
		
		System.out.println(e2.equals(e5));
	}

}
