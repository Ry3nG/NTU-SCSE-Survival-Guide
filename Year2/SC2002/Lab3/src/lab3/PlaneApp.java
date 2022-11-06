package lab3;

import java.util.Scanner;

public class PlaneApp {
    public static void main(String[] args) {
        System.out.println("Welcome to the plane seat reservation system.");
        Plane plane = new Plane();
        int option = 0;

        System.out.println("1. Show the number of empty seats");
        System.out.println("2. Show the list of empty seats");
        System.out.println("3. Show the list of seat assignments by seat ID");
        System.out.println("4. Show the list of seat assignments by customer ID");
        System.out.println("5. Assign a customer to a seat");
        System.out.println("6. Remove a seat assignment");
        System.out.println("7. Exit");

        try (Scanner sc = new Scanner(System.in)) {
            System.out.println();
            System.out.println("Enter the number of your choice:");
            while (sc.hasNextInt()) {

                option = sc.nextInt();
                switch (option) {
                    case 1:
                        plane.showNumEmptySeats();
                        break;
                    case 2:
                        plane.showEmptySeats();
                        break;
                    case 3:
                        plane.showAssignedSeats(true);
                        break;
                    case 4:
                        plane.showAssignedSeats(false);
                        break;
                    case 5:
                        System.out.println("Assigning Seat ...");
                        System.out.println("Please enter the seat ID:");
                        int seatId = sc.nextInt();
                        System.out.println("Please enter the customer ID:");
                        int customerId = sc.nextInt();
                        plane.assignSeat(seatId, customerId);
                        break;
                    case 6:
                        System.out.println("Please enter the seat ID:");
                        seatId = sc.nextInt();
                        plane.unassignSeat(seatId);
                        break;
                    case 7:
                        System.out.println("Thank you for using the plane seat reservation system.");
                        break;

                }
                System.out.println();
                System.out.println("Enter the number of your choice:");
            }
        }
        try {
        } catch (Exception e) {
            System.out.println("Invalid input.");
        }

    }

}
