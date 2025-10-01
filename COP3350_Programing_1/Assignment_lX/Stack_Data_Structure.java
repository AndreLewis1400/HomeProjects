package Assignment_Vlll;

import java.util.Scanner;
import java.util.Stack;

public class Stack_Data_Structure {

    public static String checkParenthesis(String expression) {
        Stack<Character> stack = new Stack<>();

        for (int i = 0; i < expression.length(); i++) {
            char ch = expression.charAt(i);

            // Push opening brackets onto the stack
            if (ch == '(' || ch == '{' || ch == '[') {
                stack.push(ch);
            }
            // Check for matching closing brackets
            else if (ch == ')' || ch == '}' || ch == ']') {
                // If stack is empty or top of stack doesn't match, return "Not Balanced"
                if (stack.isEmpty()) {
                    return "Not Balanced";
                }
                char top = stack.pop();
                if ((ch == ')' && top != '(') || 
                    (ch == '}' && top != '{') || 
                    (ch == ']' && top != '[')) {
                    return "Not Balanced";
                }
            }
        }

        // If stack is not empty, some opening brackets are unmatched
        return stack.isEmpty() ? "Balanced" : "Not Balanced";
    }

    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Enter the parentheses expression:");
        String userInput = keyboard.nextLine();

        String result = checkParenthesis(userInput);
        System.out.println("The expression is: " + result);

        keyboard.close();
    }
}
