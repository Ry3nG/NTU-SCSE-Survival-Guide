package lab4_3_2;

import java.util.Scanner;

public class Shape2DApp {

    public static void main(String[] args) {
        System.out.println("Enter the totol number of Shapes: ");
        Scanner sc = new Scanner(System.in);
        int total = sc.nextInt();
        Shape[] shapes = new Shape[total];
        
        System.out.println("Choose the shape and enter the required data: ");
        for (int i = 0; i < total; i++) {
            System.out.println("1. Rectangle");
            System.out.println("2. Square");
            System.out.println("3. Circle");
            System.out.println("4. Triangle");
            System.out.println("5. Exit");
            int choice = sc.nextInt();
            switch (choice) {
            case 1:
                System.out.println("Enter the length and width of the rectangle: ");
                double length = sc.nextDouble();
                double width = sc.nextDouble();
                shapes[i] = new Rectangle(length, width);
                break;
            case 2:
                System.out.println("Enter the side of the square: ");
                double side = sc.nextDouble();
                shapes[i] = new Square(side);
                break;
            case 3:
                System.out.println("Enter the radius of the circle: ");
                double radius = sc.nextDouble();
                shapes[i] = new Circle(radius);
                break;
            case 4:
                System.out.println("Enter the base and height of the triangle: ");
                double base = sc.nextDouble();
                double height = sc.nextDouble();
                shapes[i] = new Triangle(base, height);
                break;
            case 5:
                System.out.println("Exiting...");
                System.exit(0);
            default:
                System.out.println("Invalid choice. Try again.");
                break;
            }
        }

        System.out.println("Choose the calculation type: ");
        System.out.println("1. Area");
        int choice = sc.nextInt();
        switch (choice) {
        case 1:
            //print total area
            double totalArea = 0;
            for (int i = 0; i < total; i++) {
                totalArea += shapes[i].getArea();
            }
            System.out.println("Total area: " + totalArea);
            break;
        default:
            System.out.println("Invalid choice. Try again.");
            break;
        }
        sc.close();

    }
}
