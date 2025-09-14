package Assignment9Graphs;

import java.util.*;

public class GraphRepresentation {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // === TASK 1: Adjacency Matrix using 2D array ===
        System.out.print("Enter number of vertices: ");
        int v = scanner.nextInt();
        scanner.nextLine(); // Consume newline
        // Using String array to store vertex names
        String[] vertices = new String[v];
        Map<String, Integer> vertexIndexMap = new HashMap<>();

        System.out.println("Enter list of vertices:");
        for (int i = 0; i < v; i++) {
            vertices[i] = scanner.next().trim();
            vertexIndexMap.put(vertices[i], i);
        }
        // Using adjacency matrix to represent the graph
        int[][] adjMatrix = new int[v][v];
        System.out.println("Enter 1 for Yes and 0 for No");
        // Filling the adjacency matrix
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                System.out.print("Does " + vertices[i] + " have an edge with " + vertices[j] + " ?\n");
                adjMatrix[i][j] = scanner.nextInt();
            }
        }
        // Displaying the adjacency matrix
        System.out.println("\nFollowing graph is stored");
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                System.out.print(adjMatrix[i][j] + " ");
            }
            System.out.println();
        }

        // === TASK 2: Adjacency Matrix using Ragged Array ===
        // Ragged array to represent the adjacency list
        scanner.nextLine(); // consume leftover newline
        System.out.print("\n\nEnter number of vertices: ");
        v = scanner.nextInt();
        scanner.nextLine();
        // Using String array to store vertex names
        String[] vertices2 = new String[v];
        Map<String, Integer> indexMap2 = new HashMap<>();

        System.out.println("Enter list of vertices:");
        for (int i = 0; i < v; i++) {
            vertices2[i] = scanner.next().trim();
            indexMap2.put(vertices2[i], i);
        }
        // Using ragged array to represent the graph
        int[][] raggedMatrix = new int[v][];
        for (int i = 0; i < v; i++) {
            System.out.print("How many edges are associated with " + vertices2[i] + ": ");
            int edgeCount = scanner.nextInt();
            raggedMatrix[i] = new int[edgeCount];
            System.out.println("Enter adjacent vertices to " + vertices2[i] + ":");
            for (int j = 0; j < edgeCount; j++) {
                String neighbor = scanner.next();
                raggedMatrix[i][j] = indexMap2.get(neighbor.trim());
            }
        }

        System.out.println("Stored Ragged Matrix:");
        for (int i = 0; i < raggedMatrix.length; i++) {
            for (int j = 0; j < raggedMatrix[i].length; j++) {
                System.out.print(raggedMatrix[i][j] + " ");
            }
            System.out.println();
        }

        // === TASK 3: Adjacency List ===
        scanner.nextLine(); // consume newline
        System.out.print("\n\nEnter number of vertices: ");
        v = scanner.nextInt();
        scanner.nextLine();
        // Using String array to store vertex names
        String[] vertices3 = new String[v];
        Map<String, Integer> indexMap3 = new HashMap<>();
        List<List<String>> adjList = new ArrayList<>();

        System.out.println("Enter list of vertices:");
        for (int i = 0; i < v; i++) {
            vertices3[i] = scanner.next().trim();
            indexMap3.put(vertices3[i], i);
            adjList.add(new ArrayList<>());
        }

        scanner.nextLine(); // consume newline
        for (int i = 0; i < v; i++) {
            System.out.print("Enter adjacent vertices for " + vertices3[i] + " (comma separated): ");
            String[] neighbors = scanner.nextLine().split(",");
            for (String neighbor : neighbors) {
                neighbor = neighbor.trim();
                if (indexMap3.containsKey(neighbor)) {
                    adjList.get(i).add(neighbor);
                }
            }
        }

        System.out.println("\nAdjacency List:");
        for (int i = 0; i < v; i++) {
            System.out.print(vertices3[i] + " -> ");
            for (String neighbor : adjList.get(i)) {
                System.out.print(neighbor + " ");
            }
            System.out.println();
        }

        scanner.close();
    }
}
