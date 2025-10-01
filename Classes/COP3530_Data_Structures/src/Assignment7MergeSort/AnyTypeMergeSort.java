package Assignment7MergeSort;

/*
Task – 1:
Write a java program (IntegerMergeSort.java) to implement the Merge Sort algorithm to
sort the integer array. Your program will have the following method signature:
• public void mergeSort(int[] A, int lowerBound, int upperBound)
• public void merge(int[] A, int lowerBound, int midPoint, int upperBound)
Task – 2:
Write a java program (AnyTypeMergeSort.java) to implement the Merge Sort algorithm to
sort the array containing any type of elements (suppose strings). Your program will have the following
method signature:
• public void mergeSort(T[] A, int lowerBound, int upperBound)
• public void merge(T[] A, int lowerBound, int midPoint, int upperBound)
[Hint: use Comparable interface from java library and override the CompareTo method to compare
two objects. Read some stuff about Comparable interface here.
https://docs.oracle.com/javase/8/docs/api/java/lang/Comparable.html
*/

public class AnyTypeMergeSort<T extends Comparable<T>> {
	// This method sorts an array of any type using the merge sort algorithm.
	public void mergeSort(T[] A, int lowerBound, int upperBound) {
        if (lowerBound < upperBound) {
            int midPoint = (lowerBound + upperBound) / 2;
            mergeSort(A, lowerBound, midPoint);
            mergeSort(A, midPoint + 1, upperBound);
            merge(A, lowerBound, midPoint, upperBound);
        }
    }
	 //	This method merges two sorted subarrays into a single sorted array.
    public void merge(T[] A, int lowerBound, int midPoint, int upperBound) {
        int leftSize = midPoint - lowerBound + 1;
        int rightSize = upperBound - midPoint;
        // Create temporary arrays to hold the left and right subarrays.
        T[] leftArray = (T[]) new Comparable[leftSize];
        T[] rightArray = (T[]) new Comparable[rightSize];
        // Copy data to temporary arrays.
        for (int i = 0; i < leftSize; i++)
            leftArray[i] = A[lowerBound + i];
        // Copy data to temporary arrays.
        for (int j = 0; j < rightSize; j++)
            rightArray[j] = A[midPoint + 1 + j];
        // Merge the temporary arrays back into the original array.
        int i = 0, j = 0, k = lowerBound;
        // 	
        while (i < leftSize && j < rightSize) {
            if (leftArray[i].compareTo(rightArray[j]) <= 0) {
                A[k++] = leftArray[i++];
            } else {
                A[k++] = rightArray[j++];
            }
        }
        // Copy remaining elements of leftArray if any.
        while (i < leftSize) {
            A[k++] = leftArray[i++];
        }
        // Copy remaining elements of rightArray if any.
        while (j < rightSize) {
            A[k++] = rightArray[j++];
        }
    }
    // Main method to test the sorting algorithm.
    public static void main(String[] args) {
        String[] A = {"apple", "orange", "banana", "grape"};
        AnyTypeMergeSort<String> sorter = new AnyTypeMergeSort<>();
        sorter.mergeSort(A, 0, A.length - 1);
        // Print the sorted array.
        System.out.print("Sorted array: ");
        for (String str : A) {
            System.out.print(str + " ");
        }
    }
}