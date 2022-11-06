package lab1;

import java.util.Scanner;

public class P1 {
	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			while (sc.hasNext()) {
				char choice = sc.next().charAt(0);

				switch (choice) {
				case 'A':
				case 'a':

					System.out.println("Action movie fan");
					break;
				case 'C':
				case 'c':
					System.out.println("Comedy movie fan");
					break;
				case 'D':
				case 'd':
					System.out.println("Drama movie fan");
					break;
				default:
					System.out.println("Invalid choice");
					break;
				}

			}
		}
	}

}
