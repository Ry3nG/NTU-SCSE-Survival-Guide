package lab1;

import java.util.Scanner;


/*
 * Write a program that reads the height from a user and prints a pattern with the specified height. For
 * example, when the user enters height = 3, the following pattern is printed:
 * AA
 * BBAA
 * AABBAA
 * If the height is 7, then the following pattern is printed:
 * AA
 * BBAA
 * AABBAA
 * BBAABBAA
 * AABBAABBAA
 * BBAABBAABBAA
 * AABBAABBAABBAA
 */

public class P4 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		while (sc.hasNextInt()) {

			int height = sc.nextInt();

			if (height <= 0)
				System.out.println("Error Input!");
			else {
				String[] sArr = { "BB", "AA" };

				for (int numOfLine = 1; numOfLine <= height; numOfLine++) {
					for (int j = numOfLine; j > 0; j--) {
						System.out.print(sArr[j % 2]);

					}
					System.out.println();
				}
			}
		}
	}

}
