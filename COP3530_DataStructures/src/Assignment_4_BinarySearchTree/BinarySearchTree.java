package Assignment_4_BinarySearchTree;

public class BinarySearchTree {
	
	Node root;
	
	// Constructor
	BinarySearchTree(){
		root = null;
	}
	// Insert a key into the BST
	void BSTInsert(int key) {
		root = BSTInsert(root, key);
    }

	Node BSTInsert(Node root, int key) {
		if (root == null) {
			root = new Node(key);
			return root;
		}
		if (key < root.key)
			root.leftChild = BSTInsert(root.leftChild, key);
		else if (key > root.key)
			root.rightChild = BSTInsert(root.rightChild, key);
		return root;
	}
	// Find the minimum value node in the BST
	Node TreeMinimum(Node node) {
		while (node.leftChild != null) {
			node = node.leftChild;
		}
		return node;
	}
	// Find the maximum value node in the BST
	Node TreeMaximum(Node node) {
		while (node.rightChild != null) {
			node = node.rightChild;
		}
		return node;
	}
	// Search for a value in the BST
	Node TreeSearch(Node root, int key) {
		if (root == null || root.key == key)
			return root;
		if (root.key > key)
			return TreeSearch(root.leftChild, key);
		return TreeSearch(root.rightChild, key);
	}
	// Display BST in Inorder Traversal
	void inorder() {
		inorderRec(root);
		System.out.println();
	}
	void inorderRec(Node root) {
		if (root != null) {
			inorderRec(root.leftChild);
			System.out.print(root.key + " ");
			inorderRec(root.rightChild);
		}
	}
}
	

