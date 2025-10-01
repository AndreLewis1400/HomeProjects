package Assignment6Heaps;

public class TestHeaps {

    public static void main(String[] args) {
        int[] arr = {4, 10, 3, 5, 1, 7, 6, 8, 2, 9};

        System.out.println("Original array:");
        for (int num : arr) {
            System.out.print(num + " ");
        }
        System.out.println();

        // Building a Min-Heap
        Heaps.buildMinHeap(arr);
        System.out.println("Min-Heap:");
        for (int num : arr) {
            System.out.print(num + " ");
        }
        System.out.println();

        // Performing Heap Sort
        Heaps.heapSort(arr);
        System.out.println("Sorted array:");
        for (int num : arr) {
            System.out.print(num + " ");
        }
    }

}
