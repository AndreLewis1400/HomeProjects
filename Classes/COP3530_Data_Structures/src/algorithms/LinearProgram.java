package algorithms;
import java.util.ArrayList;
import java.util.List;

public class LinearProgram {

	public static void main(String[] args) {

		int [] n = new int[] {16, 17, 4, 3, 5, 2};
		List<Integer> dominantElement = new ArrayList<>();
		int dominantVariable =n[n.length-1];  // Get the last element in the array

		for (int i = n.length-1; i >= 0 ; --i) { // Iterate through array n from right to left
			if (n[i] >= dominantVariable) {
				dominantVariable = n[i];
				dominantElement.add(dominantVariable);
			}
			else {
				System.out.println("....Searching for dominant element\n" + n[i] + " Is not dominant!" );
			}
		}
		System.out.print("The dominant Elemenst are: ");
		for (int j = dominantElement.size() -1; j >= 0; --j) { // iterate through dominantElement list from right to left
			if (dominantElement.get(j) == dominantElement.get(0)) { // Omit the comma after printing the first element in the list
				System.out.print(dominantElement.get(j));
			}
			else {
				System.out.print(dominantElement.get(j) + ", ");
			}
		}
	}

}