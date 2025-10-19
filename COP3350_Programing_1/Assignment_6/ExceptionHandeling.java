package Assignment_6;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExceptionHandeling {

	// Method to check if the input string contains exactly 4 digits
	public static boolean hasFourDigits(String str1) {
		Pattern pattern = Pattern.compile("\\d{4}"); 
		Matcher matcher = pattern.matcher(str1); 
		return matcher.find(); 
	}
	// Method to check if the input string contains exactly 4 digits (alternative way)
	public static boolean containsFourDigits(String str1) {
		int digitCount = 0;
		for (char c : str1.toCharArray()) {
			if (Character.isDigit(c)) {
				digitCount++;
			}
		}
		// Return true if there are exactly 4 digits
		return digitCount == 4;
	}
	// Method to check if the input year is a leap year and adjust the number of days in February
    public static String isLeapYear(String month, String days, String year) {
        String leapdays = days;
        int yearInt = Integer.valueOf(year);
        int dayInt = Integer.valueOf(days);

        // Check if the month is February
        if (month.equals("February")) {
            if ((yearInt % 400 == 0) || (yearInt % 100 != 0 && yearInt % 4 == 0)) {
                // Leap year: allow up to 29 days
                if (dayInt > 29) {
                    leapdays = "29";
                }
            } else {
                // Not a leap year: limit to 28 days
                if (dayInt > 28) {
                    leapdays = "28";
                }
            }
        }

        return leapdays;
    }
	public static void main(String[] args) throws Exception {

		Scanner keyboard = new Scanner(System.in);

		String month[] = new String[] {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

		System.out.println("Enter date to parse (MM/DD/YYYY format):");

		String token1 = "", token2 = "", token3 = "";

		final int MAX_DAY = 31, MAX_MONTH = 12;

		String date = keyboard.nextLine();

		// Creates a StringTokenizer object "str1" and returns delimiters

		StringTokenizer str1 = new StringTokenizer(date, "/", false);

		if (str1.countTokens() !=3) {
			System.out.println("Invalid date format. Please use MM/DD/YYYY format.");
			System.exit(0);
		}

		while (str1.hasMoreTokens()) {

			token1 = str1.nextToken();

			try {
				// Convert the first token (month) to an integer and validate if it's within valid month range
				if ( Integer.valueOf(token1) <= MAX_MONTH) {
					token1 = month[Integer.valueOf(token1)-1];				
				}
				else {
					token1 = month[Integer.valueOf(token1)-1];
				}
				// Handle invalid month input by asking the user to reenter a valid month
			}catch(ArrayIndexOutOfBoundsException MonthException) {
				while (Integer.valueOf(token1) > month.length) {
					System.out.println("Invalid month. Reenter a valid month:");
					token1 = keyboard.nextLine();
				}
				token1 = month[Integer.valueOf(token1)-1];	
			}
			try {
				// If the second token (day) is available, validate it
				if (str1.hasMoreTokens()) {
					token2 = str1.nextToken();
					// Handle specific month-day validations for months with 31 days
					switch (token1) {

					case "February":
						if (Integer.valueOf(token2) > 28 || Integer.valueOf(token2) < 1)throw new  NumberFormatException(); {
							break;
						}						
					case "January", "October", "December", "March", "July", "May", "August":
						if (Integer.valueOf(token2) > 31 || Integer.valueOf(token2) < 1) throw new NumberFormatException(); {
							break;
						}				
					case "April", "September", "June", "November":
						if(Integer.valueOf(token2) > 30 || Integer.valueOf(token2) < 1) throw new NumberFormatException(); {
							break;
						}		
					}
				}
			}catch(NumberFormatException DayException) {
				// Handle invalid day input by asking the user to reenter a valid day
				switch (token1) {

				case "February":
					while((Integer.valueOf(token2) > 28 || Integer.valueOf(token2) < 1)) {
						System.out.println("Invalid day. Reenter a valid day:"); 
						token2 = keyboard.nextLine();
					}
					break;						
				case "January", "October", "December", "March", "July", "May", "August":
					while ((Integer.valueOf(token2) > 31 || Integer.valueOf(token2) < 1)) {
						System.out.println("Invalid day. Reenter a valid day:"); 
						token2 = keyboard.nextLine();
					}
				break;

				case "April", "September", "June", "November":
					while ((Integer.valueOf(token2) > 30 || Integer.valueOf(token2) < 1))  {
						System.out.println("Invalid day. Reenter a valid day:");
						token2 = keyboard.nextLine();
					}
				break;		
				}
			}
			try {
				// If the third token (year) is available, validate if it contains 4 digits
				if (str1.hasMoreTokens()) {
					token3 = str1.nextToken();
					if ((!(hasFourDigits(token3)) || Integer.valueOf(token3) > 2024)) {
						throw new  NumberFormatException();
					}
				}
			}catch(NumberFormatException YearException) {
				while ((containsFourDigits(token3)) && Integer.valueOf(token3) > 2024 || (!(containsFourDigits(token3)))) {
					System.out.println("Invalid year. Reenter a valid year:");  
					token3 = keyboard.nextLine();
				}
			}
			// Adjust the day for leap years if necessary
			token2 = isLeapYear(token1,token2,token3);
			System.out.println("Parsed date: " + token1 + " " + token2 + ", " + token3);
		}	
		keyboard.close();
	}
}



