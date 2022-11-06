package lab1;

import java.util.Scanner;

public class P3 {

	public static double currencyConvention(int value) {
		double result = 0;
		double exchangeRate = 1.82;
		result = value * exchangeRate;
		return result;

	}

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			while (sc.hasNextInt()) {
				int starting = sc.nextInt();
				int ending = sc.nextInt();
				int increment = sc.nextInt();
				// error check
				if (ending < starting) {
					System.out.println("Error Input!");
				} else {
					System.out.println("US$\tS$");
					System.out.println("------------");
					
					/*
					// for loop
					for (int i = starting; i <= ending; i += increment) {
						System.out.println(i + "\t" + currencyConvention(i));

					}
					*/
					
					/*
					// while loop
					int i = starting;
					while(i<=ending)
					{
						System.out.println(i + "\t" + currencyConvention(i));
						i += increment;
					}
					*/
					
					//do-while loop
					int i = starting;
					do {
						System.out.println(i + "\t" + currencyConvention(i));
						i += increment;
					}while(i<=ending);
					

				}
			}
		}
	}
}
