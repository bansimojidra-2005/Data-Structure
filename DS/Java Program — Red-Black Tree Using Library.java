
import java.util.Scanner;
import java.util.TreeSet;

public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        TreeSet<Integer> tree = new TreeSet<>();

        while (true) {
            System.out.println("\n--- RED BLACK TREE ---");
            System.out.println("1. Insert");
            System.out.println("2. Delete");
            System.out.println("3. Display");
            System.out.println("4. Exit");
            System.out.print("Enter choice: ");

            int choice = sc.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Enter value: ");
                    int data = sc.nextInt();

                    if (tree.add(data))
                        System.out.println("Element inserted.");
                    else
                        System.out.println("Duplicate value not allowed.");
                    break;

                case 2:
                    System.out.print("Enter value to delete: ");
                    data = sc.nextInt();

                    if (tree.remove(data))
                        System.out.println("Element deleted.");
                    else
                        System.out.println("Element not found.");
                    break;

                case 3:
                    System.out.println("Inorder: " + tree);
                    break;

                case 4:
                    System.out.println("Exiting program.");
                    sc.close();
                    return;

                default:
                    System.out.println("Invalid choice.");
            }
        }
    }
}
