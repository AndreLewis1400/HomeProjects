package Assignment_Vll;
import java.io.*;
import java.util.Scanner;

public class SentenceAppender {

	private String sourceFile;

	// Default constructor
	public SentenceAppender() {
		this("");
	}

	// Argument constructor
	public SentenceAppender(String sourceFile) {
		this.sourceFile = sourceFile;
	}

	public String getSourceFile() {
		return sourceFile;
	}

	public void setSourceFile(String sourceFile) throws IOException {
		this.sourceFile = sourceFile;
		appendSentences(); // Call separate method for appending
	}

	private void appendSentences() throws IOException {
		try (Scanner keyboard = new Scanner(System.in);
		     PrintWriter pw = new PrintWriter(new FileOutputStream(sourceFile, true))) {

			System.out.print("How many sentences would you like to enter? ");
			int sentenceCount;
			while (true) {
				try {
					sentenceCount = Integer.parseInt(keyboard.nextLine().trim());
					if (sentenceCount > 0) break;
					System.out.println("Please enter a positive number.");
				} catch (NumberFormatException e) {
					System.out.println("Invalid input. Please enter a valid integer.");
				}
			}

			for (int i = 0; i < sentenceCount; ++i) {
				System.out.print("Enter sentence " + (i + 1) + " (end with a period): ");
				String sentence = keyboard.nextLine();
				pw.println(sentence);
			}

			System.out.println("Sentences appended successfully");

		} catch (FileNotFoundException e) {
			throw new IOException("Unable to open or create file: " + sourceFile, e);
		} 
	}
}
