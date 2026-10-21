
import java.util.Scanner;
import java.util.TreeSet;

public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        TreeSet<Integer> tree = new TreeSet<>();

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();

        System.out.println("Enter " + n + " elements:");

        for (int i = 0; i < n; i++) {
            tree.add(sc.nextInt());
        }

        System.out.println("Tree after insertion: " + tree);

        System.out.print("Enter key to search: ");
        int key = sc.nextInt();

        if (tree.contains(key)) {
            System.out.println("Key " + key + " found.");
        } else {
            System.out.println("Key " + key + " not found.");
        }

        System.out.print("Enter key to delete: ");
        int del = sc.nextInt();

        if (tree.remove(del)) {
            System.out.println("Key " + del + " deleted.");
        } else {
            System.out.println("Key " + del + " not found.");
        }

        System.out.println("Tree after deletion: " + tree);

        sc.close();
    }
}
