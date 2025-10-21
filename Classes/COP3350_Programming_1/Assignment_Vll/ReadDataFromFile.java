package Assignment_Vll;

import java.io.*;
import java.util.Scanner;

public class ReadDataFromFile {

    public static void main(String[] args) {
        FileCopier fileCopier = new FileCopier();
        SentenceAppender sentenceAppender = new SentenceAppender();

        try (Scanner keyboard = new Scanner(System.in)) {
            System.out.println("Enter sourceFile name containing sentences:");
            String sourceFileName = keyboard.nextLine();
            String temporaryFile = "tempFile_1.txt";
            
            sentenceAppender.setSourceFile(sourceFileName);

            System.out.println("Original file contents:");
            displayFileContents(sentenceAppender.getSourceFile());

            fileCopier.setCopyFiles(sentenceAppender, temporaryFile);

            System.out.println("\nUpdated file contents:");
            displayFileContents(fileCopier.getSourceFile2());

        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static void displayFileContents(String filePath) {
        File file = new File(filePath);
        try (Scanner scanner = new Scanner(file)) {
            while (scanner.hasNextLine()) {
                System.out.println(scanner.nextLine());
            }
        } catch (FileNotFoundException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}