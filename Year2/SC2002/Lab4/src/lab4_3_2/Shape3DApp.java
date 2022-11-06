package lab4_3_2;

import java.util.Scanner;

public class Shape3DApp {
    public static void main(String[] args) {
        System.out.println("Enter the totol number of 3D-Shapes: ");
        Scanner sc = new Scanner(System.in);
        int total = sc.nextInt();
        Shape[] shapes = new Shape[total];

        System.out.println("Choose the 3D-shape and enter the required data: ");
        for (int i = 0; i < total; i++) {
            System.out.println("1. Cubiod");
            System.out.println("2. Cone");
            System.out.println("3. Cylinder");
            System.out.println("4. Sphere");
            System.out.println("5. Pyramid");
            System.out.println("6. Exit");
            int choice = sc.nextInt();
            switch (choice) {
                case 1:
                    System.out.println("Enter the length, width and height of the cubiod: ");
                    double length = sc.nextDouble();
                    double width = sc.nextDouble();
                    double height = sc.nextDouble();
                    shapes[i] = new Cubiod(length, width, height);
                    break;
                case 2:
                    System.out.println("Enter the radius and height of the cone: ");
                    double radius = sc.nextDouble();
                    height = sc.nextDouble();
                    shapes[i] = new Cone(radius, height);
                    break;
                case 3:
                    System.out.println("Enter the radius and height of the cylinder: ");
                    radius = sc.nextDouble();
                    height = sc.nextDouble();
                    shapes[i] = new Cylinder(radius, height);
                    break;
                case 4:
                    System.out.println("Enter the radius of the sphere: ");
                    radius = sc.nextDouble();
                    shapes[i] = new Sphere(radius);
                    break;
                case 5:
                    System.out.println("Enter the length, width and height of the pyramid: ");
                    length = sc.nextDouble();
                    width = sc.nextDouble();
                    height = sc.nextDouble();
                    shapes[i] = new Pyramid(length, width, height);
                    break;
                case 6:
                    System.out.println("Exiting...");
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Try again.");
                    break;
            }

        }
        System.out.println("Choose the calculation type: ");
        System.out.println("1. Surface Area");
        int choice = sc.nextInt();
        switch (choice) {
            case 1:
                // print total surface area
                double totalSurfaceArea = 0;
                for (int i = 0; i < total; i++) {
                    totalSurfaceArea += shapes[i].getArea();
                }
                System.out.println("Total Surface Area: " + totalSurfaceArea);
                break;

        }
    }
}
