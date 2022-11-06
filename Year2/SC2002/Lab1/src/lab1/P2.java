package lab1;

import java.util.Scanner;

/*
 * The salary scheme for a company is given as follows:
 * Salary range for grade A: $700 - $899
 * Salary range for grade B: $600 - $799
 * Salary range for grade C: $500 - $649
 * A person whose salary is between $600 and $649 is in grade C if his merit points are below 10
 * otherwise he is in grade B. A person whose salary is between $700 and $799 is in grade B if his merit
 * points are below 20, otherwise, he is in grade A. Write a program to read in a person’s salary and 
 * his merit points, and displays his grade.
 * 
 * Important: Remember to name the source code of this program as P2.java and name the compiled 
 * class code as P2.class inside the sub-directory lab1.
 * Test cases: (1) salary : $500, merit : 10; (2) salary : $610, merit : 5; (3) salary : $610, merit : 10; (4)
 * salary : $710, merit : 15; (5) salary : $710, merit : 20; (6) salary : 800, merit : 30.
 * Expected outputs: (1) salary : $500, merit : 10 – Grade C; (2) salary : $610, merit : 5 – Grade C; (3)
 * salary : $610, merit : 10 – Grade B; (4) salary : $710, merit : 15 – Grade B; (5) salary : $710, merit :
 * 20 – Grade A; (6) salary : 800, merit : 30 – Grade A.
 */

public class P2 {
	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			System.out.println("Input the salary and merit: ");
			while(sc.hasNextInt())
			{
				int salary = sc.nextInt();
				int merit = sc.nextInt();
				
				if(salary >= 799)
				{
					System.out.println("Grade A");
				}
				else if (salary>=700 && salary<=799) {
					if(merit>=20)
						System.out.println("Grade A");
					else 
						System.out.println("Grade B");
				}
				else if(salary>=649 && salary<=700) {
					System.out.println("Grade B");
				}
				else if(salary>=600 && salary<=649) {
					if(merit>=10)
						System.out.println("Grade B");
					else
						System.out.println("Grade C");
				}
				else
					System.out.println("Grade C");
			}
		}
	}

}
