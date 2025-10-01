package Assignment8QuickSort;

import java.util.Random;

public class IntegerQuickSort {

    // Public method to perform randomized quicksort on an integer array
    public void quickSort(int[] A, int lowerBound, int upperBound) {
        if (lowerBound < upperBound) {
            int pivotIndex = randomizedPartition(A, lowerBound, upperBound);
            quickSort(A, lowerBound, pivotIndex - 1);
            quickSort(A, pivotIndex + 1, upperBound);
        }
    }

    // Chooses a random pivot and partitions the array
    public int randomizedPartition(int[] A, int lowerBound, int upperBound) {
        Random rand = new Random();
        int pivotIndex = lowerBound + rand.nextInt(upperBound - lowerBound + 1);
        swap(A, pivotIndex, upperBound);
        return partition(A, lowerBound, upperBound);
    }

    // Partitions the array around the pivot
    public int partition(int[] A, int lowerBound, int upperBound) {
        int pivot = A[upperBound];
        int i = lowerBound - 1;
        for (int j = lowerBound; j < upperBound; j++) {
            if (A[j] <= pivot) {
                i++;
                swap(A, i, j);
            }
        }
        swap(A, i + 1, upperBound);
        return i + 1;
    }

    // Swaps two elements in the array
    private void swap(int[] A, int i, int j) {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    // Main method to test quicksort
    public static void main(String[] args) {
        int[] array = {10, 7, 8, 9, 1, 5};      
        System.out.print("Original array: \n");
		for (int num : array) {
			System.out.print(num + " ");
		}
		        System.out.println("\n");
        IntegerQuickSort sorter = new IntegerQuickSort();
        sorter.quickSort(array, 0, array.length - 1);

		        
        System.out.print("Sorted array: \n");
        for (int num : array) {
            System.out.print(num + " ");
        }
    }
}

