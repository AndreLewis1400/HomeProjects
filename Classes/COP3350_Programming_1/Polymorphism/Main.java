package Polymorphism;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		
		double totalDeductions = 0;
		Scanner keyboard = new Scanner(System.in);
		
		// Create employee objects for each employee
		Employee emp0 = new Employee("E001", "Mark", "HR", 15000.0, "Manager");
		Employee emp1 = new Employee("E012", "Peter", "R&D", 15000.0, "Manager");
		Employee emp2 = new Employee("E056", "Samual", "Accounts", 10000.0, "Clerk");
		Employee emp3 = new Employee("E089", "Sam", "Accounts", 10000.0, "Cashier");
		
		// Create objects for each Manager
		Manager man0 = new Manager(emp0, 300);
		Manager man1 = new Manager(emp1, 300);
		// Create objects for each Clerk
		  Clerk clk0 = new Clerk(emp2, 100);
		  Clerk clk1 = new Clerk(emp3, 100);
		
		System.out.println(man0);
		System.out.println();
			
		System.out.println(man1);
		System.out.println();
				
		System.out.println(clk0);
		System.out.println();
		
		// Check designations
		if (!emp0.equals(emp2))
		{
		System.out.println("Mark and Samual have different Designations\n");
		}
		
		int deductions[] = new int[4];
		int daysPresent[] = new int[4];
		int workingDaysPerMonth = 20;

		System.out.print("Enter the number of days Employee E001 is present out of 20 :");
		daysPresent[0] = (keyboard.nextInt());
		deductions[0] = man0.salaryDeductions(workingDaysPerMonth - daysPresent[0]);
		System.out.print("Enter the number of days Employee E012 is present out of 20 :");
		daysPresent[1] = (keyboard.nextInt());
		deductions[1] = man0.salaryDeductions(workingDaysPerMonth - daysPresent[1]);
		System.out.print("Enter the number of days Employee E056 is present out of 20 :");
		daysPresent[2] = (keyboard.nextInt());
		deductions[2] = clk0.salaryDeductions(workingDaysPerMonth - daysPresent[2]);
		System.out.print("Enter the number of days Employee E089 is present out of 20 :");
		daysPresent[3] = (keyboard.nextInt());
		deductions[3] = clk1.salaryDeductions(workingDaysPerMonth - daysPresent[3]);
	
		System.out.println("\nEmployee ID\t" + "Present\t" + "Absent\t" + "Deductions");
		for (int i = 0; i < deductions.length; ++i)
		{
			// Determine emp based on index and output etc.
			if ( i <=1)
			{
			Employee emp = (i < 1)?emp0: emp1;
			System.out.println(emp.getEmployeeID() + "\t\t" + daysPresent[i] +
					"\t" + (20 - daysPresent[i]) + "\t$" + (double)deductions[i]);
			}
			else
			{
				Employee emp = (i < 3)?emp2: emp3;
				System.out.println(emp.getEmployeeID() + "\t\t" + daysPresent[i] +
						"\t" + (20 - daysPresent[i]) + "\t$" + (double)deductions[i]);
			}
		}
		for (int i = 0; i < deductions.length; ++i)
		{
			totalDeductions += deductions[i];
		}
		System.out.println("Total Deductions : $" + totalDeductions);
		keyboard.close();
	}
}
