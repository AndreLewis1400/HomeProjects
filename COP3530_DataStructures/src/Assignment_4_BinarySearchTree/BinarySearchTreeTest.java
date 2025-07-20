package Assignment_4_BinarySearchTree;

public class BinarySearchTreeTest {

	public static void main(String[] args) {
		
		BinarySearchTree bst = new BinarySearchTree();
		
		// Insert nodes
		bst.BSTInsert(50);
		bst.BSTInsert(30);
		bst.BSTInsert(20);
		bst.BSTInsert(40);
		bst.BSTInsert(70);
		bst.BSTInsert(60);
		bst.BSTInsert(80);
		
		// Display BST (inorder traversal)
		System.out.println("Inorder traversal of the given tree");
		bst.inorder();
		
		// Find minimum and maximum value nodes
		System.out.println("Minimum value node in BST is " + bst.TreeMinimum(bst.root).key);
		
		// Find maximum value node
		System.out.println("Maximum value node in BST is " + bst.TreeMaximum(bst.root).key);
		
		// Search for a value
		int key = 60;
		Node result = bst.TreeSearch(bst.root, key);
		if (result != null)
			System.out.println("Key " + key + " found in BST");
		else
			System.out.println("Key " + key + " not found in BST");

	}

}
