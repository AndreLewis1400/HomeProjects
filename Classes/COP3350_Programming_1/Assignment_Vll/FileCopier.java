package Assignment_Vll;

import java.io.*;
import java.util.Scanner;

public class FileCopier {

    private String temporaryFile;
    private String sourceFile2;

    public FileCopier() {
        this("", "");
    }

    public FileCopier(String temporaryFile, String sourceFile2) {
        this.temporaryFile = temporaryFile;
        this.sourceFile2 = sourceFile2;
    }

    public String getTemporaryFile() {
        return temporaryFile;
    }

    public void setCopyFiles(SentenceAppender sourceFile, String temporaryFile) throws IOException {
        this.temporaryFile = temporaryFile;
        this.sourceFile2 = copyFiles(sourceFile.getSourceFile(), temporaryFile);
    }

    private String copyFiles(String sourceFilePath, String temporaryFile) throws IOException {
        File sourceFile = new File(sourceFilePath);

        if (!sourceFile.exists()) {
            throw new FileNotFoundException(sourceFilePath + " does not exist.");
        }

        if (sourceFile.isFile()) {
            System.out.println(sourceFilePath + " is a file.");
            
            copyToTemporary(sourceFilePath, temporaryFile);
            copyBackToSource(sourceFilePath, temporaryFile);
            
            new File(temporaryFile).delete();
            System.out.println("Temporary file deleted.");
        } else {
            System.out.println(sourceFilePath + " is not a file.");
        }

        return sourceFile.getAbsolutePath();
    }

    private void copyToTemporary(String sourceFilePath, String temporaryFile) throws IOException {
        try (Scanner sourceScanner = new Scanner(new File(sourceFilePath));
             PrintWriter tempWriter = new PrintWriter(new FileWriter(temporaryFile, true))) {

            while (sourceScanner.hasNextLine()) {
                String line = sourceScanner.nextLine();
                if (line.endsWith(".")){
                	tempWriter.println(line);
                }
                if (line.endsWith(".")) {
                    line = line.substring(0, line.length() - 1);
                    tempWriter.println(line);
                }             
            }
            System.out.println("Content copied successfully to " + temporaryFile);
        }
    }

    private void copyBackToSource(String sourceFilePath, String temporaryFile) throws IOException {
        int count = 0;
        StringBuilder content = new StringBuilder();

        try (Scanner tempScanner = new Scanner(new File(temporaryFile))) {
            while (tempScanner.hasNextLine()) {
                content.append(tempScanner.nextLine()).append(System.lineSeparator());
            }
        }

        try (Scanner sourceScanner = new Scanner(new File(sourceFilePath))) {
            while (sourceScanner.hasNextLine()) {
                String line = sourceScanner.nextLine();
                if (line.startsWith("Name of temporary file:")) {
                    String[] parts = line.split("_");
                    if (parts.length > 1) {
                        count = Integer.parseInt(parts[1].split("\\.")[0]);
                    }
                    break;
                }
            }
        }

        count++;

        try (PrintWriter sourceWriter = new PrintWriter(new FileWriter(sourceFilePath))) {
            sourceWriter.print(content.toString());
            sourceWriter.println("Name of temporary file: tempFile_" + count + ".txt");
        }

        System.out.println("Content copied successfully back to " + sourceFilePath);
        
        this.temporaryFile = "tempFile_" + count + ".txt";
    }

    public String getSourceFile2() {
        return sourceFile2;
    }

    public void setSourceFile2(String sourceFile2) {
        this.sourceFile2 = sourceFile2;
    }
}