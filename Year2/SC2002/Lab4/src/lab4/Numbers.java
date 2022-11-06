package lab4;

import java.util.Scanner;

public class Numbers {
// --------------------------------------------
// Reads in an array of integers, sorts them,
// then prints them in sorted order.
// --------------------------------------------
	public static void main(String[] args) {
		//callSelectionSort();
		callInsertionSort();
	}
	
	private static void callSelectionSort() {
		Integer[] intList; //changed to Integer because int is not a class
		int size;
		Scanner scan = new Scanner(System.in);
		System.out.print("\nHow many integers do you want to sort? ");
		size = scan.nextInt();
		intList = new Integer[size];
		System.out.println("\nEnter the numbers...");
		for (int i = 0; i < size; i++)
			intList[i] = scan.nextInt();
		Sorting.selectionSort(intList);
		System.out.println("\nYour numbers in sorted order...");
		for (int i = 0; i < size; i++)
			System.out.print(intList[i] + " ");
		System.out.println();
	}
	
	private static void callInsertionSort() {
		Integer[] intList; //changed to Integer because int is not a class
		int size;
		Scanner scan = new Scanner(System.in);
		System.out.print("\nHow many integers do you want to sort? ");
		size = scan.nextInt();
		intList = new Integer[size];
		System.out.println("\nEnter the numbers...");
		for (int i = 0; i < size; i++)
			intList[i] = scan.nextInt();
		Sorting.insertionSort(intList);
		System.out.println("\nYour numbers in sorted order...");
		for (int i = 0; i < size; i++)
			System.out.print(intList[i] + " ");
		System.out.println();
	}
}
