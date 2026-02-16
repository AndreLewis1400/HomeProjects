package Assignment7MergeSort;

public class IntegerMergeSort {
	// This method sorts an array of integers using the merge sort algorithm.
	public void mergeSort(int[] A, int lowerBound, int upperBound) {
        if (lowerBound < upperBound) {
            int midPoint = (lowerBound + upperBound) / 2;
            mergeSort(A, lowerBound, midPoint);
            mergeSort(A, midPoint + 1, upperBound);
            merge(A, lowerBound, midPoint, upperBound);
        }
    }
	// This method merges two sorted subarrays into a single sorted array.
    public void merge(int[] A, int lowerBound, int midPoint, int upperBound) {
        int leftSize = midPoint - lowerBound + 1;
        int rightSize = upperBound - midPoint;
        // Create temporary arrays to hold the left and right subarrays.
        int[] leftArray = new int[leftSize];
        int[] rightArray = new int[rightSize];
        //	Copy data to temporary arrays.
        for (int i = 0; i < leftSize; i++) 
            leftArray[i] = A[lowerBound + i];
        // 	
        for (int j = 0; j < rightSize; j++) 
            rightArray[j] = A[midPoint + 1 + j];
        // Merge the temporary arrays back into the original array.
        int i = 0, j = 0, k = lowerBound;
        // 	
        while (i < leftSize && j < rightSize) {
            if (leftArray[i] <= rightArray[j]) {
                A[k++] = leftArray[i++];
            } else {
                A[k++] = rightArray[j++];
            }
        }
        // 	Copy remaining elements of leftArray if any.
        while (i < leftSize) {
            A[k++] = leftArray[i++];
        }
        // 	Copy remaining elements of rightArray if any.
        while (j < rightSize) {
            A[k++] = rightArray[j++];
        }
    }
    // Main method to test the sorting algorithm.
    public static void main(String[] args) {
        int[] A = {5, 2, 9, 1, 5, 6};
        IntegerMergeSort sorter = new IntegerMergeSort();
        sorter.mergeSort(A, 0, A.length - 1);
        // Print the sorted array.
        System.out.print("Sorted array: ");
        for (int num : A) {
            System.out.print(num + " ");
        }
    }
}

