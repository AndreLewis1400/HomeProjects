package Assignment_3_Stack;

import java.util.Scanner;

public class InfixToPostfix<T> {

	private CustomStack<T> stack; // Custom Stack implementation
	private Object[] postfixArray; // Array to store postfix expression
	private int postfixIndex; // Tracks the position in the output array

	// Argument Constructor
	public InfixToPostfix(int size) {
		stack = new CustomStack<>();
		postfixArray = new Object[size];
		postfixIndex = 0;
	}
	// Convert input string to array of characters
	public static Character[] inputString(String infixStr) {
		Character[] infixArray = new Character[infixStr.length()];	
		for (int i = 0; i < infixStr.length(); i++)
			if (infixStr.charAt(i) != ' ' ) 
				infixArray[i] = infixStr.charAt(i);
		return infixArray;
	}
	// Custom Stack implementation
	private static class CustomStack<T> {
		private Object[] stack;
		private int top;

		public CustomStack() {
			stack = new Object[10]; // Default size
			top = 0;
		}

		public void push(T data) {
			if (top >= stack.length) {
				// Create a new array with double the size
				T[] temp = (T[])new Object[stack.length * 2];
				for (int i = 0; i < stack.length; ++i)
					temp[i] = (T)stack[i];
				// Replace old stack with new one
				stack = temp;
			}
			// Add new element
			stack[top] = data;
			// increment top index
			top++;
		}


		public T pop() {
			if (top <= 0) {
				throw new RuntimeException("Stack is empty");
			}
			return (T) stack[--top];
		}


		public T peek() {
			if (top <= 0) {
				throw new RuntimeException("Stack is empty");
			}
			return (T) stack[top - 1];
		}

		public boolean isEmpty() {
			return top == 0;
		}
	}
	// Method to return precedence of operators
	static int priority(char ch) {
		switch (ch) {
		case '+': case '-': return 1;  // Lowest precedence
		case '*': case '/': return 2;  // Higher precedence
		case '^': return 3;            // Highest precedence (right associative)
		default: return -1;            // Not an operator
		}
	}

	// Checks if the stack is empty
	public boolean isStackEmpty() { 
		return stack.isEmpty();
	}

	// Method to insert elements into Postfix output array
	private void addToOutput(T data) {
		postfixArray[postfixIndex] = data; 
		postfixIndex++;
	}

	// Method to convert infix to postfix
	public Object[] infixToPostFix(T[] infix) {
		for (int i = 0; i < infix.length; i++) {
			T data = infix[i];
			char ch = data.toString().charAt(0);

			// If operand, add to output
			if (Character.isLetterOrDigit(ch)) {
				addToOutput(data);
			}
			// If '(', push to stack
			else if (ch == '(') {
				stack.push(data);
			}
			// If ')', pop until '(' is found
			else if (ch == ')') {
				while (!stack.isEmpty() && stack.peek().toString().charAt(0) != '(') {
					addToOutput(stack.pop());
				}
				if (!stack.isEmpty() && stack.peek().toString().charAt(0) == '(') {
					stack.pop(); // Remove '('
				}
			}
			// If operator, pop until stack is empty or finds lower precedence operator
			else {
				while (!stack.isEmpty() && priority(ch) < priority(stack.peek().toString().charAt(0))) {
					addToOutput(stack.pop());
				}
				// Fix for exponentiation: If `^` is right-associative, don't pop the same precedence
				if (ch == '^' && !stack.isEmpty() && stack.peek().toString().charAt(0) == '^') {
					stack.push(data);
				} else {
					stack.push(data); // Push current operator (Fixed placement)
				}
			}
		}

		// Pop all remaining operators from the stack
		while (!stack.isEmpty()) {
			addToOutput(stack.pop());
		}

		// Return only non-null elements from output[]
		return getProcessedOutput();
	}

	// Method to return a processed output array (removing null values)
	private Object[] getProcessedOutput() {
		Object[] cleanedOutput = new Object[postfixIndex];
		for (int i = 0; i < postfixIndex; i++) {
			cleanedOutput[i] = postfixArray[i];
		}
		return cleanedOutput;
	}

	public void printResult() {
		System.out.print("Postfix Expression: ");
		for (Object ch : getProcessedOutput()) {
			if (ch != null)
				System.out.print(ch + " ");
		}
		System.out.println();
	}
}
