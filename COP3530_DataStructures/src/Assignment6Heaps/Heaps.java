package Assignment6Heaps;


public class Heaps {

	// Function to maintain the Min-Heap property
	public static void minHeapify(int[] A, int i, int heapSize) {
		int left = 2 * i; // Left child index
		int right = 2 * i + 1; // Right child index
		int smallest = i;
		// Compare with left child
		if (left < heapSize && A[left] < A[smallest])
			smallest = left;
		// Compare with right child
		if (right < heapSize && A[right] < A[smallest])
			smallest = right;
		// If the smallest is not the root
		if (smallest != i) {
			// Swap values
			int temp = A[i];
			A[i] = A[smallest];
			A[smallest] = temp;

			// Recursively heapify the affected subtree
			minHeapify(A, smallest, heapSize);
		}
	}
	// Function to build a Min-Heap from an unsorted array
	public static void buildMinHeap(int[] A) {
		int heapSize = A.length;
		// Start from the last non-leaf node and heapify each node
		for (int i = (heapSize / 2) - 1; i >= 0; i--) {
			// Heapify the subtree rooted at index i
			minHeapify(A, i, heapSize);
		}
	}

	// Heap Sort Algorithm using Min-Heap
	public static void heapSort(int[] A) {
		buildMinHeap(A);
		int heapSize = A.length;
		// One by one extract elements from heap
		for (int i = heapSize - 1; i > 0; i--) {
			// Swap root (min element) with last element
			int temp = A[0];
			A[0] = A[i];
			A[i] = temp;

			// Reduce heap size
			minHeapify(A, 0, i);
		}
		// Reverse the array to get sorted order
		reverseArray(A);
	}
	// Function to reverse the array
	public static void reverseArray(int[] A) {
		int left = 0;
		int right = A.length - 1;
		while (left < right) {
			// Swap values
			int temp = A[left];
			A[left] = A[right];
			A[right] = temp;
			left++;
			right--;
		}
	}
}

