package assignment_Vlll_Recursion;
import java.util.InputMismatchException;
import java.util.Scanner;
public class Recursion {
	
	private static int totalHandshakes(int people) {
		if (people < 0) 
			throw new ArithmeticException("Error: enter a valid number >= 0");
		if (people == 0) // When zero people are in the room return 
			return people; 
		else
		return totalHandshakes(people -1) + people - 1; // -1 to avoid counting shaking self hands
	}
	private static int n(int nValue) { // calculates the factorial of Value recursively
		if (nValue < 0) 
			throw new ArithmeticException("Error: enter a valid n_Value >= 0");
		if (nValue <= 1)
			return 1;
		else
			return n(nValue - 1) * nValue;		
	}
	private static int nCr(int n, int r) { // calculate combinations using factorial
		if (r < 0 || r > n) 
			throw new ArithmeticException("Error: enter a valid r_Value (0 <= r <= n)");
		return n(n) / (n(r) * n(n - r));
	}
	public static void main(String[] args) {
		Scanner keyboard = new Scanner(System.in);
		try {
		System.out.println("How many people are in the room?");
		int peopleInRoom = keyboard.nextInt();
		System.out.println("If everyone shakes hands once, there will be " + totalHandshakes(peopleInRoom) + " handshakes.\n");
		System.out.println("Enter value for n:");
		int n_value = keyboard.nextInt();
		System.out.println("Enter value for r:");
		int r_value = keyboard.nextInt();
		System.out.println("There are " + nCr(n_value,r_value) + " possible combinations.");
		}catch (InputMismatchException x){
			System.out.println("Error: enter a valid integer");
			System.exit(0);
		}finally{
		keyboard.close();
		}
	}
}
