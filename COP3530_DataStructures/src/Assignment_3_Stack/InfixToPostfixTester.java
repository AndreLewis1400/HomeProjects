package Assignment_3_Stack;

import java.util.Scanner;

public class InfixToPostfixTester {

	public static void main(String[] args) {

		Scanner keyboard = new Scanner(System.in);
		System.out.print("Enter infix expression: ");
		String infixStr = keyboard.nextLine();
		Character[] infixArray = InfixToPostfix.inputString(infixStr);
		keyboard.close();

		// Convert infix to postfix
		InfixToPostfix <Character> converter = new InfixToPostfix<>(infixArray.length);
		Object[] postfix = converter.infixToPostFix(infixArray);

		// print result
		converter.printResult();
	}
}