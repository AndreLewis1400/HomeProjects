package algorithms;

public class RecursiveProgram {

	public static void recursive(int input[], int i, int output[], int negIndex, int posIndex) {
		// Base case: if index i is less than 0, stop recursion
		if (i < 0) {
			return;
		}
		// Check if the current element is negative
		if (input[i] < 0) {
			output[negIndex] = input[i];
			recursive(input, i - 1, output, negIndex - 1, posIndex);
		}
		// If the current element is positive
		else {
			output[posIndex] = input[i];
			recursive(input, i - 1, output, negIndex, posIndex - 1);
		}
	}
	public static void print(int result[]) {

		for (int num : result) {
			System.out.print(num + " ");
		}
	}
	public static void main(String[] args) {

		int[] arr = new int[] {1, -1, 3, 2, -7, -5, 11, 6};
		int[] out = new int[arr.length];
		int i = arr.length -1;
		int negIndex = 2; // Negative numbers from index 2 to 0
		int posIndex = 7; // Positive numbers from index 7 to 3
		recursive(arr, i, out, negIndex, posIndex); // recursive function call

		print(out);
	}
}
