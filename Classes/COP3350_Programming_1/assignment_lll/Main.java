package assignment_lll;

public class Main 
{

	public static void main(String[] args) 
	{		
		Doctor doc1 = new Doctor(new SalariedEmployee("Bob", new Date(12 , 31, 1969), 34000.0), 10.5, "Pediatrician");
		System.out.println(doc1);
		
		Doctor doc2 = new Doctor(new SalariedEmployee("Susan", new Date(02 , 24, 1999), 78000.0), 150.5, "Obstetrician");
		System.out.println(doc2);
		
		Doctor doc3 = new Doctor(new SalariedEmployee("Lilly", new Date(01 , 15, 1869), 65000.0), 95.5, "General Practitioner");
		System.out.println(doc3);

		System.out.println("\n*Patient's Information*");
		Patient patient1 = new Patient("Fred", doc1);
		System.out.println(patient1);
		
		Patient patient2 = new Patient("Sally", doc2);
		System.out.println(patient2);
		
		Patient patient3 = new Patient("John", doc3);
		System.out.println(patient3);
		
		System.out.println("\n*Billing's Information*");
		Billing bill1 = new Billing(patient1, 21.0);
		System.out.println(bill1);
		
		Billing bill2 = new Billing(patient2, 150.5);
		System.out.println(bill2);
		
		Billing bill3 = new Billing(patient3, 170.0);
		System.out.println(bill3);
		
		System.out.println("The total income from billing records is: " + (bill1.getAmountDue() + bill2.getAmountDue() + bill3.getAmountDue()));
	}

}
