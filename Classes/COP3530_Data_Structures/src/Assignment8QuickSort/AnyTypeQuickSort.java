package Assignment8QuickSort;

import java.util.Random;

public class AnyTypeQuickSort<T extends Comparable<T>> {

    private final Random rand = new Random();

    // QuickSort function that sorts the array between lowerBound and upperBound
    public void quickSort(T[] A, int lowerBound, int upperBound) {
        if (lowerBound < upperBound) {
            int pivotIndex = randomizedPartition(A, lowerBound, upperBound);
            quickSort(A, lowerBound, pivotIndex - 1);
            quickSort(A, pivotIndex + 1, upperBound);
        }
    }

    // Randomized partition: picks a random pivot and swaps with the end
    public int randomizedPartition(T[] A, int lowerBound, int upperBound) {
        int pivotIndex = rand.nextInt(upperBound - lowerBound + 1) + lowerBound;
        swap(A, pivotIndex, upperBound);
        return partition(A, lowerBound, upperBound);
    }

    // Partition the array and return the index of the pivot
    public int partition(T[] A, int lowerBound, int upperBound) {
        T pivot = A[upperBound];
        int i = lowerBound - 1;
        for (int j = lowerBound; j < upperBound; j++) {
            if (A[j].compareTo(pivot) <= 0) {
                i++;
                swap(A, i, j);
            }
        }
        swap(A, i + 1, upperBound);
        return i + 1;
    }

    // Helper method to swap two elements in the array
    private void swap(T[] A, int i, int j) {
        T temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    // Main method for testing
    public static void main(String[] args) {
        AnyTypeQuickSort<String> sorter = new AnyTypeQuickSort<>();
        String[] arr = {"banana", "apple", "grape", "cherry", "orange"};

        System.out.println("Original array:");
        for (String s : arr) System.out.print(s + " ");

        sorter.quickSort(arr, 0, arr.length - 1);

        System.out.println("\n\nSorted array:");
        for (String s : arr) System.out.print(s + " ");
    }
}
