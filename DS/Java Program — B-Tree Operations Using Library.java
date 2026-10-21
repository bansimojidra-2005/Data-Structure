
import java.util.Scanner;
import java.util.TreeSet;

public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        TreeSet<Integer> tree = new TreeSet<>();

        System.out.println("================================");
        System.out.println("    INTERACTIVE B-TREE SIMULATION");
        System.out.println("================================");

        System.out.print("Enter minimum degree t (minimum 2): ");
        int t = sc.nextInt();

        while (t < 2) {
            System.out.print("Invalid degree! Enter t >= 2: ");
            t = sc.nextInt();
        }

        System.out.println("Tree initialized with t = " + t);
        System.out.println("Maximum keys per node = " + (2 * t - 1));

        while (true) {
            System.out.println("\n-----------------------------");
            System.out.println("1. Insert Key");
            System.out.println("2. Traverse / Print Tree");
            System.out.println("3. Exit");
            System.out.print("Choice: ");

            int choice = sc.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Enter key to insert: ");
                    int key = sc.nextInt();

                    if (tree.add(key)) {
                        System.out.println("Key " + key + " inserted.");
                    } else {
                        System.out.println("Duplicate key not allowed.");
                    }
                    break;

                case 2:
                    System.out.println("In-order Traversal: " + tree);
                    break;

                case 3:
                    System.out.println("Exiting application.");
                    sc.close();
                    return;

                default:
                    System.out.println("Invalid choice!");
            }
        }
    }
}
