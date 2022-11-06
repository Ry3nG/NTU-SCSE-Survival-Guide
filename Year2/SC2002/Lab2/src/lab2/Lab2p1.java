package lab2;

import java.util.Random;
import java.util.Scanner;

public class Lab2p1 {
	public static void main(String[] args) {
		int choice;
		try (Scanner sc = new Scanner(System.in)) {
			do {
				System.out.println("Perform the following methods:");
				System.out.println("1: multiplication test");
				System.out.println("2: quotient using division by subtraction");
				System.out.println("3: remainder using division by subtraction");
				System.out.println("4: count the number of digits");
				System.out.println("5: position of a digit");
				System.out.println("6: extract all odd digits");
				System.out.println("7: quit");
				choice = sc.nextInt();
				switch (choice) {
				case 1:
					mulTest();
					break;
				case 2:
					System.out.println("Input two integers to carry out the calculation.");
					int m = sc.nextInt();
					int n = sc.nextInt();
					int result = divide(m, n);
					System.out.println(m + "/" + n + " = " + result);
					break;
				case 3:
					System.out.println("Input two integers to carry out the calculation.");
					m = sc.nextInt();
					n = sc.nextInt();
					result = modulus(m, n);
					System.out.println(m + "%" + n + " = " + result);
					break;
				case 4:
					System.out.println("Input one positve integer to count its digit.");
					n = sc.nextInt();
					result = countDigits(n);
					if (result == 0)
						System.out.println("Error Input!");
					else
						System.out.println(n + " - count = " + result);
					break;
				case 5:
					System.out.println("Input one positve integer.");
					m = sc.nextInt();
					System.out.println("Input the digit.");
					n = sc.nextInt();
					result = position(m, n);
					System.out.println("position = " + result);
					break;
				case 6: /* add extractOddDigits() call */
					System.out.println("Input a number to extract its odd digits.");
					long input = sc.nextLong();
					long output = extractOddDigits(input);
					if (output == 0)
						System.out.println("Error Input!");
					else
						System.out.println("oddDgits = " + output);
					break;

				case 7:
					System.out.println("Program terminating …");
				}

			} while (choice < 7);
		}
	}

	/* add method code here */
	public static void mulTest() {
		int faults = 0, num1, num2;
		final int MAX = 9, MIN = 0, TRIAL = 5; // use to bound the number generated, TRIAL is the questions student need
												// to answer
		Scanner sc = new Scanner(System.in);
		for (int i = 0; i < TRIAL; i++) {
			num1 = new Random().nextInt(MAX - MIN + 1) + MIN;
			num2 = new Random().nextInt(MAX - MIN + 1) + MIN;
			System.out.println("How much is " + num1 + " times " + num2 + "?");
			if (sc.nextInt() != num1 * num2)
				faults++;
		}
		System.out.println((TRIAL - faults) + " answers out of " + TRIAL + " is correct.");
	}

	public static int divide(int m, int n) {

		int count = 0;
		while (m >= n) {
			m -= n;
			count++;
		}
		return count;
	}

	public static int modulus(int m, int n) {

		int count = 0, origin = m;
		while (m >= n) {
			m -= n;
			count++;
		}
		return origin - count * n;
	}

	public static int countDigits(int n) {

		int count = 0;
		while (n > 0) {
			n /= 10;
			count++;
		}
		return count;
	}

	public static int position(int n, int digit) {
		int pos = 0;
		while (n > 0) {
			int lastDigit = n - ((n / 10) * 10);
			n /= 10;
			pos++;
			if (lastDigit == digit)
				return pos;
		}
		return -1;
	}

	public static long extractOddDigits(long n) {
		long output = 0;
		long lastDigit;
		long coef = 1; // the multiplication coefficient x1,x10,x100 ...
		if (n < 0)
			return 0;
		while (n > 0) {
			lastDigit = n - (n / 10) * 10;
			if (lastDigit % 2 == 1)// is odd
			{
				output += lastDigit * coef;
				coef *= 10;
			}
			n /= 10;
		}

		output = output == 0 ? -1 : output;

		return output;

	}

}